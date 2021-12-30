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

    for (const MapleAction& action : actions)
    {
        if (action.done)
        {

        }
        else
        {

        }
    }

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
    this->actions.push_back(action);

    //Item setup
    QListWidgetItem* item = new QListWidgetItem("testing", unfinishedList);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    item->setCheckState(Qt::Unchecked);

    //Store the data associated with the item
    QVariant data;
    data.setValue(action);
    item->setData(Qt::UserRole, data);

    connect(unfinishedList, &QListWidget::itemChanged, this, &TrackerWidget::moveToFinished);

    unfinishedList->addItem(item);
}

void TrackerWidget::moveToFinished(QListWidgetItem *item)
{
    if (item->checkState() == Qt::Checked)
    {
        MapleAction action = item->data(Qt::UserRole).value<MapleAction>();
        action.done = Qt::Checked;
        //item = unfinishedList->takeItem(unfinishedList->currentRow());
        //finishedList->addItem(item);
        emit updateProgress();
    }
}
