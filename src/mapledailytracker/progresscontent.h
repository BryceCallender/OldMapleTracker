#ifndef PROGRESSCONTENT_H
#define PROGRESSCONTENT_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QProgressBar>

#include "character.h"
#include "actiontype.h"

namespace Ui {
class ProgressContent;
}

class ProgressContent : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressContent(Character* character, QWidget *parent = nullptr);
    void loadProgressBars();
    Character* getCharacter();
    QMap<ActionType, double> getProgressFromData();
    void mousePressEvent(QMouseEvent* event);
    ~ProgressContent();
signals:
    void clicked(Character* character);
private:
    double getProgressFromSet(const QVector<MapleAction>& set);
    void animateProgress(QProgressBar* progressBar, double value);
    Character* character;
    Ui::ProgressContent *ui;
};

#endif // PROGRESSCONTENT_H
