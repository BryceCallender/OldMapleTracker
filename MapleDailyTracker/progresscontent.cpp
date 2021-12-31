#include "progresscontent.h"
#include "ui_progresscontent.h"

ProgressContent::ProgressContent(Character &character, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressContent)
{
    ui->setupUi(this);

    this->character = character;

    ui->label->setText(character.getName());
}

void ProgressContent::loadProgressBars()
{

}

QMap<QString, double> ProgressContent::getProgressFromData(Character& character)
{
    QMap<QString, double> progressData;

    progressData.insert("dailies", getProgressFromSet(character.getDailies()));
    progressData.insert("wedWeeklies", getProgressFromSet(character.getWedWeeklies()));
    progressData.insert("monWeeklies", getProgressFromSet(character.getMonWeeklies()));

    return progressData;
}

double ProgressContent::getProgressFromSet(const QVector<MapleAction>& set)
{
    int numberOfDone = 0;

    for (const MapleAction& action : set)
    {
        if (action.done)
        {
            ++numberOfDone;
        }
    }

    return (numberOfDone / set.size()) * 100;
}


ProgressContent::~ProgressContent()
{
    delete ui;
}
