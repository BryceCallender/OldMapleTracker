#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    setWindowTitle("Preferences");

    logger = Logger::getLogger();

    QDirIterator it(":/styles", QDirIterator::Subdirectories);
    QStringList themes;

    while (it.hasNext())
    {
        it.next();
        QFileInfo fileInfo = it.fileInfo();
        if (fileInfo.suffix() == "qss")
        {
            themes.append(fileInfo.baseName().remove("dark_"));
        }
    }

    QSettings settings;
    QString theme = settings.value("theme", "teal").toString();
    currentTheme = theme;

    buttonBox = ui->buttonBox;


    ui->comboBox->addItems(themes);
    ui->comboBox->setCurrentText(theme);

    connect(buttonBox, &QDialogButtonBox::clicked, this, &Preferences::dialogButtonClicked);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &Preferences::themeChanged);

    buttonBox->button(QDialogButtonBox::Apply)->setDisabled(true);
}

void Preferences::dialogButtonClicked(QAbstractButton *button)
{
    QPushButton* pushButton = static_cast<QPushButton*>(button);

    if (pushButton == buttonBox->button(QDialogButtonBox::Apply))
    {
        applySettings();
    }

    if (pushButton == buttonBox->button(QDialogButtonBox::Ok))
    {
        saveSettings();
    }

    if (pushButton == buttonBox->button(QDialogButtonBox::Cancel))
    {
        currentTheme = oldTheme;
    }
}

void Preferences::themeChanged(const QString& theme)
{
    buttonBox->button(QDialogButtonBox::Apply)->setDisabled(currentTheme == theme);
}

void Preferences::applySettings()
{
    QString theme = ui->comboBox->currentText();
    oldTheme = currentTheme;
    currentTheme = theme;

    QFile styleFile(QString(":/styles/dark_%1.qss").arg(theme));
    styleFile.open(QFile::ReadOnly);

    QString style { styleFile.readAll() };
    qApp->setStyleSheet(style);
}

void Preferences::saveSettings()
{
    QSettings settings;
    settings.setValue("theme", ui->comboBox->currentText());

    logger->info("Changing theme to: {}", ui->comboBox->currentText().toStdString());

    applySettings();
}

Preferences::~Preferences()
{
    delete ui;
}
