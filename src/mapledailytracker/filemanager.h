#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <algorithm>

#include "character.h"
#include "resetchecker.h"
#include "savedata.h"
#include "logger.h"

class FileManager
{
private:
    FileManager();
    static FileManager* instance;
    std::shared_ptr<spdlog::logger> logger;
public:
    static bool closedWelcome;
    static QString saveFile;
    static QString autosaveFile;
    static FileManager* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new FileManager();
        }

        return instance;
    }

    bool saveData(const QString& name, ResetChecker& resetChecker, QVector<Character*> characters);
    void clearAutoSave();
    SaveData loadData(const QString& name);
    QDateTime zeroOutTime(QDateTime dateTime);
};

#endif // FILEMANAGER_H
