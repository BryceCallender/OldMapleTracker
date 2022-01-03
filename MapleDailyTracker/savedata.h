#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <QDateTime>
#include <QVector>

#include "character.h"

struct SaveData
{
    bool closedWelcome;
    QDateTime lastOpened;
    QVector<Character*> characters;
};

#endif // SAVEDATA_H
