#include "filemanager.h"

bool FileManager::closedWelcome = false;
FileManager *FileManager::instance = nullptr;
QString FileManager::saveFile = QString::fromUtf8("SaveData.json");
QString FileManager::autosaveFile = QString::fromUtf8("AutoSave.json");

FileManager::FileManager()
{

}

bool FileManager::saveData(const QString& name, ResetChecker& resetChecker, QVector<Character*> characters) const
{
    QFile saveFile(name);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning() << "Couldn't open save file.";
        return false;
    }

    QJsonObject json;
    json["closedWelcome"] = FileManager::closedWelcome;
    json["lastOpened"] = QDateTime::currentDateTimeUtc().toString();
    json["nextDailyReset"] = resetChecker.timeTillDailyReset().toString();
    json["nextWedWeeklyReset"] = resetChecker.timeTillWeeklyReset().toString();
    json["nextMonWeeklyReset"] = resetChecker.timeTillWeeklyReset(Qt::Monday).toString();

    QJsonArray charactersArray;
    int index = 1;
    for (Character* character: characters)
    {
        QJsonObject mapler;
        character->setOrder(index++);
        character->write(mapler);
        charactersArray.push_back(mapler);
    }

    json["characters"] = charactersArray;

    saveFile.write(QJsonDocument(json).toJson());

    return true;
}

void FileManager::clearAutoSave()
{
    QFile autoSave("AutoSave.json");
    autoSave.resize(0);
}

SaveData FileManager::loadData(const QString &name)
{
    QFile loadFile(name);
    SaveData data;

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return data;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    if (json.contains("closedWelcome") && json["closedWelcome"].isBool())
    {
        data.closedWelcome = json["closedWelcome"].toBool();
        FileManager::closedWelcome = data.closedWelcome;
    }

    if (json.contains("lastOpened") && json["lastOpened"].isString())
    {
        data.lastOpened = QDateTime::fromString(json["lastOpened"].toString());
    }

    if (json.contains("nextDailyReset") && json["nextDailyReset"].isString())
    {
        data.nextDailyReset = QDateTime::fromString(json["nextDailyReset"].toString());
    }

    if (json.contains("nextWedWeeklyReset") && json["nextWedWeeklyReset"].isString())
    {
        data.nextWedWeeklyReset = QDateTime::fromString(json["nextWedWeeklyReset"].toString());
    }

    if (json.contains("nextMonWeeklyReset") && json["nextMonWeeklyReset"].isString())
    {
        data.nextMonWeeklyReset = QDateTime::fromString(json["nextMonWeeklyReset"].toString());
    }

    QVector<Character*> characters;
    if (json.contains("characters") && json["characters"].isArray())
    {
        QJsonArray jsonArray = json["characters"].toArray();
        for (int i = 0; i < jsonArray.size(); ++i)
        {
            QJsonObject object = jsonArray[i].toObject();
            Character* character = new Character();
            character->read(object);
            characters.push_back(character);
        }
    }

    std::sort(characters.begin(), characters.end(), [](const Character* lhs, const Character* rhs) {
        return lhs->getOrder() < rhs->getOrder();
    });

    data.characters = characters;

    return data;
}
