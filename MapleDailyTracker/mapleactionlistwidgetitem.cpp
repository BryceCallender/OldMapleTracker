#include "mapleactionlistwidgetitem.h"

MapleActionListWidgetItem::MapleActionListWidgetItem(MapleAction& action, QListWidget* parent) : QListWidgetItem(action.name, parent), action(action)
{
}

MapleAction& MapleActionListWidgetItem::getAction()
{
    return action;
}
