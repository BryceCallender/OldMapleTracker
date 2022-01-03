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
    QMap<QString, double> getProgressFromData();
    ~ProgressContent();

private:
    double getProgressFromSet(const QVector<MapleAction>& set);
    Character* character;
    Ui::ProgressContent *ui;
};

#endif // PROGRESSCONTENT_H
