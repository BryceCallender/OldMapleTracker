#include "orderactionwidget.h"
#include "ui_orderactionwidget.h"

OrderActionWidget::OrderActionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderActionWidget)
{
    ui->setupUi(this);

    connect(ui->finishButton, &QPushButton::clicked, this, &OrderActionWidget::finalizeOrder);
}

OrderActionWidget::~OrderActionWidget()
{
    delete ui;
}

QVector<MapleAction> OrderActionWidget::finalizeOrder()
{

}
