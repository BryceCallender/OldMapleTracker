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
#include "logger.h"

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
    void reloadTabs();
    void tabCloseRequest(int index);
    void tabMoved(int from, int to);
    void actionsReset(const QString& type);
    void addNewTab(Character* character, const QString& name);
    QVector<Character*> getCharactersFromTabs();
    ~TrackerTabWidget();
public slots:
    void addCharacterTab(const QString& name);
    void cloneCharacterTab(Character* clone, const QString& name);
signals:
    void characterRemoved(int index);
private:
    Ui::TrackerTabWidget *ui;
    Progress* progress;
    QVector<TrackerTabContent*> tabs;
    std::shared_ptr<spdlog::logger> logger;
};

#endif // TRACKERTABWIDGET_H
