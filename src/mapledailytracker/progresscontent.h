#ifndef PROGRESSCONTENT_H
#define PROGRESSCONTENT_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QProgressBar>
#include <QGraphicsOpacityEffect>

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
public slots:
    void toggleProgressBar(ActionType actionType, bool isVisible);
private:
    double getProgressFromSet(const QVector<MapleAction>& set);
    void animateProgress(QProgressBar* progressBar, double value);

    QMap<ActionType, QProgressBar*> progressBars;
    Character* character;
    Ui::ProgressContent *ui;
};

#endif // PROGRESSCONTENT_H
