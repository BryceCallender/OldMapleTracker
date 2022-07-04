#ifndef MAPLEACTIONDIALOG_H
#define MAPLEACTIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QJsonDocument>

#include "mapleaction.h"
#include "logger.h"

namespace Ui {
class MapleActionDialog;
}

class MapleActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapleActionDialog(QVector<MapleAction>& actions, MapleAction* action = nullptr, QWidget* parent = nullptr);
    void createAction();
    void editAction();
    void checkForAction(const QString& name);
    std::string logAction(const MapleAction& action);
    ~MapleActionDialog();

private slots:
    void enableTemporaryState(int state);

signals:
    void actionConfirmed(MapleAction& mapleAction);
private:
    QVector<MapleAction>& actions;
    MapleAction* action;
    Ui::MapleActionDialog* ui;

    std::shared_ptr<spdlog::logger> logger;
};

#endif // MAPLEACTIONDIALOG_H
