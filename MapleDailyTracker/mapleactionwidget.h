#ifndef MAPLEACTIONWIDGET_H
#define MAPLEACTIONWIDGET_H

#include <QWidget>

#include "mapleaction.h"

namespace Ui {
class MapleActionWidget;
}

class MapleActionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapleActionWidget(QWidget *parent = nullptr);
    ~MapleActionWidget();

    const MapleAction &getMapleAction() const;
    void setMapleAction(const MapleAction &newMapleAction);

private:
    MapleAction mapleAction;
    Ui::MapleActionWidget *ui;
};

#endif // MAPLEACTIONWIDGET_H
