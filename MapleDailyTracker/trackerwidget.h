#ifndef TRACKERWIDGET_H
#define TRACKERWIDGET_H

#include <QWidget>
#include <QVector>
#include <QListWidget>
#include <QAction>
#include <QMenu>
#include <algorithm>

#include "character.h"
#include "mapleaction.h"
#include "progress.h"
#include "mapleactionlistwidgetitem.h"
#include "orderactionwidget.h"

namespace Ui {
class TrackerWidget;
}

class TrackerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrackerWidget(QVector<MapleAction>& actions, Progress* progress, QWidget *parent = nullptr);
    void resetActions();
    void reload();
    void load();
    void orderMode();
    void listMode();
    void triggerEditAction();
    void triggerDeleteAction();
    void provideContextMenu(QListWidget* widget, const QPoint& point);
    ~TrackerWidget();
private slots:
    void addMapleAction();
    void addToUnfinishedListWidget(MapleAction& action);
    void moveItem(QListWidgetItem *item);
    void provideContextMenuUnfinished(const QPoint& point);
    void provideContextMenuFinished(const QPoint& point);
signals:
    void updateProgress();
private:
    void loadActionTo(QListWidget* widget, MapleAction& action);
    void triggerActionDialog(MapleAction* action = nullptr);
    QVector<MapleAction>& actions;

    Ui::TrackerWidget *ui;
    Progress* progress;

    QListWidget* unfinishedList;
    QListWidget* finishedList;

    QAction* addAction;
    QAction* deleteAction;
    QAction* editAction;
};

#endif // TRACKERWIDGET_H
