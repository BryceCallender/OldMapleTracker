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
    const QString getName() const;

    void addDaily(MapleAction daily);
    void addWedWeekly(MapleAction weekly);
    void addMonWeekly(MapleAction weekly);

    void read(const QJsonObject &json);
    void write(QJsonObject &json);

    QVector<MapleAction>& getDailies();

    QVector<MapleAction>& getWedWeeklies();

    QVector<MapleAction>& getMonWeeklies();

private:
    QJsonArray actionsToJSONArray(QVector<MapleAction> actions);
    void readActions(const QJsonObject &json, QString name, QVector<MapleAction> actions);

    QString name;
    QVector<MapleAction> dailies;
    QVector<MapleAction> wedWeeklies;
    QVector<MapleAction> monWeeklies;
};

#endif // CHARACTER_H
