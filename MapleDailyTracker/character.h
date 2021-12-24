#ifndef CHARACTER_H
#define CHARACTER_H

#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QJsonArray>

#include "mapleaction.h"

class Character
{
public:
    Character();
    void setName(QString name);
    QString getName();
    void addDaily(MapleAction daily);
    void addWedWeekly(MapleAction weekly);
    void addMonWeekly(MapleAction weekly);

    void read(const QJsonObject &json);
    void write(QJsonObject &json);

private:
    QJsonArray actionsToJSONArray(QVector<MapleAction> actions);
    void readActions(const QJsonObject &json, QString name, QVector<MapleAction> actions);

    QString name;
    QVector<MapleAction> dailies;
    QVector<MapleAction> wedWeeklies;
    QVector<MapleAction> monWeeklies;
};

#endif // CHARACTER_H
