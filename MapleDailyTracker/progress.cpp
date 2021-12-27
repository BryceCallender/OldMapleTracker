#include "progress.h"
#include "ui_progress.h"

Progress::Progress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Progress)
{
    ui->setupUi(this);
    layout = ui->progressLayout;
}

void Progress::load(QVector<Character> characters)
{
    for (const Character& character: characters)
    {
        addCharacterProgress(character);
    }
}

void Progress::addProgressBar(QString name, QMap<QString, double>& progressData)
{
    if (progressData.contains(name))
    {
        QProgressBar* progress = new QProgressBar();
        progress->setFixedWidth(150);
        progress->setTextVisible(true);
        progress->setValue(progressData[name]);
        layout->addWidget(progress);
    }
}

QMap<QString, double> Progress::getProgressFromData(const Character& character)
{
    QMap<QString, double> progressData;

    progressData.insert("dailies", getProgressFromSet(character.getDailies()));
    progressData.insert("wedWeeklies", getProgressFromSet(character.getWedWeeklies()));
    progressData.insert("monWeeklies", getProgressFromSet(character.getMonWeeklies()));

    return progressData;
}

void Progress::addCharacterProgress(const Character& character)
{
    QMap<QString, double> progressData = getProgressFromData(character);

    layout->addWidget(new QLabel(character.getName()));
    addProgressBar("dailies", progressData);
    addProgressBar("wedWeeklies", progressData);
    addProgressBar("monWeeklies", progressData);
}

double Progress::getProgressFromSet(const QVector<MapleAction>& set)
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

Progress::~Progress()
{
    delete ui;
}
