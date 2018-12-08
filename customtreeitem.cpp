#include "customtreeitem.h"

CustomTreeItem::CustomTreeItem(QString nameS, QTreeWidget* tree, unsigned int level)
    : m_id(IdManager::Instance().GetId()), m_level(level)
{
    this->lineEdit = new QLineEdit();
    this->lineEdit->setText(nameS);
    this->name = this->lineEdit->text();
    tree->setItemWidget(this, 0, this->lineEdit);
}

unsigned int CustomTreeItem::GetItemId() const
{
    return m_id;
}

unsigned int CustomTreeItem::GetLevelId() const
{
    return m_level;
}

QString CustomTreeItem::GetLabel() const
{
    return name;
}
