#ifndef CHARACTERDIALOG_H
#define CHARACTERDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "character.h"

namespace Ui {
class CharacterDialog;
}

class CharacterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterDialog(QVector<Character*> characters, QWidget *parent = nullptr);
    void hideCloneCharacter();
    void showCloneCharacter();
    ~CharacterDialog();

private slots:
    void characterConfirmed();
    void characterNameChanged(const QString &name);

signals:
    void newCharacter(const QString& name);
    void cloneCharacter(Character* character, const QString& name);

private:
    QVector<Character*> characters;
    Ui::CharacterDialog *ui;
};

#endif // CHARACTERDIALOG_H
