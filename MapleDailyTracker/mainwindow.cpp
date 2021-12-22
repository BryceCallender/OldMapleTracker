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

    QTime dailyResetTime = dateChecker.timeTillDailyReset();
    QTime weeklyResetTime = dateChecker.timeTillWeeklyReset();

    qDebug() << timeToLabel(dailyResetTime);
    qDebug() << timeToLabel(weeklyResetTime);
}

QString MainWindow::timeToLabel(QTime time)
{
    QString label;

    if (time.hour() > 0)
    {
        label.append(QString::number(time.hour()) + "h");
    }

    if (time.minute() > 0)
    {
        label.append(QString::number(time.minute()) + "m");
    }

    if (time.second() > 0)
    {
        label.append(QString::number(time.second()) + "s");
    }

    return label;
}

MainWindow::~MainWindow()
{
    delete ui;
}
