#include "mapleactiondialog.h"
#include "trackerwidget.h"
#include "ui_trackerwidget.h"

TrackerWidget::TrackerWidget(QVector<MapleAction>& actions, Progress* progress, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackerWidget)
{
    ui->setupUi(this);

    this->actions = actions;
    this->progress = progress;

    unfinishedList = ui->unfinishedListWidget;
    finishedList = ui->finishedListWidget;

    unfinishedList->setMinimumHeight(200);
    finishedList->setMinimumHeight(200);

//    QAction* deleteAction = new QAction("Delete", this);

//    unfinishedList->setContextMenuPolicy(Qt::ActionsContextMenu);
//    unfinishedList->addActions({ deleteAction });

//    finishedList->setContextMenuPolicy(Qt::ActionsContextMenu);
//    finishedList->addActions({ deleteAction });

    connect(ui->addButton, &QPushButton::clicked, this, &TrackerWidget::addMapleAction);
    connect(unfinishedList, &QListWidget::itemChanged, this, &TrackerWidget::moveItem);
    connect(finishedList, &QListWidget::itemChanged, this, &TrackerWidget::moveItem);
    connect(this, &TrackerWidget::updateProgress, progress, &Progress::updateProgress);
}

TrackerWidget::~TrackerWidget()
{
    delete ui;
}

void TrackerWidget::addMapleAction()
{
    MapleActionDialog* dialog = new MapleActionDialog(this);
    connect(dialog, &MapleActionDialog::actionConfirmed, this, &TrackerWidget::addToUnfinishedListWidget);
    dialog->exec();
}

void TrackerWidget::addToUnfinishedListWidget(MapleAction& action)
{
    actions.push_back(action);

    //Item setup
    QListWidgetItem* item = new QListWidgetItem(action.name, unfinishedList);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    item->setCheckState(Qt::Unchecked);

    unfinishedList->addItem(item);
}

void TrackerWidget::moveItem(QListWidgetItem *item)
{
    if (item->checkState() == Qt::Checked)
    {
        QListWidgetItem* taken = unfinishedList->takeItem(unfinishedList->currentRow());
        finishedList->addItem(taken);
    }
    else
    {
        QListWidgetItem* taken = finishedList->takeItem(finishedList->currentRow());
        unfinishedList->addItem(taken);
    }

    emit updateProgress();
}
