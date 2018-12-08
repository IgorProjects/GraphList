#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidgetItem>
#include <QLineEdit>
#include "clickablelabel.h"
#include "idmanager.h"

class CustomTreeItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:
    CustomTreeItem(QString name, QTreeWidget* tree, unsigned int m_level = 1);
    void SetLineEdit();
    void SetLabel();
    void FirstSetLabel();
    unsigned int GetItemId() const;
    unsigned int GetLevelId() const;
    QString GetLabel() const;
    ~CustomTreeItem();
public slots:
    void makeEditable();
    void makeNonEditable();
private:
    QLineEdit* m_lineEdit;
    ClickableLabel* m_label;
    QTreeWidget* m_tree;

    unsigned m_id;
    unsigned m_level;
};

#endif // CUSTOMTREEWIDGET_H
