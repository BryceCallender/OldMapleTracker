#include "progress.h"
#include "ui_progress.h"

Progress::Progress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Progress)
{
    ui->setupUi(this);
    layout = ui->progressLayout->layout();
    layout->setAlignment(Qt::AlignTop);
}

void Progress::addCharacterProgress(Character* character)
{
    ProgressContent* progressContent = new ProgressContent(character, this);
    layout->addWidget(progressContent);
    progress.push_back(progressContent);

    connect(progressContent, &ProgressContent::clicked, this, &Progress::progressContentClicked);
}

void Progress::removeCharacterProgress(int index)
{
    QWidget* widget = progress.takeAt(index);
    layout->removeWidget(widget);
    delete widget;
}

void Progress::scrollToProgress(int index)
{
    if (progress.size() <= index || index < 0)
        return;

    ui->scrollArea->ensureWidgetVisible(progress[index]);
}

void Progress::updateProgress()
{
    for (ProgressContent* pc: progress)
    {
        pc->loadProgressBars();
    }
}

void Progress::progressContentClicked(Character* character)
{
    int index = 0;
    bool found = false;
    ProgressContent* pc = nullptr;

    do
    {
        pc = progress[index];
        if (pc->getCharacter()->getName() == character->getName())
        {
            found = true;
            emit clicked(index);
        }
        index++;
    } while(!found);
}

Progress::~Progress()
{
    delete ui;
}
