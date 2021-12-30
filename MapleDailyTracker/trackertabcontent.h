#ifndef TRACKERTABCONTENT_H
#define TRACKERTABCONTENT_H


#include <QWidget>

#include "character.h"
#include "actiontype.h"
#include "trackerwidget.h"

namespace Ui {
class TrackerTabContent;
}

class TrackerTabContent : public QWidget
{
    Q_OBJECT

public:
    explicit TrackerTabContent(QWidget *parent = nullptr);
    void addMapleAction(ActionType actionType, QString &action);
    Character getCharacter();
    void setCharacter(Character character);
    ~TrackerTabContent();

private:
    Ui::TrackerTabContent *ui;
    Character character;
};

#endif // TRACKERTABCONTENT_H
