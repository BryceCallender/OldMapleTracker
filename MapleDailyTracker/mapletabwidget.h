#ifndef MAPLETABWIDGET_H
#define MAPLETABWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QDebug>
#include <QTimer>
#include "checkboxnamewindow.h"
#include "datechecker.h"

namespace Ui {
class MapleTabWidget;
}

class MapleTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapleTabWidget(QWidget *parent = nullptr);
    bool finishedAllDailies();
    bool finishedAllWeekly();
    bool dailyOrWeeklyExistsAlready(QString name);
    QList<QCheckBox*> getDailies();
    QList<QCheckBox*> getWeeklies();
    void addDailyCheckBox(QCheckBox* checkBox);
    void addWeeklyCheckBox(QCheckBox* checkBox);
    ~MapleTabWidget();

private slots:
    void on_addDailyButton_clicked();
    void on_addWeeklyButton_clicked();
    void updateResets();

private:
    Ui::MapleTabWidget *ui;
    DateChecker* dateChecker;
    QTimer* timer;
    CheckBoxNameWindow* nameWindow;
};

#endif // MAPLETABWIDGET_H
