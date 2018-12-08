#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include "customtreeitem.h"

class Serializator
{
public:
    static Serializator& Instance();
    void AddlItem(CustomTreeItem* item, CustomTreeItem* parent = nullptr);
    void DeleteItem(CustomTreeItem* item, bool hasChild = false);
private:
    Serializator(const QString& file = "dotfile");
    Serializator(const Serializator& root) = delete;
    Serializator& operator=(const Serializator&) = delete;

    QFile m_dotFile;
    unsigned m_lastLine;
};

#endif // SERIALIZATOR_H
