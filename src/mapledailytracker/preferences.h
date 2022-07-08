#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QAbstractButton>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDirIterator>
#include <QSettings>
#include <QPushButton>

#include "logger.h"

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = nullptr);
    void dialogButtonClicked(QAbstractButton* button);
    void themeChanged(const QString& theme);
    void applySettings();
    void saveSettings();
    ~Preferences();

private:
    Ui::Preferences* ui;
    QDialogButtonBox* buttonBox;
    QString currentTheme;
    QString oldTheme;

    std::shared_ptr<spdlog::logger> logger;
};

#endif // PREFERENCES_H
