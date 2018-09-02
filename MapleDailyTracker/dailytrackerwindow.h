#ifndef DAILYTRACKERWINDOW_H
#define DAILYTRACKERWINDOW_H

#include <QTabWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QCloseEvent>

#include "mapletabwidget.h"
#include "datechecker.h"

namespace Ui {
class DailyTrackerWindow;
}

class DailyTrackerWindow : public QTabWidget
{
    Q_OBJECT

public:
    explicit DailyTrackerWindow(QWidget *parent = nullptr);
    void loadTabs();
    QVector<QString> getNamesForTabs();
    void resetDailies();
    void resetWeeklies();
    void closeEvent(QCloseEvent *event);
    bool saveData();
    bool loadData();
    ~DailyTrackerWindow();

private:
    QVector<MapleTabWidget*> tabs;
    DateChecker* dateChecker;
    Ui::DailyTrackerWindow *ui;
};

#endif // DAILYTRACKERWINDOW_H
