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

CharacterDialog::~CharacterDialog()
{
    delete ui;
}

void CharacterDialog::characterConfirmed()
{
    if (ui->charactersBox->currentText() != "None")
    {
        QVector<Character*>::iterator it = std::find_if(characters.begin(), characters.end(), [&] (const Character* c) { return c->getName() == ui->charactersBox->currentText(); });
        emit cloneCharacter(*it, ui->lineEdit->text());
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

