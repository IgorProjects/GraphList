#include "customtreeitem.h"

CustomTreeItem::CustomTreeItem(QString name, unsigned int level)
    : m_id(IdManager::Instance().GetId()), m_level(level)
{
    m_lineEdit = new QLineEdit();
    m_lineEdit->setText(name);
    m_lineEdit->setReadOnly(true);
    this->setText(0, name);
}

void CustomTreeItem::SetItemWidget(QTreeWidget *tree)
{
    tree->setItemWidget(this, 0, m_lineEdit);
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
    return m_lineEdit->text();
}
