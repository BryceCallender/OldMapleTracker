#include "mapleactiondialog.h"
#include "ui_mapleactiondialog.h"

MapleActionDialog::MapleActionDialog(QVector<MapleAction>& actions, QWidget *parent) :
    QDialog(parent),
    actions(actions),
    ui(new Ui::MapleActionDialog)
{
    ui->setupUi(this);
    ui->expirationDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    ui->errorText->hide();

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MapleActionDialog::checkForAction);
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

void MapleActionDialog::checkForAction(const QString &name)
{
    for (const MapleAction& action: actions)
    {
        if (action.name == name)
        {
            ui->errorText->show();
            ui->errorText->setText("<span style='color: #dc3545;'>" + name + " already exists." + "</span>");
            ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
            return;
        }
    }

    ui->errorText->hide();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}
