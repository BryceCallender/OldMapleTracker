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

    trackers.insert("Daily", daily);
    trackers.insert("WedWeekly", wedWeekly);
    trackers.insert("MonWeekly", monWeekly);

    ui->dailiesBox->layout()->addWidget(daily);
    ui->wedWeekliesBox->layout()->addWidget(wedWeekly);
    ui->monWeekliesBox->layout()->addWidget(monWeekly);
}

Character* TrackerTabContent::getCharacter()
{
    return character;
}

void TrackerTabContent::actionsReset(const QString& type)
{
    trackers[type]->resetActions();
}

void TrackerTabContent::reloadTabs()
{
    for (const TrackerWidget* tracker : trackers)
    {
        tracker->reload();
    }
}

TrackerTabContent::~TrackerTabContent()
{
    delete ui;
}
