#include "maintenancetool.h"

MaintenanceTool::MaintenanceTool(QObject *parent) :
    QObject(parent),
    m_state(MaintenanceTool::NotRunning),
    m_hasUpdate(false)
{

    connect(&m_process, &QProcess::started, this, &MaintenanceTool::processStarted);
    connect(&m_process, &QProcess::finished, this, &MaintenanceTool::processFinished);
    connect(&m_process, &QProcess::errorOccurred, this, &MaintenanceTool::processError);
}

void MaintenanceTool::checkUpdate()
{
    startMaintenanceTool(MaintenanceTool::CheckUpdate);
}

void MaintenanceTool::startMaintenanceTool(StartMode mode)
{
    QString toolName;
    QString path;
#if defined(Q_OS_WIN)
    toolName = "maintenancetool.exe";
#elif defined(Q_OS_MAC)
    toolName = "../../../maintenancetool.app/Contents/MacOS/maintenancetool";
#else
    toolName = "maintenancetool";
#endif
    path = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(toolName);
    qDebug() << path;

    QStringList args;
    if(mode == MaintenanceTool::CheckUpdate)
    {
        if(m_process.state() == QProcess::NotRunning)
        {
            setUpdateDetails(QString());
            setHasUpdate(false);
            args.append("--checkupdates");
            m_process.start(path, args);
        }
        else
        {
            qDebug() << "Already started.";
        }
    }
    else
    {
        args.append("--updater");
        QProcess::startDetached(path, args);
    }
}

MaintenanceTool::ProcessState MaintenanceTool::state() const
{
    return m_state;
}

void MaintenanceTool::setState(ProcessState state)
{
    if(m_state == state)    return;
    m_state = state;
    emit stateChanged(m_state);
}

bool MaintenanceTool::hasUpdate() const
{
    return m_hasUpdate;
}

void MaintenanceTool::setHasUpdate(bool hasUpdate)
{
    if(m_hasUpdate == hasUpdate)    return;
    m_hasUpdate = hasUpdate;
    emit hasUpdateChanged(m_hasUpdate);
}

QString MaintenanceTool::updateDetails() const
{
    return m_updateDetails;
}
void MaintenanceTool::setUpdateDetails(const QString &updateDetails)
{
    if(m_updateDetails == updateDetails) return;
    m_updateDetails = updateDetails;
    emit updateDetailsChanged(m_updateDetails);
}


void MaintenanceTool::processStarted()
{
    setState(MaintenanceTool::Running);
}

void MaintenanceTool::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "exitCode=" << exitCode << ", exitStatus=" << exitStatus;

    if(exitCode == 0)
    {
        QByteArray stdOut = m_process.readAllStandardOutput();
        QString stdOutStr = QString::fromLocal8Bit(stdOut);
        qDebug() << "out>" << stdOutStr;

        QString xmlStr;
        QStringList lines;
        bool enabled = false;
        lines = stdOutStr.split("\n");
        foreach (const QString &line, lines) 
        {
            if(line.startsWith("<updates>"))
            {
                enabled = true;
                xmlStr.append(line);
            }
            else if(line.endsWith("</updates>"))
            {
                xmlStr.append(line);
                break;
            }
            else if(enabled)
            {
                xmlStr.append(line);
            }
            else
            {
            }
        }

        if(xmlStr.length() > 0)
        {
            setUpdateDetails(xmlStr);
            setHasUpdate(true);
        }

        setState(MaintenanceTool::NotRunning);

    }else if(exitCode == 1)
    {
        QByteArray stdErr = m_process.readAllStandardError();
        QString stdErrStr = QString::fromLocal8Bit(stdErr);
        qDebug() << "err>" << stdErrStr;

        setState(MaintenanceTool::NotRunning);
    }
    else
    {
        setState(MaintenanceTool::NotRunning);
    }
}

void MaintenanceTool::processError(QProcess::ProcessError error)
{
    qDebug() << error;
    setState(MaintenanceTool::NotRunning);
}
