#include "filemanager.h"

FileManager *FileManager::instance = nullptr;

FileManager::FileManager()
{

}

bool FileManager::saveData(QVector<Character> characters) const
{
    QFile saveFile("SaveData.json");

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject json;
    json["lastOpened"] = QDateTime::currentDateTimeUtc().toString();

    QJsonArray charactersArray;
    for (Character &character: characters)
    {
        QJsonObject mapler;
        character.write(mapler);
        charactersArray.push_back(mapler);
    }

    json["characters"] = charactersArray;

    saveFile.write(QJsonDocument(json).toJson());

    return true;
}

SaveData FileManager::loadData()
{
    QFile loadFile("SaveData.json");
    SaveData data;

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return data;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    return data;
}
