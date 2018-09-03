#include "dailytrackerwindow.h"
#include "ui_dailytrackerwindow.h"

DailyTrackerWindow::DailyTrackerWindow(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::DailyTrackerWindow)
{
    ui->setupUi(this);
    QTabWidget::setWindowTitle("Maple Daily/Weekly Tracker");
    dateChecker = new DateChecker();

    //Making a save file when u open up the window or at least make an object
    //of this tracker window so u can open it and have save data written to it
    //when the oncloseevent is called for this window
    QFile file("SaveData.txt");

    if(file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Made save file for u bb";
    }
    else
    {
        qDebug() << file.errorString();
    }
}

DailyTrackerWindow::~DailyTrackerWindow()
{
    delete ui;
}

void DailyTrackerWindow::loadTabs()
{
    qDebug() << "Loading tabs....";
    QVector<QString> names = getNamesForTabs();
    qDebug() << "How many names? " << names.size();
    for(int i = 0; i < names.size(); i++)
    {
        qDebug() << names.at(i);
        MapleTabWidget* newTab = new MapleTabWidget();
        this->addTab(newTab,names.at(i));
        tabs.push_back(newTab);
    }
}

QVector<QString> DailyTrackerWindow::getNamesForTabs()
{
    QVector<QString> names;
    QFile file("FileLocation.txt");
    QString pathOfFile;

    if(!file.open(QIODevice::ReadOnly) && !file.exists())
    {
        return names;
    }
    //This will be the full path to the file
    pathOfFile = file.readLine();

    QStringList path = pathOfFile.split('/');
    //The filename we want is at the end with the actual name of the file you chose
    QString fileName = path.at(path.length() - 1);
    qDebug() << "File name" << fileName;
    QFile nameFile(fileName);

    if(nameFile.open(QIODevice::ReadOnly))
    {
        QDataStream fileStream(&nameFile);
        names.clear();
        fileStream >> names;
    }
    else
    {
        qDebug() << nameFile.errorString();
    }

    nameFile.close();
    file.close();
    return names;
}

void DailyTrackerWindow::resetDailies()
{
    if(dateChecker->isDailyReset())
    {
        foreach(MapleTabWidget* tab,tabs)
        {
            QList<QCheckBox*> checkBoxes = tab->getDailies();

            foreach(QCheckBox *checkBox, checkBoxes)
            {
                checkBox->setChecked(false);
            }
        }
    }
}

void DailyTrackerWindow::resetWeeklies()
{
    if(dateChecker->isWeeklyReset())
    {
        foreach(MapleTabWidget* tab,tabs)
        {
            QList<QCheckBox*> checkBoxes = tab->getWeeklies();

            foreach(QCheckBox *checkBox, checkBoxes)
            {
                checkBox->setChecked(false);
            }
        }
    }
}

bool DailyTrackerWindow::saveData()
{
    QFile file("SaveData.txt");

    if(file.open(QIODevice::WriteOnly))
    {
       dateChecker->writeToFile();
       QTextStream fileStream(&file);
       foreach (MapleTabWidget* tab, tabs)
       {
           QList<QCheckBox*> checkBoxes = tab->getDailies();
           //Writes dailies to file
           fileStream << checkBoxes.size() << "\n";
           foreach(QCheckBox *daily, checkBoxes)
           {
               fileStream << daily->text() << "\n";
               fileStream << daily->isChecked() << "\n";
               fileStream.flush();
           }

           checkBoxes = tab->getWeeklies();
           //writes weeklys to file
           fileStream << checkBoxes.size() << "\n";
           foreach(QCheckBox *weekly, checkBoxes)
           {
               fileStream << weekly->text() << "\n";
               fileStream << weekly->isChecked() << "\n";
               fileStream.flush();
           }
       }
       file.close();
       return true;
    }
    return false;
}

bool DailyTrackerWindow::loadData()
{
    int i = 0;
    loadTabs();

    QFile file("SaveData.txt");

    if(file.open(QIODevice::ReadOnly))
    {    
        QTextStream fileStream(&file);
        //At the beginning it should be at end since its a new file
        while(!fileStream.atEnd())
        {
            //Find out how many times to check for dailies
            int dailyCount = fileStream.readLine().toInt();
            qDebug() << "Daily Count " << dailyCount;
            for(int j = 0; j < dailyCount; j++)
            {
                QCheckBox *dailyBox = new QCheckBox();
                dailyBox->setText(fileStream.readLine());
                dailyBox->setChecked(fileStream.readLine().toInt());
                tabs.at(i)->addDailyCheckBox(dailyBox);
            }
            //Find out how many times to check for weeklies
            int weeklyCount = fileStream.readLine().toInt();
            qDebug() << "Weekly Count " << weeklyCount;
            for(int j = 0; j < weeklyCount; j++)
            {
                QCheckBox *weeklyBox = new QCheckBox();
                weeklyBox->setText(fileStream.readLine());
                weeklyBox->setChecked(fileStream.readLine().toInt());
                tabs.at(i)->addWeeklyCheckBox(weeklyBox);
            }
            i++;
        }
        file.close();
        return true;
    }
    return false;
}

void DailyTrackerWindow::closeEvent(QCloseEvent *event)
{
    if(saveData())
    {
        qDebug() << "Saved";
        event->accept();
    }
    else
    {
        qDebug() << "Not Saved";
        event->ignore();
    }
}
