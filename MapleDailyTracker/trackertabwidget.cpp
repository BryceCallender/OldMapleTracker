#include "trackertabwidget.h"
#include "ui_trackertabwidget.h"

TrackerTabWidget::TrackerTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TrackerTabWidget)
{
    ui->setupUi(this);

    setMovable(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &TrackerTabWidget::tabCloseRequest);
    connect(this->tabBar(), &QTabBar::tabMoved, this, &TrackerTabWidget::tabMoved);
}

void TrackerTabWidget::setProgressReference(Progress* progress)
{
    this->progress = progress;
    connect(this, &TrackerTabWidget::characterRemoved, progress, &Progress::removeCharacterProgress);
    connect(this, &TrackerTabWidget::currentChanged, progress, &Progress::scrollToProgress);
}

void TrackerTabWidget::loadTabs(SaveData& saveData)
{
    clear();

    for (Character* character : saveData.characters)
    {
        TrackerTabContent* content = new TrackerTabContent(character, progress, this);
        addTab(content, character->getName());
        tabs.push_back(content);
    }
}

void TrackerTabWidget::reloadTabs()
{
    for (TrackerTabContent* tabContent: tabs)
    {
        tabContent->reloadTabs();
    }
}

void TrackerTabWidget::tabCloseRequest(int index)
{
    if (tabText(index).contains("Welcome"))
    {
        FileManager::closedWelcome = true;
    }
    else
    {
        int result = QMessageBox::warning(this, "Removing character", "Are you sure you want to remove? This will permenantly delete all data associated with it.", QMessageBox::Ok, QMessageBox::Cancel);
        if (result != QMessageBox::Ok)
        {
            return;
        }

        emit characterRemoved(index);

        tabs.removeAt(index);
    }

    removeTab(index);
}

void TrackerTabWidget::tabMoved(int from, int to)
{
    std::swap(tabs[from], tabs[to]);
}

void TrackerTabWidget::actionsReset(const QString &type)
{
    for (TrackerTabContent* tabContent: tabs)
    {
        tabContent->actionsReset(type);
    }
}

void TrackerTabWidget::addNewTab(Character *character, const QString &name)
{
    TrackerTabContent* content = new TrackerTabContent(character, progress, this);

    if (!FileManager::closedWelcome)
    {
        FileManager::closedWelcome = true;
        removeTab(0);
    }

    addTab(content, name);
    tabs.push_back(content);
}

QVector<Character*> TrackerTabWidget::getCharactersFromTabs()
{
    QVector<Character*> characters;
    for (TrackerTabContent* tabContent: tabs)
    {
        characters.push_back(tabContent->getCharacter());
    }

    return characters;
}

TrackerTabWidget::~TrackerTabWidget()
{
    delete ui;
}

void TrackerTabWidget::addCharacterTab(const QString &name)
{
    Character* character = new Character();
    character->setName(name);

    addNewTab(character, name);
}

void TrackerTabWidget::cloneCharacterTab(Character* clone, const QString &name)
{
    Character* character = clone->clone();
    character->setName(name);

    addNewTab(character, name);
}
