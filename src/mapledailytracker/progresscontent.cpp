#include "progresscontent.h"
#include "ui_progresscontent.h"

ProgressContent::ProgressContent(Character* character, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressContent)
{
    ui->setupUi(this);

    this->character = character;

    ui->label->setText(character->getName());

    progressBars.insert(ActionType::Daily, ui->dailyBar);
    progressBars.insert(ActionType::WedWeekly, ui->wedWeeklyBar);
    progressBars.insert(ActionType::MonWeekly, ui->monWeeklyBar);

    loadProgressBars();
}

void ProgressContent::loadProgressBars()
{
    QMap<ActionType, double> progressData = getProgressFromData();

    animateProgress(progressBars[ActionType::Daily], progressData[ActionType::Daily]);
    animateProgress(progressBars[ActionType::WedWeekly], progressData[ActionType::WedWeekly]);
    animateProgress(progressBars[ActionType::MonWeekly], progressData[ActionType::MonWeekly]);
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
    QPropertyAnimation* animation = new QPropertyAnimation(progressBar, "value", this);
    animation->setDuration(250);
    animation->setStartValue(progressBar->value());
    animation->setEndValue(value);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

ProgressContent::~ProgressContent()
{
    delete ui;
}

void ProgressContent::toggleProgressBar(ActionType actionType, bool isVisible)
{
    QGraphicsOpacityEffect* fadeEffect = new QGraphicsOpacityEffect(this);
    progressBars[actionType]->setGraphicsEffect(fadeEffect);
    progressBars[actionType]->setVisible(true);

    double startValue = 1.0 * !isVisible;
    double endValue = !isVisible ? 0.01 : 1.0;

    QPropertyAnimation* animation = new QPropertyAnimation(fadeEffect, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->start(QPropertyAnimation::DeleteWhenStopped);

    connect(animation, &QAbstractAnimation::finished, progressBars[actionType], [=]() {
        progressBars[actionType]->setVisible(isVisible);
    });
}
