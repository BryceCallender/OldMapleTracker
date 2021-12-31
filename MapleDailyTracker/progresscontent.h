#ifndef PROGRESSCONTENT_H
#define PROGRESSCONTENT_H

#include <QWidget>

#include "character.h"

namespace Ui {
class ProgressContent;
}

class ProgressContent : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressContent(Character& character, QWidget *parent = nullptr);
    void loadProgressBars();
    QMap<QString, double> getProgressFromData(Character& character);
    Character& getCharacter();
    ~ProgressContent();

private:
    double getProgressFromSet(const QVector<MapleAction>& set);
    Ui::ProgressContent *ui;
    Character character;
};

#endif // PROGRESSCONTENT_H
