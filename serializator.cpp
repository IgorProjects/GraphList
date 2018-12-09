#include "serializator.h"
#include "imageviewer.h"

Serializator::Serializator(const QString& file)
    : m_dotFile(file), m_lastLine(1)
{
    if (m_dotFile.exists())
        QFile::resize(file,0);
    if (m_dotFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&m_dotFile);
        textStream.setCodec("UTF-8");
        textStream << "digraph D {" << endl;
        textStream << endl;
        textStream << "}" << endl;
        m_dotFile.close();
    }
}

Serializator& Serializator::Instance()
{
    static Serializator theSingleInstance;
    return theSingleInstance;
}

void Serializator::AddlItem(CustomTreeItem *item, CustomTreeItem* parent, ImageViewer* iv)
{
    if (m_dotFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream textStream(&m_dotFile);
        textStream.setCodec("UTF-8");
        textStream.setGenerateByteOrderMark(false);
        QStringList tempList = textStream.readAll().split("\n");
        tempList.erase(tempList.end()-1);
        m_dotFile.close();
        QFile::resize(m_dotFile.fileName(),0);
        QString temp;
        QTextStream tempStream(&temp);
        tempStream.setCodec("UTF-8");
        tempStream.setGenerateByteOrderMark(false);
        tempStream << "{rank=" << item->GetLevelId()
                   << " " << item->GetItemId() << "}";
        tempList.insert(m_lastLine++, temp);
        temp = "";
        tempStream << item->GetItemId() << " [label=\""
                   << item->GetLabel() << "\"]";
        tempList.insert(m_lastLine++, temp);
        temp = "";
        if (parent == nullptr)
            tempStream << item->GetItemId() << ";";
        else
            tempStream << parent->GetItemId() << " -> " << item->GetItemId() << ";";
        tempList.insert(m_lastLine++, temp);
        if (m_dotFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            for (auto& str : tempList)
                textStream << str << endl;
            m_dotFile.close();
        }
        iv->loadFile("./dotengine/dot.png");
    }
}

void Serializator::DeleteItem(CustomTreeItem *item, bool hasChild, ImageViewer* iv)
{
    if (m_dotFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream textStream(&m_dotFile);
        textStream.setCodec("UTF-8");
        textStream.setGenerateByteOrderMark(false);
        QStringList tempList = textStream.readAll().split("\n");
        tempList.erase(tempList.end()-1);
        m_dotFile.close();
        QFile::resize(m_dotFile.fileName(),0);
        auto rx = QRegExp(QString::number(item->GetItemId()).append(" *"));
        rx.setPatternSyntax(QRegExp::Wildcard);
        auto idx = tempList.indexOf(rx, 1) - 1;
        tempList.erase(tempList.begin()+idx, tempList.begin()+idx+3);
        m_lastLine -= 3;
        if (hasChild)
        {
            rx = QRegExp(QString::number(item->GetItemId()).append(" -*"));
            rx.setPatternSyntax(QRegExp::Wildcard);
            while ((idx = tempList.indexOf(rx, 1)) != -1)
            {
                idx -= 2;
                tempList.erase(tempList.begin()+idx, tempList.begin()+idx+3);
                m_lastLine -= 3;
            }
        }
        if (m_dotFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            for (auto& str : tempList)
                textStream << str << endl;
            m_dotFile.close();
        }
        iv->loadFile("./dotengine/dot.png");
    }
}

void Serializator::RenameItem(CustomTreeItem *item)
{
    if (m_dotFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream textStream(&m_dotFile);
        textStream.setCodec("UTF-8");
        textStream.setGenerateByteOrderMark(false);
        QStringList tempList = textStream.readAll().split("\n");
        tempList.erase(tempList.end()-1);
        m_dotFile.close();
        QFile::resize(m_dotFile.fileName(),0);
        auto rx = QRegExp(QString::number(item->GetItemId()).append(" *"));
        rx.setPatternSyntax(QRegExp::Wildcard);
        auto idx = tempList.indexOf(rx, 1);
        tempList[idx] = QString::number(item->GetItemId())
                .append(" [label=\"")
                .append(item->GetLabel())
                .append("\"]");
        if (m_dotFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            for (auto& str : tempList)
                textStream << str << endl;
            m_dotFile.close();
        }
    }
}




































