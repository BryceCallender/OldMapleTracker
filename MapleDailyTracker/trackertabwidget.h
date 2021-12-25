#ifndef TRACKERTABWIDGET_H
#define TRACKERTABWIDGET_H

#include <QTabWidget>
#include <QVector>
#include <QDebug>

#include "savedata.h"
#include "trackertabcontent.h"

namespace Ui {
class TrackerTabWidget;
}

class TrackerTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TrackerTabWidget(QWidget *parent = nullptr);
    void loadTabs(SaveData saveData);
    QVector<Character> getCharactersFromTabs();
    ~TrackerTabWidget();
public slots:
    void addCharacterTab(QString name);
private:
    Ui::TrackerTabWidget *ui;
    QVector<TrackerTabContent*> tabs;
};

#endif // TRACKERTABWIDGET_H
