#include "characterdialog.h"
#include "ui_characterdialog.h"

CharacterDialog::CharacterDialog(QVector<Character*> characters, QWidget *parent) :
    QDialog(parent),
    characters(characters),
    ui(new Ui::CharacterDialog)
{
    ui->setupUi(this);

    setWindowTitle("New Character");

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);

    if (characters.length() > 0)
    {
        showCloneCharacter();
        ui->charactersBox->addItem("None");
        for (const Character* character: characters)
        {
            ui->charactersBox->addItem(character->getName());
        }
    }
    else
    {
        hideCloneCharacter();
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CharacterDialog::characterConfirmed);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &CharacterDialog::characterNameChanged);
    connect(ui->charactersBox, &QComboBox::currentIndexChanged, this, &CharacterDialog::characterSelectionChanged);
}

void CharacterDialog::hideCloneCharacter()
{
    ui->inherit->hide();
    ui->charactersBox->hide();
}

void CharacterDialog::showCloneCharacter()
{
    ui->inherit->show();
    ui->charactersBox->show();
}

void CharacterDialog::parseTree()
{
    QTreeWidgetItem* root = ui->treeWidget->invisibleRootItem();

    if (root->childCount() == 0)
    {
        return;
    }

    QTreeWidgetItem* characterRoot = root->child(0);

    if (characterRoot->childCount() == 3)
    {
        QTreeWidgetItem* dailyRoot = characterRoot->child(0);
        QTreeWidgetItem* wedWeeklyRoot = characterRoot->child(1);
        QTreeWidgetItem* monWeeklyRoot = characterRoot->child(2);

        character->setDailies(extractActions(dailyRoot));
        character->setWedWeeklies(extractActions(wedWeeklyRoot));
        character->setMonWeeklies(extractActions(monWeeklyRoot));
    }
}

CharacterDialog::~CharacterDialog()
{
    delete ui;
}

void CharacterDialog::characterConfirmed()
{
    if (characters.length() > 0 && ui->charactersBox->currentText() != "None")
    {
        parseTree();

        emit cloneCharacter(character, ui->lineEdit->text());
    }
    else
    {
        emit newCharacter(ui->lineEdit->text());
    }
}

void CharacterDialog::characterNameChanged(const QString &name)
{
    if (name.length() > 0)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }
}

void CharacterDialog::characterSelectionChanged(const int index)
{
    character = characters.at(index - 1)->clone();

    QTreeWidgetItem* root = new QTreeWidgetItem();
    root->setText(0, character->getName());

    ui->treeWidget->clear();
    ui->treeWidget->addTopLevelItem(root);

    QTreeWidgetItem* dailies = new QTreeWidgetItem({"Dailies"}, QTreeWidgetItem::Type);
    QTreeWidgetItem* wedWeeklies = new QTreeWidgetItem({"Wed Weeklies"}, QTreeWidgetItem::Type);
    QTreeWidgetItem* monWeeklies = new QTreeWidgetItem({"Mon Weeklies"}, QTreeWidgetItem::Type);

    dailies->setFlags(dailies->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsAutoTristate);
    dailies->setCheckState(0, Qt::Checked);

    for (const MapleAction& action: character->getDailies())
    {
        addWidgetItem(dailies, action);
    }

    wedWeeklies->setFlags(wedWeeklies->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsAutoTristate);
    wedWeeklies->setCheckState(0, Qt::Checked);

    for (const MapleAction& action: character->getWedWeeklies())
    {
        addWidgetItem(wedWeeklies, action);
    }

    monWeeklies->setFlags(monWeeklies->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsAutoTristate);
    monWeeklies->setCheckState(0, Qt::Checked);

    for (const MapleAction& action: character->getMonWeeklies())
    {
        addWidgetItem(monWeeklies, action);
    }

    root->addChildren({ dailies, wedWeeklies, monWeeklies });

    parseTree();
    ui->treeWidget->expandItem(root);
}

void CharacterDialog::addWidgetItem(QTreeWidgetItem* parent, const MapleAction& action)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, action.name);
    item->setCheckState(0, Qt::Checked);

    QVariant qvar;
    qvar.setValue(action);
    item->setData(0, Qt::UserRole, qvar);

    parent->addChild(item);
}

QVector<MapleAction> CharacterDialog::extractActions(QTreeWidgetItem *parent)
{
    QVector<MapleAction> actions;

    for (int i = 0; i < parent->childCount(); i++)
    {
        QTreeWidgetItem* child = parent->child(i);

        if (child->checkState(0) == Qt::Checked)
        {
            MapleAction action = child->data(0, Qt::UserRole).value<MapleAction>();
            actions.push_back(action);
        }
    }

    return actions;
}
