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
    ~QModernProgressBar() Q_DECL_OVERRIDE;

   protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

public:
    virtual QString text() const Q_DECL_OVERRIDE;
};

#endif // QMODERNPROGRESSBAR_H
