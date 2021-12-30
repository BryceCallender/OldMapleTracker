#ifndef PROGRESS_H
#define PROGRESS_H

#include <QVBoxLayout>
#include <QWidget>
#include <QProgressBar>
#include <QSpacerItem>
#include <QLabel>

#include "character.h"

namespace Ui {
class Progress;
}

class Progress : public QWidget
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = nullptr);
    void load(QVector<Character> characters);
    void addProgressBar(QString name, QMap<QString, double>& progressData);
    void addCharacterProgress(Character& character);
    QMap<QString, double> getProgressFromData(Character& character);
    ~Progress();

private:
    double getProgressFromSet(const QVector<MapleAction> &set);
    QVBoxLayout* layout;
    Ui::Progress *ui;
};

#endif // PROGRESS_H
