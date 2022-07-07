#include "character.h"

Character::Character()
{
    logger = Logger::getLogger();
}

void Character::setName(const QString& name)
{
    this->name = name;
}

void Character::setOrder(const int order)
{
    this->order = order;
}

void Character::setDailies(QVector<MapleAction> actions)
{
    this->dailies = actions;
}

void Character::setWedWeeklies(QVector<MapleAction> actions)
{
    this->wedWeeklies = actions;
}

void Character::setMonWeeklies(QVector<MapleAction> actions)
{
    this->monWeeklies = actions;
}

const QString Character::getName() const
{
    return name;
}

int Character::getOrder() const
{
    return order;
}

void Character::read(const QJsonObject& json)
{
    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();

    if (json.contains("order"))
        order = json["order"].toInt();

    readActions(json, "dailies", dailies);
    readActions(json, "wedWeeklies", wedWeeklies);
    readActions(json, "monWeeklies", monWeeklies);
}

void Character::write(QJsonObject& json)
{
    json["name"] = name;
    json["order"] = order;
    json["dailies"] = actionsToJSONArray(dailies);
    json["wedWeeklies"] = actionsToJSONArray(wedWeeklies);
    json["monWeeklies"] = actionsToJSONArray(monWeeklies);
}

QJsonArray Character::actionsToJSONArray(QVector<MapleAction>& actions)
{
    QJsonArray characterActions;
    for (const MapleAction& action : actions)
    {
        QJsonObject dailyAction;
        action.write(dailyAction);
        characterActions.push_back(dailyAction);
    }

    return characterActions;
}

void Character::readActions(const QJsonObject& json, const QString& name, QVector<MapleAction>& actions)
{
    if (json.contains(name) && json[name].isArray())
    {
        QJsonArray jsonArray = json[name].toArray();
        actions.clear();
        actions.reserve(jsonArray.size());
        for (int i = 0; i < jsonArray.size(); ++i)
        {
            QJsonObject actionObject = jsonArray[i].toObject();
            MapleAction action;
            action.read(actionObject);
            actions.push_back(action);
        }
    }
}

void Character::resetActions(QVector<MapleAction>& actions)
{
    for (MapleAction& action: actions)
    {
        action.done = false;
    }
}

QVector<MapleAction>& Character::getMonWeeklies()
{
    return monWeeklies;
}

bool Character::removeExpiredActions()
{
    bool removed = false;
    const auto pred = [&removed, this](const MapleAction& action)
    {
        if (action.isTemporary)
        {
            QDateTime removalTimeUtc = action.removalTime.toUTC();
            QDateTime currentTimeUtc = QDateTime::currentDateTimeUtc();

            if (currentTimeUtc.secsTo(removalTimeUtc) <= 0)
            {
                removed = true;
                logger->info("Removed temporary action: {}", action.toString());
            }
        }

        return removed;
    };

    dailies.removeIf(pred);
    wedWeeklies.removeIf(pred);
    monWeeklies.removeIf(pred);

    return removed;
}

void Character::resetDailies()
{
    resetActions(dailies);
}

void Character::resetWedWeeklies()
{
    resetActions(wedWeeklies);
}

void Character::resetMonWeeklies()
{
    resetActions(monWeeklies);
}

Character *Character::clone()
{
    return new Character(*this);
}

QVector<MapleAction>& Character::getWedWeeklies()
{
    return wedWeeklies;
}

QVector<MapleAction>& Character::getDailies()
{
    return dailies;
}
