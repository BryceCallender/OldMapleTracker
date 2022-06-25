#ifndef MAPLEACTIONLISTWIDGETITEM_H
#define MAPLEACTIONLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QDebug>

#include "mapleaction.h"

class MapleActionListWidgetItem: public QListWidgetItem
{
public:
    explicit MapleActionListWidgetItem(const MapleAction& action, QListWidget *parent = nullptr);

    bool operator <(const QListWidgetItem& other) const
    {
        return action.order < static_cast<const MapleActionListWidgetItem&>(other).action.order;
    }
private:
    MapleAction action;
};


#endif // MAPLEACTIONLISTWIDGETITEM_H
