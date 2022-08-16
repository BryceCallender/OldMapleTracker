#ifndef TRACKERTABCONTENT_H
#define TRACKERTABCONTENT_H


#include <QWidget>

#include "character.h"
#include "trackerwidget.h"
#include "progress.h"
#include "actiontype.h"

namespace Ui {
class TrackerTabContent;
}

class TrackerTabContent : public QWidget
{
    Q_OBJECT

public:
    explicit TrackerTabContent(Character* character, Progress* progress, QWidget *parent = nullptr);
    Character* getCharacter();
    void actionsReset(ActionType type);
    void reloadTabs();
    ~TrackerTabContent();

private:
    Ui::TrackerTabContent *ui;
    Progress* progress;
    Character* character;
    QMap<ActionType, TrackerWidget*> trackers;
};

#endif // TRACKERTABCONTENT_H
