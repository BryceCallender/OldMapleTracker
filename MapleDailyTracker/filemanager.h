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

class FileManager
{
private:
    FileManager();
    static FileManager* instance;
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

    bool saveData(const QString& name, ResetChecker& resetChecker, QVector<Character*> characters) const;
    void clearAutoSave();
    SaveData loadData(const QString& name);
};

#endif // FILEMANAGER_H
