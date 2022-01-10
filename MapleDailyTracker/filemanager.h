#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>

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
    static FileManager* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new FileManager();
        }

        return instance;
    }

    bool saveData(ResetChecker& resetChecker, QVector<Character*> characters) const;
    SaveData loadData();
};

#endif // FILEMANAGER_H
