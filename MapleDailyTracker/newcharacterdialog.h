#ifndef NEWCHARACTERDIALOG_H
#define NEWCHARACTERDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class NewCharacterDialog;
}

class NewCharacterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCharacterDialog(QWidget *parent = nullptr);
    ~NewCharacterDialog();

private slots:
    void on_buttonBox_accepted();

    void on_lineEdit_textChanged(const QString &name);

signals:
    void newCharacter(QString name);

private:
    Ui::NewCharacterDialog *ui;
};

#endif // NEWCHARACTERDIALOG_H
