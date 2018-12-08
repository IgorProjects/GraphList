#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidgetItem>
#include <QLineEdit>
#include "idmanager.h"

class CustomTreeItem : public QTreeWidgetItem
{
public:
    CustomTreeItem(QString name, QTreeWidget* tree, unsigned int m_level = 1);
    unsigned int GetItemId() const;
    unsigned int GetLevelId() const;
    QString GetLabel() const;
private:
    QLineEdit* lineEdit;
    QString name;

    unsigned int m_id;
    unsigned int m_level;
};

#endif // CUSTOMTREEWIDGET_H
