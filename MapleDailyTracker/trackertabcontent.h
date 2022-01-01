#ifndef TRACKERTABCONTENT_H
#define TRACKERTABCONTENT_H


#include <QWidget>

#include "character.h"
#include "trackerwidget.h"
#include "progress.h"

namespace Ui {
class TrackerTabContent;
}

class TrackerTabContent : public QWidget
{
    Q_OBJECT

public:
    explicit TrackerTabContent(Progress* progress, QWidget *parent = nullptr);
    Character& getCharacter();
    void setCharacter(Character& character);
    ~TrackerTabContent();

private:
    Ui::TrackerTabContent *ui;
    Progress* progress;
    Character character;
};

#endif // TRACKERTABCONTENT_H
