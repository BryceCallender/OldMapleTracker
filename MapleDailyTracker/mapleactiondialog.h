#ifndef MAPLEACTIONDIALOG_H
#define MAPLEACTIONDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "mapleaction.h"

namespace Ui {
class MapleActionDialog;
}

class MapleActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapleActionDialog(QVector<MapleAction>& actions, MapleAction* action = nullptr, QWidget* parent = nullptr);
    void createAction();
    void checkForAction(const QString& name);
    ~MapleActionDialog();

private slots:
    void enableTemporaryState(int state);

signals:
    void actionConfirmed(MapleAction& mapleAction);
private:
    QVector<MapleAction>& actions;
    Ui::MapleActionDialog* ui;
};

#endif // MAPLEACTIONDIALOG_H
