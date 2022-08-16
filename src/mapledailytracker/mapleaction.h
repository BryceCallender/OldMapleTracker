#ifndef MAPLEACTION_H
#define MAPLEACTION_H

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "actiontype.h"

struct MapleAction
{
    QString name;
    ActionType type;
    int order;
    bool done;

    bool isTemporary;
    QDateTime removalTime;


    void read(const QJsonObject& json)
    {
        if (json.contains("name") && json["name"].isString())
            name = json["name"].toString();

        if (json.contains("order"))
            order = json["order"].toInt();

        if (json.contains("done") && json["done"].isBool())
            done = json["done"].toBool();

        if (json.contains("isTemporary") && json["isTemporary"].isBool())
            isTemporary = json["isTemporary"].toBool();

        if (json.contains("removalTime") && json["removalTime"].isString())
            removalTime = QDateTime::fromString(json["removalTime"].toString());
    }

    void write(QJsonObject& json) const
    {
        json["name"] = name;
        json["order"] = order;
        json["done"] = done;
        json["isTemporary"] = isTemporary;
        json["removalTime"] = removalTime.toString();
    }

    std::string toString() const
    {
        QJsonObject data;
        write(data);

        QJsonDocument doc(data);
        return doc.toJson(QJsonDocument::Compact).toStdString();
    }
};

Q_DECLARE_METATYPE(MapleAction)

#endif // MAPLEACTION_H
