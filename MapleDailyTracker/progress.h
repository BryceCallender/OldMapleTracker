#ifndef PROGRESS_H
#define PROGRESS_H

#include <QVBoxLayout>
#include <QWidget>
#include <QProgressBar>
#include <QSpacerItem>
#include <QLabel>

#include "character.h"
#include "progresscontent.h"

namespace Ui {
class Progress;
}

class Progress : public QWidget
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = nullptr);
    void addCharacterProgress(Character* character);
     ~Progress();
public slots:
    void removeCharacterProgress(int index);
    void scrollToProgress(int index);
    void updateProgress();
    void progressContentClicked(Character* character);
signals:
    void clicked(int index);
private:
    QLayout* layout;
    Ui::Progress *ui;
    QVector<ProgressContent*> progress;
};

#endif // PROGRESS_H
