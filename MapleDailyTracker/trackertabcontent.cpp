#include "trackertabcontent.h"
#include "ui_trackertabcontent.h"

TrackerTabContent::TrackerTabContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackerTabContent)
{
    ui->setupUi(this);
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
