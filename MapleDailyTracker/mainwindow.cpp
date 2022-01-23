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

    resetChecking();
    ui->serverTime->setText(QDateTime::currentDateTimeUtc().toString("ddd MMMM d hh:mm:ss AP"));

    timer = new QTimer(this);
    timer->setInterval(1000 * 60);
    timer->callOnTimeout(this, &MainWindow::resetChecking);
    timer->start();

    QTimer* currentServerTimer = new QTimer(this);
    currentServerTimer->setInterval(1000);
    currentServerTimer->callOnTimeout([this]() {  ui->serverTime->setText(QDateTime::currentDateTimeUtc().toString("ddd MMMM d hh:mm:ss AP")); });
    currentServerTimer->start();

    // AUTO SAVE FUNCTIONALITY
    loadContents();

    QTimer* autosaveTimer = new QTimer(this);
    autosaveTimer->setInterval(5000);
    autosaveTimer->callOnTimeout([this]() {
        FileManager* instance = FileManager::getInstance();
        instance->saveData(FileManager::autosaveFile, resetChecker, trackerTabWidget->getCharactersFromTabs() );
    });
    autosaveTimer->start();

    trackerTabWidget = ui->tabWidget;

    Progress* progress = ui->progressContents;

    trackerTabWidget->setProgressReference(progress);

    checkForExpiredResets(saveData);

    if (!saveData.characters.isEmpty())
    {
        trackerTabWidget->loadTabs(saveData);
    }
    else
    {
        FileManager::closedWelcome = false;
    }
}

void MainWindow::resetChecking()
{
    QDateTime dailyResetTime = resetChecker.timeTillDailyReset();
    QDateTime weeklyResetTime = resetChecker.timeTillWeeklyReset();
    QDateTime weeklyMondayResetTime = resetChecker.timeTillWeeklyReset(Qt::Monday);

    ui->dailyResetLabel->setText(ResetChecker::resetToLabel(dailyResetTime));
    ui->wedWeeklyResetLabel->setText(ResetChecker::resetToLabel(weeklyResetTime));
    ui->monWeeklyResetLabel->setText(ResetChecker::resetToLabel(weeklyMondayResetTime));

    for (Character* character: saveData.characters)
    {
        if (resetChecker.hasReset(dailyResetTime))
        {
            character->resetDailies();
            trackerTabWidget->actionsReset("Daily");
        }

        if (resetChecker.hasReset(weeklyResetTime))
        {
            character->resetWedWeeklies();
            trackerTabWidget->actionsReset("WedWeekly");
        }

        if (resetChecker.hasReset(weeklyMondayResetTime))
        {
            character->resetMonWeeklies();
            trackerTabWidget->actionsReset("MonWeekly");
        }

        // check incase they expire as the application is running
        if (character->removeExpiredActions())
        {
            trackerTabWidget->reloadTabs();
        }
    }
}

void MainWindow::checkForExpiredResets(SaveData& saveData)
{
    for (Character* character: saveData.characters)
    {
        if (resetChecker.hasReset(saveData.nextDailyReset))
        {
            character->resetDailies();
        }

        if (resetChecker.hasReset(saveData.nextWedWeeklyReset))
        {
            character->resetWedWeeklies();
        }

        if (resetChecker.hasReset(saveData.nextMonWeeklyReset))
        {
            character->resetMonWeeklies();
        }

        character->removeExpiredActions();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

    FileManager* instance = FileManager::getInstance();
    instance->saveData(FileManager::saveFile, resetChecker, trackerTabWidget->getCharactersFromTabs());
    instance->clearAutoSave();
}

void MainWindow::loadContents()
{
    QFile file(FileManager::autosaveFile);
    FileManager* instance = FileManager::getInstance();

    // Application crashed / closed without properly saving
    if (file.size() > 0)
    {
        saveData = instance->loadData(FileManager::autosaveFile);
    }
    else
    {
        saveData = instance->loadData(FileManager::saveFile);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Character_triggered()
{
    CharacterDialog* newCharDialog = new CharacterDialog(this);
    connect(newCharDialog, &CharacterDialog::newCharacter, trackerTabWidget, &TrackerTabWidget::addCharacterTab);
    newCharDialog->exec();
}

