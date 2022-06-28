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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void resetChecking();
    void checkForExpiredResets(SaveData &saveData);
    void closeEvent(QCloseEvent* event);
    void loadContents();
    void saveContents();
    void addCharacter();
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    ResetChecker resetChecker;
    QTimer* timer;

    SaveData saveData;
    Progress* progress;
    TrackerTabWidget* trackerTabWidget;
};

#endif // MAINWINDOW_H
