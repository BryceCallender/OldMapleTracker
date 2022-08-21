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
#include "logger.h"

namespace Ui {
class TrackerWidget;
}

class TrackerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrackerWidget(const QString& section, QVector<MapleAction>& actions, Progress* progress, QWidget *parent = nullptr);
    void resetActions();
    void reload();
    void load();
    void orderMode();
    void listMode();
    void triggerEditAction();
    void triggerDeleteAction();
    void toggleVisibility(bool isOn);
    void provideContextMenu(QListWidget* widget, const QPoint& point);
    std::string actionsToList(QVector<MapleAction>& actions);
    ~TrackerWidget();
private slots:
    void addMapleAction();
    void addToUnfinishedListWidget(MapleAction& action);
    void moveItem(QListWidgetItem *item);
    void provideContextMenuUnfinished(const QPoint& point);
    void provideContextMenuFinished(const QPoint& point);
    void unselectUnfinished();
    void unselectFinished();
    void rowsMoved(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row);
signals:
    void updateProgress();
private:
    void loadActionTo(QListWidget* widget, MapleAction& action) const;
    void triggerActionDialog(MapleAction* action = nullptr);
    QVector<MapleAction>& actions;
    QString section;

    Ui::TrackerWidget *ui;
    Progress* progress;

    QListWidget* unfinishedList;
    QListWidget* finishedList;

    QAction* addAction;
    QAction* deleteAction;
    QAction* editAction;

    std::shared_ptr<spdlog::logger> logger;
};

#endif // TRACKERWIDGET_H
