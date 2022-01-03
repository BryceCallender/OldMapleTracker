#ifndef CHARACTERDIALOG_H
#define CHARACTERDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class CharacterDialog;
}

class CharacterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterDialog(QWidget *parent = nullptr);
    ~CharacterDialog();

private slots:
    void characterConfirmed();
    void characterNameChanged(const QString &name);

signals:
    void newCharacter(QString name);

private:
    Ui::CharacterDialog *ui;
};

#endif // CHARACTERDIALOG_H
