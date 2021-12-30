#include "mapleactiondialog.h"
#include "ui_mapleactiondialog.h"

MapleActionDialog::MapleActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapleActionDialog)
{
    ui->setupUi(this);
    ui->expirationDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());

    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MapleActionDialog::enableTemporaryState);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &MapleActionDialog::createAction);
}

MapleActionDialog::~MapleActionDialog()
{
    delete ui;
}

void MapleActionDialog::enableTemporaryState(int state)
{
    bool enable = state == Qt::Checked;
    ui->expirationLabel->setEnabled(enable);
    ui->expirationDateTimeEdit->setEnabled(enable);
}

void MapleActionDialog::createAction()
{
    MapleAction action;
    action.name = ui->lineEdit->text();
    action.done = false;
    action.isTemporary = ui->checkBox->isChecked();
    action.removalTime = action.isTemporary ? ui->expirationDateTimeEdit->dateTime() : QDateTime();
    emit actionConfirmed(action);
}

