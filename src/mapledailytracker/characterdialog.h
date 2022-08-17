#ifndef CHARACTERDIALOG_H
#define CHARACTERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTreeWidget>
#include <QVariant>

#include "character.h"

namespace Ui {
class CharacterDialog;
}

class CharacterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterDialog(QVector<Character*> characters, QWidget *parent = nullptr);
    void setCloneCharacterEditability(bool state);
    void parseTree();
    ~CharacterDialog();

private slots:
    void characterConfirmed();
    void characterNameChanged(const QString &name);
    void characterSelectionChanged(const int index);

signals:
    void newCharacter(const QString& name);
    void cloneCharacter(Character* character, const QString& name);

private:
    void addWidgetItem(QTreeWidgetItem* parent, const MapleAction& action);
    QVector<MapleAction> extractActions(QTreeWidgetItem* parent);

    QVector<Character*> characters;
    Character* character;
    Ui::CharacterDialog *ui;
};

#endif // CHARACTERDIALOG_H
