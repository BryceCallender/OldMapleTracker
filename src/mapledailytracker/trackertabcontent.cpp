#include "trackertabcontent.h"
#include "ui_trackertabcontent.h"

TrackerTabContent::TrackerTabContent(Character* character, Progress* progress, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackerTabContent)
{
    ui->setupUi(this);

    this->progress = progress;
    this->character = character;

    progress->addCharacterProgress(character);

    TrackerWidget* daily = new TrackerWidget("Dailies", character->getDailies(), progress, this);
    TrackerWidget* wedWeekly = new TrackerWidget("Wed Weeklies", character->getWedWeeklies(), progress, this);
    TrackerWidget* monWeekly = new TrackerWidget("Mon Weeklies", character->getMonWeeklies(), progress, this);

    trackers.insert(ActionType::Daily, daily);
    trackers.insert(ActionType::WedWeekly, wedWeekly);
    trackers.insert(ActionType::MonWeekly, monWeekly);

    ui->dailiesBox->layout()->addWidget(daily);
    ui->wedWeekliesBox->layout()->addWidget(wedWeekly);
    ui->monWeekliesBox->layout()->addWidget(monWeekly);

    connect(ui->dailiesBox, &QGroupBox::toggled, this, [=](bool isVisible) {
        toggleContent(daily, ActionType::Daily, isVisible);
    });

    connect(ui->wedWeekliesBox, &QGroupBox::toggled, this, [=](bool isVisible) {
        toggleContent(wedWeekly, ActionType::WedWeekly, isVisible);
    });

    connect(ui->monWeekliesBox, &QGroupBox::toggled, this, [=](bool isVisible) {
        toggleContent(monWeekly, ActionType::MonWeekly, isVisible);
    });

    connect(this, &TrackerTabContent::toggleProgressBar, progress, &Progress::progressBarToggled);
}

Character* TrackerTabContent::getCharacter()
{
    return character;
}

void TrackerTabContent::actionsReset(ActionType type)
{
    trackers[type]->resetActions();
}

void TrackerTabContent::reloadTabs()
{
    for (TrackerWidget* tracker : qAsConst(trackers))
    {
        tracker->reload();
    }
}

void TrackerTabContent::toggleContent(TrackerWidget* widget, ActionType actionType, bool isVisible)
{
    widget->toggleVisibility(isVisible);
    emit toggleProgressBar(actionType, isVisible);
}

TrackerTabContent::~TrackerTabContent()
{
    delete ui;
}
