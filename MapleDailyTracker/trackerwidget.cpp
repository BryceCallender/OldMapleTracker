#include "mapleactiondialog.h"
#include "trackerwidget.h"
#include "ui_trackerwidget.h"

#include <QDebug>

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

    load();

    addAction = new QAction("Add", this);
    deleteAction = new QAction("Delete", this);
    editAction = new QAction("Edit", this);

    connect(addAction, &QAction::triggered, this, &TrackerWidget::addMapleAction);
    connect(editAction, &QAction::triggered, this, &TrackerWidget::triggerEditAction);
    connect(deleteAction, &QAction::triggered, this, &TrackerWidget::triggerDeleteAction);

    unfinishedList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(unfinishedList, &QListWidget::customContextMenuRequested, this, &TrackerWidget::provideContextMenuUnfinished);
    unfinishedList->addActions({ addAction });

    finishedList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(finishedList, &QListWidget::customContextMenuRequested, this, &TrackerWidget::provideContextMenuFinished);
    finishedList->addActions({ addAction });

    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->addButton, &QPushButton::clicked, this, &TrackerWidget::addMapleAction);
    connect(unfinishedList, &QListWidget::itemChanged, this, &TrackerWidget::moveItem);
    connect(finishedList, &QListWidget::itemChanged, this, &TrackerWidget::moveItem);
    connect(this, &TrackerWidget::updateProgress, progress, &Progress::updateProgress);
    connect(ui->orderButton, &QPushButton::clicked, this, &TrackerWidget::orderMode);
    connect(ui->finalizeButton, &QPushButton::clicked, this, &TrackerWidget::listMode);
}

void TrackerWidget::resetActions()
{
    for(int row = 0; row < finishedList->count(); row++)
    {
         QListWidgetItem* item = finishedList->takeItem(row);
         item->setCheckState(Qt::Unchecked);
         unfinishedList->addItem(item);
    }

    emit updateProgress();
}

void TrackerWidget::reload()
{
    unfinishedList->clear();
    finishedList->clear();

    load();

    emit updateProgress();
}

void TrackerWidget::load()
{
    for (MapleAction& action: actions)
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

    unfinishedList->sortItems();
}

void TrackerWidget::orderMode()
{
    ui->orderWidget->clear();

    for (MapleAction& action: actions)
    {
        ui->orderWidget->addItem(new MapleActionListWidgetItem(action, ui->orderWidget));
    }

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void TrackerWidget::listMode()
{
    QVector<MapleAction> actions;

    for (int i = 0; i < ui->orderWidget->count(); ++i)
    {
        MapleActionListWidgetItem* item = dynamic_cast<MapleActionListWidgetItem*>(ui->orderWidget->item(i));

        if (item)
        {
            MapleAction& action = item->getAction();
            action.order = i + 1;
            actions.push_back(action);
        }
    }

    this->actions = actions;
    reload();

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void TrackerWidget::triggerEditAction()
{
    QListWidgetItem* selectedItem;

    if (unfinishedList->selectedItems().size() > 0)
    {
        // Get curent item on selected row
        selectedItem = unfinishedList->item(unfinishedList->currentRow());
    }
    else
    {
        selectedItem = finishedList->item(finishedList->currentRow());
    }

    MapleActionListWidgetItem* actionItem = dynamic_cast<MapleActionListWidgetItem*>(selectedItem);

    if (actionItem)
    {
        triggerActionDialog(&actionItem->getAction());
    }
}

void TrackerWidget::triggerDeleteAction()
{
    // If multiple selection is on, we need to erase all selected items
    for (int i = 0; i < unfinishedList->selectedItems().size(); ++i)
    {
        // Get curent item on selected row
        QListWidgetItem *item = unfinishedList->takeItem(unfinishedList->currentRow());

        // And remove it
        this->actions.removeIf([&item](const MapleAction& action) {
            return item->text() == action.name;
        });

        emit updateProgress();

        delete item;
    }


    // If multiple selection is on, we need to erase all selected items
    for (int i = 0; i < finishedList->selectedItems().size(); ++i)
    {
        // Get curent item on selected row
        QListWidgetItem *item = finishedList->takeItem(finishedList->currentRow());

        // And remove it
        this->actions.removeIf([&item](const MapleAction& action) {
            return item->text() == action.name;
        });

        emit updateProgress();

        delete item;
    }
}

TrackerWidget::~TrackerWidget()
{
    delete ui;
}

void TrackerWidget::addMapleAction()
{
    triggerActionDialog();
}

void TrackerWidget::addToUnfinishedListWidget(MapleAction& action)
{
    action.order = actions.length() + 1;
    actions.push_back(action);
    loadActionTo(unfinishedList, action);
}

void TrackerWidget::moveItem(QListWidgetItem* item)
{
    if (item->checkState() == Qt::Checked)
    {
        QListWidgetItem* taken = unfinishedList->takeItem(unfinishedList->row(item));
        finishedList->addItem(taken);
    }
    else
    {
        QListWidgetItem* taken = finishedList->takeItem(finishedList->row(item));
        unfinishedList->addItem(taken);
        unfinishedList->sortItems();
    }

    MapleActionListWidgetItem* actionItem = dynamic_cast<MapleActionListWidgetItem*>(item);

    if (actionItem)
    {
        actionItem->getAction().done = item->checkState();
    }

    emit updateProgress();
}

void TrackerWidget::provideContextMenuUnfinished(const QPoint& point)
{
    provideContextMenu(unfinishedList, point);
}

void TrackerWidget::provideContextMenuFinished(const QPoint &point)
{
    provideContextMenu(finishedList, point);
}

void TrackerWidget::provideContextMenu(QListWidget *widget, const QPoint &point)
{
    QPoint globalPos = widget->mapToGlobal(point);
    QListWidgetItem* test = widget->item(widget->indexAt(point).row());
    MapleActionListWidgetItem* actionItem = dynamic_cast<MapleActionListWidgetItem*>(test);

    QMenu myMenu;
    myMenu.addAction(addAction);

    if (actionItem)
    {
        myMenu.addAction(editAction);
        myMenu.addAction(deleteAction);
    }

    myMenu.exec(globalPos);
}

void TrackerWidget::loadActionTo(QListWidget* widget, MapleAction& action)
{
    QListWidgetItem* item = new MapleActionListWidgetItem(action, widget);
    item->setCheckState(action.done ? Qt::Checked : Qt::Unchecked);

    widget->addItem(item);
}

void TrackerWidget::triggerActionDialog(MapleAction *action)
{
    MapleActionDialog* dialog = new MapleActionDialog(actions, action, this);
    connect(dialog, &MapleActionDialog::actionConfirmed, this, &TrackerWidget::addToUnfinishedListWidget);
    dialog->exec();

    unfinishedList->clearSelection();
    finishedList->clearSelection();
}
