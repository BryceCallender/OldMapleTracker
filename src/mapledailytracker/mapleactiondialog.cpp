#include "mapleactiondialog.h"
#include "ui_mapleactiondialog.h"

MapleActionDialog::MapleActionDialog(const QString& section, QVector<MapleAction>& actions, MapleAction* action, QWidget* parent) :
    QDialog(parent),
    actions(actions),
    ui(new Ui::MapleActionDialog)
{
    ui->setupUi(this);

    logger = Logger::getLogger();

    this->section = section;

    ui->expirationDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    ui->errorText->hide();

    if (action != nullptr)
    {
        setWindowTitle(tr("Edit Action"));
        this->action = action;

        ui->lineEdit->setText(action->name);
        ui->checkBox->setChecked(action->isTemporary);
        ui->expirationDateTimeEdit->setDateTime(action->removalTime);
    }

    if (action)
    {
         connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &MapleActionDialog::editAction);
    }
    else
    {
         connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &MapleActionDialog::createAction);
    }

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MapleActionDialog::checkForAction);
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MapleActionDialog::enableTemporaryState);
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
    action.order = 999;
    action.isTemporary = ui->checkBox->isChecked();
    action.removalTime = action.isTemporary ? ui->expirationDateTimeEdit->dateTime() : QDateTime();

    logger->info("{0}: Created action: {1}", section.toStdString(), action.toString());
    emit actionConfirmed(action);
}

void MapleActionDialog::editAction()
{
    MapleAction actionBefore = *action;
    action->name = ui->lineEdit->text();
    action->isTemporary = ui->checkBox->isChecked();
    action->removalTime = action->isTemporary ? ui->expirationDateTimeEdit->dateTime() : QDateTime();

    logger->info("{0}: Edited action {1} to {2}", section.toStdString(), actionBefore.toString(), action->toString());
}

void MapleActionDialog::checkForAction(const QString& name)
{
    for (const MapleAction& action: actions)
    {
        if (action.name == name)
        {
            ui->errorText->show();
            ui->errorText->setText("<span style='color: #dc3545;'>" + name + tr(" already exists.") + "</span>");
            ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
            return;
        }
    }

    ui->errorText->hide();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}
