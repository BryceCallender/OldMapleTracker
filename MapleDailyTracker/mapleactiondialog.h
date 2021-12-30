#ifndef MAPLEACTIONDIALOG_H
#define MAPLEACTIONDIALOG_H

#include <QDialog>

#include "mapleaction.h"

namespace Ui {
class MapleActionDialog;
}

class MapleActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapleActionDialog(QWidget *parent = nullptr);
    void createAction();
    ~MapleActionDialog();

private slots:
    void enableTemporaryState(int state);

signals:
    void actionConfirmed(MapleAction& mapleAction);
private:
    Ui::MapleActionDialog *ui;
};

#endif // MAPLEACTIONDIALOG_H
