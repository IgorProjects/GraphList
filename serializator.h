#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

// for mac:
//#define SERIALIZE_COMMAND "dot -Tpng /Users/keet/dotfile -o /Users/keet/dot.png"
//for pc:
#define SERIALIZE_COMMAND "dotengine/dot.exe -Tpng dotengine/dotfile -o dotengine/dot.png"

#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QProcess>
#include "customtreeitem.h"

class Serializator : public QObject
{
    Q_OBJECT
public:
    static Serializator& Instance();
    void AddlItem(CustomTreeItem* item, CustomTreeItem* parent = nullptr);
    void DeleteItem(CustomTreeItem* item, bool hasChild = false);
    void RenameItem(CustomTreeItem* item);
signals:
    void fileChanged();
private:
//    for mac:
//    Serializator(const QString& file = "/Users/keet/dotfile");
//    for pc:
    Serializator(const QString& file = "dotengine/dotfile");
    Serializator(const Serializator& root) = delete;
    Serializator& operator=(const Serializator&) = delete;

    QFile m_dotFile;
    unsigned m_lastLine;
};

#endif // SERIALIZATOR_H
