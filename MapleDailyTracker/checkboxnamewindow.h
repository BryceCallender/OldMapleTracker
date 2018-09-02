#ifndef CHECKBOXNAMEWINDOW_H
#define CHECKBOXNAMEWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class CheckBoxNameWindow;
}

class CheckBoxNameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CheckBoxNameWindow(QWidget *parent = nullptr);
    QString getName();
    ~CheckBoxNameWindow();

private slots:
    void on_submitButton_clicked();

private:
    Ui::CheckBoxNameWindow *ui;
};

#endif // CHECKBOXNAMEWINDOW_H
