#include "mapleactionwidget.h"
#include "ui_mapleactionwidget.h"

MapleActionWidget::MapleActionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapleActionWidget)
{
    ui->setupUi(this);
}

MapleActionWidget::~MapleActionWidget()
{
    delete ui;
}

const MapleAction &MapleActionWidget::getMapleAction() const
{
    return mapleAction;
}

void MapleActionWidget::setMapleAction(const MapleAction &newMapleAction)
{
    mapleAction = newMapleAction;
    ui->mapleAction->setText(mapleAction.name);
    ui->mapleAction->setChecked(mapleAction.done);
}
