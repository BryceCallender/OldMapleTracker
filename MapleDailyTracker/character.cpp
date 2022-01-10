#include "character.h"

Character::Character()
{
}

void Character::setName(const QString& name)
{
    this->name = name;
}

const QString Character::getName() const
{
    return name;
}

void Character::read(const QJsonObject& json)
{
    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();

    readActions(json, "dailies", dailies);
    readActions(json, "wedWeeklies", wedWeeklies);
    readActions(json, "monWeeklies", monWeeklies);
}

void Character::write(QJsonObject& json)
{
    json["name"] = name;
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
        dailyAction["name"] = action.name;
        dailyAction["done"] = action.done;
        dailyAction["isTemporary"] = action.isTemporary;
        dailyAction["removalTime"] = action.removalTime.toString();
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

            if (actionObject.contains("name") && actionObject["name"].isString())
                action.name = actionObject["name"].toString();

            if (actionObject.contains("done") && actionObject["done"].isBool())
                action.done = actionObject["done"].toBool();

            if (actionObject.contains("isTemporary") && actionObject["isTemporary"].isBool())
                action.isTemporary = actionObject["isTemporary"].toBool();

            if (actionObject.contains("removalTime") && actionObject["removalTime"].isString())
                action.removalTime = QDateTime::fromString(actionObject["removalTime"].toString());

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

void Character::removeExpiredActions()
{
    const auto pred = [](const MapleAction& action)
    {
        if (action.isTemporary)
        {
            QDateTime removalTimeUtc = action.removalTime.toUTC();
            QDateTime currentTimeUtc = QDateTime::currentDateTimeUtc();

            if (currentTimeUtc.secsTo(removalTimeUtc) <= 0)
            {
                return true;
            }
        }

        return false;
    };

    dailies.removeIf(pred);
    wedWeeklies.removeIf(pred);
    monWeeklies.removeIf(pred);
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

QVector<MapleAction>& Character::getWedWeeklies()
{
    return wedWeeklies;
}

QVector<MapleAction>& Character::getDailies()
{
    return dailies;
}
