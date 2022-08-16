#ifndef QMODERNPROGRESSBAR_H
#define QMODERNPROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QPaintEvent>
#include <QStylePainter>
#include <QStyleOption>
#include <QDebug>

class QModernProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit QModernProgressBar(QWidget *parent = nullptr);
    ~QModernProgressBar() override;

protected:
    void paintEvent(QPaintEvent *) override;

public:
    virtual QString text() const override;
};

#endif // QMODERNPROGRESSBAR_H
