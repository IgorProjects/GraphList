#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidgetItem>
#include <QLineEdit>
#include "idmanager.h"

class CustomTreeItem : public QTreeWidgetItem
{
public:
    CustomTreeItem(QString name, unsigned int m_level = 1);
    void SetItemWidget(QTreeWidget* tree);
    unsigned int GetItemId() const;
    unsigned int GetLevelId() const;
    QString GetLabel() const;
private:
    QLineEdit* m_lineEdit;

    unsigned int m_id;
    unsigned int m_level;
};

#endif // CUSTOMTREEWIDGET_H
