#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "initilizationwindow.h"
#include "dailytrackerwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_beginTrackerButton_clicked();

private:
    Ui::MainWindow *ui;
    InitilizationWindow *initWindow;
    DailyTrackerWindow *trackerWindow;
};

#endif // MAINWINDOW_H
