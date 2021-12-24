#ifndef TRACKERTABCONTENT_H
#define TRACKERTABCONTENT_H

#include <QWidget>

#include "character.h"

namespace Ui {
class TrackerTabContent;
}

class TrackerTabContent : public QWidget
{
    Q_OBJECT

public:
    explicit TrackerTabContent(QWidget *parent = nullptr);
    Character getCharacter();
    void setCharacter(Character character);
    ~TrackerTabContent();

private:
    Ui::TrackerTabContent *ui;
    Character character;
};

#endif // TRACKERTABCONTENT_H
