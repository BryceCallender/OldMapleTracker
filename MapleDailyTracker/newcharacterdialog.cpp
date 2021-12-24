#include "newcharacterdialog.h"
#include "ui_newcharacterdialog.h"

NewCharacterDialog::NewCharacterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCharacterDialog)
{
    ui->setupUi(this);

    setWindowTitle("New Character");

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

NewCharacterDialog::~NewCharacterDialog()
{
    delete ui;
}

void NewCharacterDialog::on_buttonBox_accepted()
{
    emit newCharacter(ui->lineEdit->text());
}


void NewCharacterDialog::on_lineEdit_textChanged(const QString &name)
{
    if (name.length() > 0)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }
}

