#ifndef TRACKERWIDGET_H
#define TRACKERWIDGET_H

#include <QWidget>
#include <QVector>
#include <QListWidget>
#include <QAction>

#include "character.h"
#include "mapleaction.h"
#include "progress.h"

namespace Ui {
class TrackerWidget;
}

class TrackerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrackerWidget(QVector<MapleAction>& actions, Progress* progress, QWidget *parent = nullptr);
    ~TrackerWidget();
private slots:
    void addMapleAction();
    void addToUnfinishedListWidget(MapleAction& action);
    void moveItem(QListWidgetItem *item);
signals:
    void updateProgress();
private:
    Ui::TrackerWidget *ui;
    Progress* progress;

    QVector<MapleAction> actions;

    QListWidget* unfinishedList;
    QMap<QString, MapleAction> unfinished;

    QListWidget* finishedList;
    QMap<QString, MapleAction> finished;
};

#endif // TRACKERWIDGET_H
