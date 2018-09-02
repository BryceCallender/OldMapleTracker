#include "mapletabwidget.h"
#include "ui_mapletabwidget.h"

MapleTabWidget::MapleTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapleTabWidget)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit->setTime(QTime::currentTime());
    nameWindow = new CheckBoxNameWindow();
}

MapleTabWidget::~MapleTabWidget()
{
    delete ui;
}

/**
 * @brief MapleTabWidget::on_addDailyButton_clicked
 * This function will add a new daily to the current tab
 * and will open a new window to ask for the name of the new tab
 * if it already exists will prompt them with error message
 */
void MapleTabWidget::on_addDailyButton_clicked()
{
    QCheckBox* checkBox = new QCheckBox(ui->dailyBox); //dailyBox the parent of this new checkbox
    nameWindow->exec();   
    if(!dailyOrWeeklyExistsAlready(nameWindow->getName()))
    {
        checkBox->setText(nameWindow->getName());
        ui->dailyBox->layout()->addWidget(checkBox);
    }
    else
    {
        QMessageBox::critical(this,"Name exists","This already exists in your current section",QMessageBox::Ok);
    }
}

/**
 * @brief MapleTabWidget::on_addWeeklyButton_clicked
 * This function will add a new weekly to the current tab
 * and will open a new window to ask for the name of the new tab
 * if it already exists will prompt them with error message
 */
void MapleTabWidget::on_addWeeklyButton_clicked()
{
    QCheckBox* checkBox = new QCheckBox(ui->weeklyBox); //weeklyBox is the parent of this new checkbox
    nameWindow->exec();
    if(!dailyOrWeeklyExistsAlready(nameWindow->getName()))
    {
        checkBox->setText(nameWindow->getName());
        ui->weeklyBox->layout()->addWidget(checkBox);
    }
    else
    {
        QMessageBox::critical(this,"Name exists","This already exists in your current section",QMessageBox::Ok);
    }
}

//ToDo::fix this to be based on the current tab
bool MapleTabWidget::finishedAllDailies()
{
    const auto checkBoxList = ui->dailyBox->findChildren<QCheckBox*>();
    for(auto&& checkBox : checkBoxList)
    {
        if(!checkBox->isChecked())
        {
            return false;
        }
    }

    return true;
}

//ToDo::fix this to be based on the current tab
bool MapleTabWidget::finishedAllWeekly()
{
    const auto checkBoxList = ui->weeklyBox->findChildren<QCheckBox*>();
    for(auto&& checkBox : checkBoxList)
    {
        if(!checkBox->isChecked())
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief MapleTabWidget::dailyOrWeeklyExistsAlready
 * Function checks if we have a daily or weekly with this current
 * name from the other window we had just entered it into
 * @param name
 * @return
 */
bool MapleTabWidget::dailyOrWeeklyExistsAlready(QString name)
{
    auto checkBoxList = ui->dailyBox->findChildren<QCheckBox*>();
    checkBoxList.append(ui->weeklyBox->findChildren<QCheckBox*>());

    for(auto&& checkBox : checkBoxList)
    {
        if(checkBox->text() == name)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief MapleTabWidget::getDailies
 * returns list of the dailies for the current tab
 * @return
 */
QList<QCheckBox*> MapleTabWidget::getDailies()
{
    return ui->dailyBox->findChildren<QCheckBox*>();
}

/**
 * @brief MapleTabWidget::getWeeklies
 * returns list of the weeklies for the current tab
 * @return
 */
QList<QCheckBox*> MapleTabWidget::getWeeklies()
{
    return ui->weeklyBox->findChildren<QCheckBox*>();
}

void MapleTabWidget::addDailyCheckBox(QCheckBox *checkBox)
{
    ui->dailyBox->layout()->addWidget(checkBox);
}

void MapleTabWidget::addWeeklyCheckBox(QCheckBox *checkBox)
{
    ui->weeklyBox->layout()->addWidget(checkBox);
}

