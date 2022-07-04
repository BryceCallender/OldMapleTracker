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
    explicit ProgressContent(Character* character, QWidget *parent = nullptr);
    void loadProgressBars();
    Character* getCharacter();
    QMap<QString, double> getProgressFromData();
    void mousePressEvent(QMouseEvent* event);
    ~ProgressContent();
signals:
    void clicked(Character* character);
private:
    double getProgressFromSet(const QVector<MapleAction>& set);
    Character* character;
    Ui::ProgressContent *ui;
};

#endif // PROGRESSCONTENT_H
