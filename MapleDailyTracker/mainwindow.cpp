#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDateTime dailyResetTime = resetChecker.timeTillDailyReset();
    QDateTime weeklyResetTime = resetChecker.timeTillWeeklyReset();
    QDateTime weeklyMondayResetTime = resetChecker.timeTillWeeklyReset(Qt::Monday);

    qDebug() << "Daily reset is in:" << ResetChecker::resetToLabel(dailyResetTime);
    qDebug() << "Weekly reset is in:" << ResetChecker::resetToLabel(weeklyResetTime);
    qDebug() << "Monday Weekly reset is in:" << ResetChecker::resetToLabel(weeklyMondayResetTime);
}

MainWindow::~MainWindow()
{
    delete ui;
}
