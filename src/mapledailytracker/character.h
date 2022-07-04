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

    void setName(const QString &name);
    void setOrder(const int order);
    void setDailies(QVector<MapleAction> actions);
    void setWedWeeklies(QVector<MapleAction> actions);
    void setMonWeeklies(QVector<MapleAction> actions);

    const QString getName() const;
    int getOrder() const;

    void read(const QJsonObject& json);
    void write(QJsonObject& json);

    QVector<MapleAction>& getDailies();
    QVector<MapleAction>& getWedWeeklies();
    QVector<MapleAction>& getMonWeeklies();

    bool removeExpiredActions();
    void resetDailies();
    void resetWedWeeklies();
    void resetMonWeeklies();

    Character* clone();

    bool operator ==(const Character& other)
    {
        return name == other.getName();
    }
private:
    QJsonArray actionsToJSONArray(QVector<MapleAction>& actions);
    void readActions(const QJsonObject& json, const QString& name, QVector<MapleAction>& actions);
    void resetActions(QVector<MapleAction>& actions);

    QString name;
    int order;
    QVector<MapleAction> dailies;
    QVector<MapleAction> wedWeeklies;
    QVector<MapleAction> monWeeklies;
};

#endif // CHARACTER_H
