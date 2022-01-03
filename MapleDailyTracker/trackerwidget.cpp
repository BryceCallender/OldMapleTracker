#include "mapleactiondialog.h"
#include "trackerwidget.h"
#include "ui_trackerwidget.h"

TrackerWidget::TrackerWidget(QVector<MapleAction>& actions, Progress* progress, QWidget *parent) :
    QWidget(parent),
    actions(actions),
    ui(new Ui::TrackerWidget)
{
    ui->setupUi(this);

    this->progress = progress;

    unfinishedList = ui->unfinishedListWidget;
    finishedList = ui->finishedListWidget;

    unfinishedList->setMinimumHeight(200);
    finishedList->setMinimumHeight(200);

    for (const MapleAction& action: actions)
    {
        if (action.done)
        {
            loadActionTo(finishedList, action);
        }
        else
        {
            loadActionTo(unfinishedList, action);
        }
    }

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
    MapleActionDialog* dialog = new MapleActionDialog(actions, this);
    connect(dialog, &MapleActionDialog::actionConfirmed, this, &TrackerWidget::addToUnfinishedListWidget);
    dialog->exec();
}

void TrackerWidget::addToUnfinishedListWidget(const MapleAction& action)
{
    actions.push_back(action);
    loadActionTo(unfinishedList, action);
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

    updateActionTo(item->text(), item->checkState());
    emit updateProgress();
}

void TrackerWidget::loadActionTo(QListWidget *widget, const MapleAction &action)
{
    QListWidgetItem* item = new QListWidgetItem(action.name, widget);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    item->setCheckState(action.done ? Qt::Checked : Qt::Unchecked);

    widget->addItem(item);
}

void TrackerWidget::updateActionTo(const QString& actionName, bool checked)
{
    for (MapleAction& action : actions)
    {
        if (action.name == actionName)
        {
            action.done = checked;
            return;
        }
    }
}
