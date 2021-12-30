#include "trackertabcontent.h"
#include "ui_trackertabcontent.h"

TrackerTabContent::TrackerTabContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackerTabContent)
{
    ui->setupUi(this);

    ui->dailiesBox->layout()->addWidget(new TrackerWidget(character.getDailies(), this));
    ui->wedWeekliesBox->layout()->addWidget(new TrackerWidget(character.getWedWeeklies(), this));
    ui->monWeekliesBox->layout()->addWidget(new TrackerWidget(character.getMonWeeklies(), this));
}

void TrackerTabContent::addMapleAction(ActionType actionType, QString& action)
{
    MapleAction mapleAction;
    mapleAction.name = action;
    mapleAction.done = false;

    switch (actionType)
    {
        case ActionType::Daily: character.addDaily(mapleAction);
            break;
        case ActionType::WedWeekly: character.addWedWeekly(mapleAction);
            break;
        case ActionType::MonWeekly: character.addMonWeekly(mapleAction);
            break;
        default: break;
    }
}

Character TrackerTabContent::getCharacter()
{
    return character;
}

void TrackerTabContent::setCharacter(Character character)
{
    this->character = character;
}

TrackerTabContent::~TrackerTabContent()
{
    delete ui;
}
