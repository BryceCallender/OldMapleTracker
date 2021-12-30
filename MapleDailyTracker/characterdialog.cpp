#include "characterdialog.h"
#include "ui_characterdialog.h"

CharacterDialog::CharacterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterDialog)
{
    ui->setupUi(this);

    setWindowTitle("New Character");

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CharacterDialog::characterConfirmed);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &CharacterDialog::characterNameChanged);
}

CharacterDialog::~CharacterDialog()
{
    delete ui;
}

void CharacterDialog::characterConfirmed()
{
    emit newCharacter(ui->lineEdit->text());
}

void CharacterDialog::characterNameChanged(const QString &name)
{
    if (name.length() > 0)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }
}

