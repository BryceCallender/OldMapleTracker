#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTimer>

#include "filemanager.h"
#include "resetchecker.h"
#include "characterdialog.h"
#include "trackertabwidget.h"
#include "progress.h"
#include "preferences.h"
#include "logger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void resetChecking();
    void updateTimerLabels();
    void checkForExpiredResets(SaveData &saveData);
    void closeEvent(QCloseEvent* event);
    void loadContents();
    void openPreferences();
    ~MainWindow();

private slots:
    void on_actionAdd_Character_triggered();

private:
    Ui::MainWindow *ui;
    ResetChecker resetChecker;
    QTimer* timer;

    SaveData saveData;
    Progress* progress;
    TrackerTabWidget* trackerTabWidget;

    std::shared_ptr<spdlog::logger> logger;
};

#endif // MAINWINDOW_H
