#ifndef TRACKERWIDGET_H
#define TRACKERWIDGET_H

#include <QWidget>
#include <QVector>
#include <QListWidget>

#include "character.h"
#include "mapleaction.h"

namespace Ui {
class TrackerWidget;
}

class TrackerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrackerWidget(QVector<MapleAction>& actions, QWidget *parent = nullptr);
    ~TrackerWidget();
private slots:
    void addMapleAction();
    void addToUnfinishedListWidget(MapleAction& action);
    void moveToFinished(QListWidgetItem *item);
signals:
    void updateProgress();
private:
    Ui::TrackerWidget *ui;
    QVector<MapleAction> actions;

    QListWidget* unfinishedList;
    QVector<MapleAction> unfinished;

    QListWidget* finishedList;
    QVector<MapleAction> finished;
};

#endif // TRACKERWIDGET_H
