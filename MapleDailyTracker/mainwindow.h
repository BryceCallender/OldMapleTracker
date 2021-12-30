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
    void calculateResets();
    void closeEvent(QCloseEvent* event);
    ~MainWindow();

private slots:
    void on_actionAdd_Character_triggered();

private:
    Ui::MainWindow *ui;
    ResetChecker resetChecker;
    QTimer* timer;

    Progress* progress;
    TrackerTabWidget* trackerTabWidget;
    CharacterDialog* newCharDialog;
};

#endif // MAINWINDOW_H
