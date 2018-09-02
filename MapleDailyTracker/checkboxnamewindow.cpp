#include "checkboxnamewindow.h"
#include "ui_checkboxnamewindow.h"

CheckBoxNameWindow::CheckBoxNameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckBoxNameWindow)
{
    ui->setupUi(this);
}

CheckBoxNameWindow::~CheckBoxNameWindow()
{
    delete ui;
}

QString CheckBoxNameWindow::getName()
{
    return ui->checkboxName->text();
}

void CheckBoxNameWindow::on_submitButton_clicked()
{
    if(getName().isEmpty())
    {
        QMessageBox::information(this,"Fill out name","Fill out the name for the checkbox",QMessageBox::Ok);
    }
    else
    {
        this->close();
    }
}
