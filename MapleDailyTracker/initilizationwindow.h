#ifndef INITILIZATIONWINDOW_H
#define INITILIZATIONWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class InitilizationWindow;
}

class InitilizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InitilizationWindow(QWidget *parent = nullptr);
    ~InitilizationWindow();

private slots:
    void on_trackPlayerBox_valueChanged(int arg1);

    void on_submitButton_clicked();

private:
    void writeToFile(QVector<QString> characters);
    void readFile();
    QVector<QString> characters;
    Ui::InitilizationWindow *ui;
};

#endif // INITILIZATIONWINDOW_H
