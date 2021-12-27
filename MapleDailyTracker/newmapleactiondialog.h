#ifndef NEWMAPLEACTIONDIALOG_H
#define NEWMAPLEACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class NewMapleActionDialog;
}

class NewMapleActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMapleActionDialog(QWidget *parent = nullptr);
    ~NewMapleActionDialog();

private slots:
    void on_checkBox_stateChanged(int state);

private:
    Ui::NewMapleActionDialog *ui;
};

#endif // NEWMAPLEACTIONDIALOG_H
