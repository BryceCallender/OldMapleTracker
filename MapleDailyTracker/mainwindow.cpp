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

    calculateResets();

    timer = new QTimer(this);
    timer->setInterval(1000 * 60);
    timer->callOnTimeout(this, &MainWindow::calculateResets);
    timer->start();

    trackerTabWidget = ui->tabWidget;

    FileManager* instance = FileManager::getInstance();
    SaveData saveData = instance->loadData();

    if (!saveData.characters.isEmpty())
    {
        trackerTabWidget->loadTabs(saveData);
    }
}

void MainWindow::calculateResets()
{
    QDateTime dailyResetTime = resetChecker.timeTillDailyReset();
    QDateTime weeklyResetTime = resetChecker.timeTillWeeklyReset();
    QDateTime weeklyMondayResetTime = resetChecker.timeTillWeeklyReset(Qt::Monday);

    ui->dailyResetLabel->setText(ResetChecker::resetToLabel(dailyResetTime));
    ui->wedWeeklyResetLabel->setText(ResetChecker::resetToLabel(weeklyResetTime));
    ui->monWeeklyResetLabel->setText(ResetChecker::resetToLabel(weeklyMondayResetTime));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    FileManager* instance = FileManager::getInstance();
    instance->saveData(trackerTabWidget->getCharactersFromTabs());
    qDebug() << "Close event";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Character_triggered()
{
    newCharDialog = new NewCharacterDialog();
    newCharDialog->show();
}

