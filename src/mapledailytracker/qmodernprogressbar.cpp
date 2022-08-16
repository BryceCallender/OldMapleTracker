#include "qmodernprogressbar.h"

QModernProgressBar::QModernProgressBar(QWidget *parent) : QProgressBar(parent) {}

QModernProgressBar::~QModernProgressBar() {}

/* https://www.qtcentre.org/threads/70885-QProgressBar-with-in-decimal */

QString QModernProgressBar::text() const
{
    QString result = format();
    if(minimum() ==0 && maximum()==0)
    {
        if(result=="%p%")
        {
            return QString("");
        }
        else
        {
            return result;
        }
    }
    else if (minimum() == maximum())
    {
        return QString("");
    }

    if(result.isEmpty())
    {
        return QString("%p%");
    }
    else
    {
        return result;
    }
}

void QModernProgressBar::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev)
    QStylePainter paint(this);
    QStyleOptionProgressBar opt;
    initStyleOption(&opt);

    paint.drawControl(QStyle::CE_ProgressBarGroove, opt);
    paint.drawControl(QStyle::CE_ProgressBarContents, opt);

    const QStyleOptionProgressBar *option = &opt;
    QStylePainter *painter = &paint;

    // Stolen from QFusionStyle::drawControl
    if (const QStyleOptionProgressBar *pbar = qstyleoption_cast<const QStyleOptionProgressBar *>(option))
    {
        QRect leftRect;
        QRect rect = pbar->rect;
        QColor textColor            = option->palette.text().color();
        QColor alternateTextColor   = QColor(35, 38, 41);

        painter->save();
        bool vertical = false, inverted = false;
        inverted = pbar->invertedAppearance;
        if (vertical)
            rect = QRect(rect.left(), rect.top(), rect.height(), rect.width());
        const auto totalSteps = qMax(Q_INT64_C(1), qint64(pbar->maximum) - pbar->minimum);
        const auto progressSteps = qint64(pbar->progress) - pbar->minimum;
        const int progressIndicatorPos = static_cast<int>(progressSteps * rect.width() / totalSteps);
        if (progressIndicatorPos >= 0 && progressIndicatorPos <= rect.width())
            leftRect = QRect(rect.left(), rect.top(), progressIndicatorPos, rect.height());
        if (vertical)
            leftRect.translate(rect.width() - progressIndicatorPos, 0);

        bool flip = (!vertical && (((pbar->direction == Qt::RightToLeft) && !inverted) ||
                    ((pbar->direction == Qt::LeftToRight) && inverted)));

        QString formattedText = pbar->text;
        formattedText.replace(QLatin1String("%m"), QString("%1").arg(totalSteps));
        const auto progress = static_cast<int>((qint64(value()) - pbar->minimum) * 100.0 / totalSteps);
        formattedText.replace(QLatin1String("%p"), QString("%1").arg(progress));
        QRegion rightRect = rect;
        rightRect = rightRect.subtracted(leftRect);
        painter->setClipRegion(rightRect);
        painter->setPen(flip ? alternateTextColor : textColor);
        painter->drawText(rect, formattedText, QTextOption(Qt::AlignAbsolute |
                                                           Qt::AlignHCenter  |
                                                           Qt::AlignVCenter));
        if (!leftRect.isNull())
        {

            painter->setPen(flip ? textColor : alternateTextColor);
            painter->setClipRect(leftRect);
            painter->drawText(rect, formattedText, QTextOption(Qt::AlignAbsolute |
                                                               Qt::AlignHCenter  |
                                                               Qt::AlignVCenter));
        }
        painter->restore();
    }
}
