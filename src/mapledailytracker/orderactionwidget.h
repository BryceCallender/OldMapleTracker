#ifndef ORDERACTIONWIDGET_H
#define ORDERACTIONWIDGET_H

#include <QWidget>
#include <QVector>

#include "mapleaction.h"

namespace Ui {
class OrderActionWidget;
}

class OrderActionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderActionWidget(QWidget *parent = nullptr);
    ~OrderActionWidget();

    QVector<MapleAction> finalizeOrder();

private:
    Ui::OrderActionWidget *ui;
};

#endif // ORDERACTIONWIDGET_H
