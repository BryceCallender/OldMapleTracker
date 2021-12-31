#include "mapleactiondialog.h"
#include "trackerwidget.h"
#include "ui_trackerwidget.h"

TrackerWidget::TrackerWidget(QVector<MapleAction> &actions, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackerWidget)
{
    ui->setupUi(this);

    this->actions = actions;

    unfinishedList = ui->unfinishedListWidget;
    finishedList = ui->finishedListWidget;

    unfinishedList->setMinimumHeight(200);
    finishedList->setMinimumHeight(200);

    QAction* deleteAction = new QAction("Delete", this);

    unfinishedList->setContextMenuPolicy(Qt::ActionsContextMenu);
    unfinishedList->addActions({ deleteAction });

    finishedList->setContextMenuPolicy(Qt::ActionsContextMenu);
    finishedList->addActions({ deleteAction });

    connect(ui->addButton, &QPushButton::clicked, this, &TrackerWidget::addMapleAction);
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

    connect(unfinishedList, &QListWidget::itemChanged, this, &TrackerWidget::moveToFinished);

    unfinishedList->addItem(item);
}

void TrackerWidget::moveToFinished(QListWidgetItem *item)
{
    if (item->checkState() == Qt::Checked)
    {
        QListWidgetItem* taken = unfinishedList->takeItem(unfinishedList->currentRow());
        finishedList->addItem(taken);
    }

    emit updateProgress();
}
