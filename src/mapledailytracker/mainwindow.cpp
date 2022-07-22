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

    logger = Logger::getLogger();

    QSettings settings;
    if (settings.contains("ui/geometry"))
    {
        setGeometry(settings.value("ui/geometry").toRect());
    }

    ui->serverTime->setText(QDateTime::currentDateTimeUtc().toString("ddd MMMM d hh:mm:ss AP"));

    // Actions
    ui->addCharacter->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
    QAction* saveAction = new QAction("Save", this);
    saveAction->setShortcut(QKeySequence(QKeySequence::Save));

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->callOnTimeout(this, &MainWindow::resetChecking);
    timer->start();

    QTimer* currentServerTimer = new QTimer(this);
    currentServerTimer->setInterval(1000);
    currentServerTimer->callOnTimeout([this]() {  ui->serverTime->setText(QDateTime::currentDateTimeUtc().toString("ddd MMMM d hh:mm:ss AP")); });
    currentServerTimer->start();

    QTimer* updateTimerLabels = new QTimer(this);
    updateTimerLabels->setInterval(1000);
    updateTimerLabels->callOnTimeout(this, &MainWindow::updateTimerLabels);
    updateTimerLabels->start();

    // AUTO SAVE FUNCTIONALITY
    loadContents();
    resetChecking();
    checkForExpiredResets();

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

    if (!saveData.characters.isEmpty())
    {
        trackerTabWidget->loadTabs(saveData);
    }
    else
    {
        FileManager::closedWelcome = false;
    }

    connect(progress, &Progress::clicked, trackerTabWidget, [this](int index) {
       trackerTabWidget->setCurrentIndex(index);
    });

    connect(ui->addCharacter, &QAction::triggered, this, &MainWindow::addCharacter);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveContents);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::openPreferences);
}

void MainWindow::resetChecking()
{
    QDateTime dailyResetTime = resetChecker.timeTillDailyReset();
    QDateTime weeklyResetTime = resetChecker.timeTillWeeklyReset();
    QDateTime weeklyMondayResetTime = resetChecker.timeTillWeeklyReset(Qt::Monday);

    for (Character* character: saveData.characters)
    {
        std::string characterName = character->getName().toStdString();
        if (resetChecker.hasReset(dailyResetTime))
        {
            logger->info("{}'s dailies has been reset", characterName);
            character->resetDailies();
            trackerTabWidget->actionsReset("Daily");
        }

        if (resetChecker.hasReset(weeklyResetTime))
        {
            logger->info("{}'s wednesday weeklies has been reset", characterName);
            character->resetWedWeeklies();
            trackerTabWidget->actionsReset("WedWeekly");
        }

        if (resetChecker.hasReset(weeklyMondayResetTime))
        {
            logger->info("{}'s monday weeklies has been reset", characterName);
            character->resetMonWeeklies();
            trackerTabWidget->actionsReset("MonWeekly");
        }

        // check incase they expire as the application is running
        if (character->removeExpiredActions())
        {
            logger->info("{}'s expired actions have been removed", characterName);
            trackerTabWidget->reloadTabs();
        }
    }
}

void MainWindow::updateTimerLabels()
{
    QDateTime dailyResetTime = resetChecker.timeTillDailyReset();
    QDateTime weeklyResetTime = resetChecker.timeTillWeeklyReset();
    QDateTime weeklyMondayResetTime = resetChecker.timeTillWeeklyReset(Qt::Monday);

    ui->dailyResetLabel->setText(ResetChecker::resetToLabel(dailyResetTime));
    ui->wedWeeklyResetLabel->setText(ResetChecker::resetToLabel(weeklyResetTime));
    ui->monWeeklyResetLabel->setText(ResetChecker::resetToLabel(weeklyMondayResetTime));
}

void MainWindow::checkForExpiredResets()
{
    QDateTime now = QDateTime::currentDateTimeUtc();

    for (Character* character: saveData.characters)
    {
        std::string characterName = character->getName().toStdString();

        if ((saveData.nextDailyReset.isValid() && resetChecker.hasReset(saveData.nextDailyReset)) || now > saveData.nextDailyReset)
        {
            logger->info("{}'s dailies has been reset", characterName);
            character->resetDailies();
        }

        if ((saveData.nextWedWeeklyReset.isValid() && resetChecker.hasReset(saveData.nextWedWeeklyReset)) || now > saveData.nextWedWeeklyReset)
        {
            logger->info("{}'s wednesday weeklies has been reset", characterName);
            character->resetWedWeeklies();
        }

        if ((saveData.nextMonWeeklyReset.isValid() && resetChecker.hasReset(saveData.nextMonWeeklyReset)) || now > saveData.nextMonWeeklyReset)
        {
            logger->info("{}'s monday weeklies has been reset", characterName);
            character->resetMonWeeklies();
        }

        if (character->removeExpiredActions())
        {
            logger->info("{}'s expired actions have been removed", characterName);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

    saveContents();
}

void MainWindow::loadContents()
{
    QFile file(FileManager::autosaveFile);
    FileManager* instance = FileManager::getInstance();

    // Application crashed / closed without properly saving
    if (file.size() > 0)
    {
        logger->info("Loading autosave...");
        saveData = instance->loadData(FileManager::autosaveFile);
    }
    else
    {
        logger->info("Loading save file...");
        saveData = instance->loadData(FileManager::saveFile);
    }
}

void MainWindow::saveContents()
{
    FileManager* instance = FileManager::getInstance();
    logger->info("Closing application and saving contents...");
    instance->saveData(FileManager::saveFile, resetChecker, trackerTabWidget->getCharactersFromTabs());
    instance->clearAutoSave();

    QSettings settings;
    settings.setValue("ui/geometry", this->geometry());
}

void MainWindow::openPreferences()
{
    Preferences* preferencesDialog = new Preferences(this);
    preferencesDialog->exec();
}

void MainWindow::addCharacter()
{
    CharacterDialog* newCharDialog = new CharacterDialog(trackerTabWidget->getCharactersFromTabs(), this);
    connect(newCharDialog, &CharacterDialog::newCharacter, trackerTabWidget, &TrackerTabWidget::addCharacterTab);
    connect(newCharDialog, &CharacterDialog::cloneCharacter, trackerTabWidget, &TrackerTabWidget::cloneCharacterTab);
    newCharDialog->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
