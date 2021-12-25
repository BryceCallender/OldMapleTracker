#include "character.h"

Character::Character()
{

}

void Character::setName(QString name)
{
    this->name = name;
}

QString Character::getName()
{
    return name;
}

void Character::addDaily(MapleAction daily)
{
    this->dailies.push_back(daily);
}

void Character::addWedWeekly(MapleAction weekly)
{
    this->wedWeeklies.push_back(weekly);
}

void Character::addMonWeekly(MapleAction weekly)
{
    this->monWeeklies.push_back(weekly);
}

void Character::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();

    readActions(json, "dailies", dailies);
    readActions(json, "wedWeeklies", wedWeeklies);
    readActions(json, "monWeeklies", monWeeklies);
}

void Character::write(QJsonObject &json)
{
    json["name"] = name;
    json["dailies"] = actionsToJSONArray(dailies);
    json["wedWeeklies"] = actionsToJSONArray(wedWeeklies);
    json["monWeeklies"] = actionsToJSONArray(monWeeklies);
}

QJsonArray Character::actionsToJSONArray(QVector<MapleAction> actions)
{
    QJsonArray characterActions;
    for (const MapleAction& action : actions)
    {
        QJsonObject dailyAction;
        dailyAction["name"] = action.name;
        dailyAction["done"] = action.done;
        characterActions.push_back(dailyAction);
    }

    return characterActions;
}

void Character::readActions(const QJsonObject &json, QString name, QVector<MapleAction> actions)
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

            if (actionObject.contains("done") && actionObject["done"].isString())
                action.done = actionObject["done"].toBool();

            actions.push_back(action);
        }
    }
}
