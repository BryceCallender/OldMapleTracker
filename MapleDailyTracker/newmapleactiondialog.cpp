#include "newmapleactiondialog.h"
#include "ui_newmapleactiondialog.h"

NewMapleActionDialog::NewMapleActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMapleActionDialog)
{
    ui->setupUi(this);
}

NewMapleActionDialog::~NewMapleActionDialog()
{
    delete ui;
}

void NewMapleActionDialog::on_checkBox_stateChanged(int state)
{
    if (state == Qt::Checked)
    {
        ui->expirationLabel->setEnabled(true);
        ui->expirationDateTimeEdit->setEnabled(true);
    }
    else
    {
        ui->expirationLabel->setEnabled(false);
        ui->expirationDateTimeEdit->setEnabled(false);
    }
}

