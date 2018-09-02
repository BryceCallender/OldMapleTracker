#ifndef MAPLEFILE_H
#define MAPLEFILE_H

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

class MapleFile
{
public:
    MapleFile();
    void loadFile();
    void saveFile();
private:
    QString fileName;
};

#endif // MAPLEFILE_H
