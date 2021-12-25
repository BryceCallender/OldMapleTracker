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
    QJsonObject json = loadDoc.object();

    if (json.contains("lastOpened") && json["lastOpened"].isString())
    {
        data.lastOpened = QDateTime::fromString(json["lastOpened"].toString());
    }

    QVector<Character> characters;
    if (json.contains("characters") && json["characters"].isArray())
    {
        QJsonArray jsonArray = json["characters"].toArray();
        for (int i = 0; i < jsonArray.size(); ++i)
        {
            QJsonObject object = jsonArray[i].toObject();
            Character character;
            character.read(object);
            characters.push_back(character);
        }
    }

    data.characters = characters;

    return data;
}
