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
    for (Character& character: characters)
    {
        ProgressContent* progressContent = new ProgressContent(character, this);
        layout->addWidget(progressContent);
        progress.push_back(progressContent);
    }
}

void Progress::addCharacterProgress(Character& character)
{
    progress.push_back(new ProgressContent(character, this));
}

void Progress::removeCharacterProgress(int index)
{
    QWidget* widget = progress.takeAt(index);
    layout->removeWidget(widget);
    delete widget;
}

Progress::~Progress()
{
    delete ui;
}
