#include "mapleactionlistwidgetitem.h"

MapleActionListWidgetItem::MapleActionListWidgetItem(const MapleAction& action, QListWidget *parent) : QListWidgetItem(action.name, parent)
{
    this->action = action;
}
