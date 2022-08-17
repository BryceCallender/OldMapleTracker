#include "progresscontent.h"
#include "ui_progresscontent.h"

ProgressContent::ProgressContent(Character* character, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressContent)
{
    ui->setupUi(this);

    this->character = character;

    ui->label->setText(character->getName());

    loadProgressBars();
}

void ProgressContent::loadProgressBars()
{
    QMap<ActionType, double> progressData = getProgressFromData();

    animateProgress(ui->dailyBar, progressData[ActionType::Daily]);
    animateProgress(ui->wedWeeklyBar, progressData[ActionType::WedWeekly]);
    animateProgress(ui->monWeeklyBar, progressData[ActionType::MonWeekly]);
}

Character *ProgressContent::getCharacter()
{
    return character;
}

QMap<ActionType, double> ProgressContent::getProgressFromData()
{
    QMap<ActionType, double> progressData;

    progressData.insert(ActionType::Daily, getProgressFromSet(character->getDailies()));
    progressData.insert(ActionType::WedWeekly, getProgressFromSet(character->getWedWeeklies()));
    progressData.insert(ActionType::MonWeekly, getProgressFromSet(character->getMonWeeklies()));

    return progressData;
}

void ProgressContent::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked(this->character);
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

    return numberOfDone == 0 ? 0 : (numberOfDone / (double)set.size()) * 100;
}

void ProgressContent::animateProgress(QProgressBar *progressBar, double value)
{
    QPropertyAnimation* animation = new QPropertyAnimation(progressBar, "value");
    animation->setDuration(250);
    animation->setStartValue(progressBar->value());
    animation->setEndValue(value);
    animation->start();
}

ProgressContent::~ProgressContent()
{
    delete ui;
}
