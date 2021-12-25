#include "trackertabwidget.h"
#include "ui_trackertabwidget.h"

TrackerTabWidget::TrackerTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TrackerTabWidget)
{
    ui->setupUi(this);
}

void TrackerTabWidget::loadTabs(SaveData saveData)
{
    clear();

    for (Character character : saveData.characters)
    {
        TrackerTabContent* content = new TrackerTabContent(this);
        content->setCharacter(character);
        addTab(content, character.getName());
        tabs.push_back(content);
    }
}

QVector<Character> TrackerTabWidget::getCharactersFromTabs()
{
    QVector<Character> characters;
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

void TrackerTabWidget::addCharacterTab(QString name)
{
    TrackerTabContent* content = new TrackerTabContent(this);
    Character character;
    character.setName(name);

    content->setCharacter(character);
    addTab(content, name);
    tabs.push_back(content);
}
