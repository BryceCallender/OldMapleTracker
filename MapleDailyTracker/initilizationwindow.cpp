#include "initilizationwindow.h"
#include "ui_initilizationwindow.h"


InitilizationWindow::InitilizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitilizationWindow)
{
    ui->setupUi(this);
    ui->playerTrackerTable->setColumnCount(1);
    ui->playerTrackerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->playerTrackerTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Character Name"));
}

InitilizationWindow::~InitilizationWindow()
{
    delete ui;
}

void InitilizationWindow::on_trackPlayerBox_valueChanged(int arg1)
{
    ui->playerTrackerTable->setRowCount(arg1);
}

void InitilizationWindow::on_submitButton_clicked()
{
    int playerCount = ui->playerTrackerTable->rowCount();
    QVector<QString> charactersToTrack;
    QAbstractItemModel* model = ui->playerTrackerTable->model();

    for(int i = 0; i < playerCount; i++)
    {   
        QString name = model->data(model->index(i,0)).toString();
        charactersToTrack.push_back(name);
    }

    writeToFile(charactersToTrack);
    readFile();
    QMessageBox::information(this,"Characters saved to file","Your characters have been recorded",QMessageBox::Ok);
}

void InitilizationWindow::writeToFile(QVector<QString> characters)
{
    QDir dir;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Characters"), dir.currentPath(),
                                                    tr("Character List (*.txt);;All Files (*)"));

    qDebug() << fileName;

    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        QFile saveFileName("FileLocation.txt");
        if (!file.open(QIODevice::WriteOnly) || !saveFileName.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream out(&file);
        QTextStream save(&saveFileName);
        save << fileName;
        out << characters;
    }
}

void InitilizationWindow::readFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Character List"), "",
                                                    tr("Character List (*.txt);;All Files (*)"));

    qDebug() << fileName;

    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream in(&file);
        characters.clear();
        in >> characters;
    }
}
