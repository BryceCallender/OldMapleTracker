#include "trackertabcontent.h"
#include "ui_trackertabcontent.h"

TrackerTabContent::TrackerTabContent(Progress* progress, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackerTabContent)
{
    ui->setupUi(this);

    this->progress = progress;

    ui->dailiesBox->layout()->addWidget(new TrackerWidget(character.getDailies(), progress, this));
    ui->wedWeekliesBox->layout()->addWidget(new TrackerWidget(character.getWedWeeklies(), progress, this));
    ui->monWeekliesBox->layout()->addWidget(new TrackerWidget(character.getMonWeeklies(), progress, this));

}

Character& TrackerTabContent::getCharacter()
{
    return character;
}

void TrackerTabContent::setCharacter(Character& character)
{
    this->character = character;
}

TrackerTabContent::~TrackerTabContent()
{
    delete ui;
}
