#include <QObject>
#include <QProcess>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

class MaintenanceTool : public QObject
{
    Q_OBJECT

    Q_ENUMS(ProcessState)
    Q_ENUMS(StartMode)

    Q_PROPERTY(ProcessState state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool hasUpdate READ hasUpdate NOTIFY hasUpdateChanged)
    Q_PROPERTY(QString updateDetails READ updateDetails NOTIFY updateDetailsChanged)

public:
    explicit MaintenanceTool(QObject *parent = 0);

    enum ProcessState
    {
        NotRunning,
        Running
    };
    enum StartMode
    {
        CheckUpdate,
        Updater
    };

    ProcessState state() const;
    bool hasUpdate() const;
    QString updateDetails() const;

signals:
    void stateChanged(MaintenanceTool::ProcessState state);
    void hasUpdateChanged(bool asUpdate);
    void updateDetailsChanged(const QString &updateDetails);

public slots:
    void checkUpdate();
    void startMaintenanceTool(MaintenanceTool::StartMode mode = Updater);

private slots:
    void setHasUpdate(bool hasUpdate);
    void setUpdateDetails(const QString &updateDetails);
    void processStarted();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);

private:
    ProcessState m_state;
    bool m_hasUpdate;
    QString m_updateDetails;
    QProcess m_process;

    void setState(ProcessState state);
};
