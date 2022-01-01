#ifndef TRACKERTABWIDGET_H
#define TRACKERTABWIDGET_H

#include <QTabWidget>
#include <QVector>
#include <QDebug>
#include <QMessageBox>

#include "savedata.h"
#include "trackertabcontent.h"
#include "filemanager.h"
#include "progress.h"

namespace Ui {
class TrackerTabWidget;
}

class TrackerTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TrackerTabWidget(QWidget *parent = nullptr);
    void setProgressReference(Progress* progress);
    void loadTabs(SaveData& saveData);
    void tabCloseRequest(int index);
    QVector<Character> getCharactersFromTabs();
    ~TrackerTabWidget();
public slots:
    void addCharacterTab(QString name);
signals:
    void characterAdded(Character& character);
    void characterRemoved(int index);
private:
    Ui::TrackerTabWidget *ui;
    Progress* progress;
    QVector<TrackerTabContent*> tabs;
};

#endif // TRACKERTABWIDGET_H
