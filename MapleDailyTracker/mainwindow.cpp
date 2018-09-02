#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow = new InitilizationWindow();
    trackerWindow = new DailyTrackerWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_beginTrackerButton_clicked()
{
    QFile file("FileLocation.txt");
    this->close();

    //If the save file is saved into the program
    if(file.exists("FileLocation.txt"))
    {
        qDebug() << "File exists";
        if(file.open(QIODevice::ReadOnly))
        {
            if(!file.atEnd())
            {
                if(trackerWindow->loadData())
                {
                    trackerWindow->show();
                    QMessageBox::information(this,"Welcome Back","Welcome back!",QMessageBox::Ok);
                }
                else
                {
                    QMessageBox::critical(this,"Couldn't get save information","No Save File detected or file is corrupted");
                }

            }
            else
            {
                qDebug() << "Empty file";
            }
        }
    }
    else
    {
        initWindow->show();
    }
}
