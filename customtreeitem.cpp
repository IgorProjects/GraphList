#include "customtreeitem.h"
#include "serializator.h"

CustomTreeItem::CustomTreeItem(QString name, QTreeWidget* tree, unsigned int level)
    : m_tree(tree),
      m_id(IdManager::Instance().GetId()),
      m_label(new ClickableLabel(name)),
      m_lineEdit(new QLineEdit(name)),
      m_level(level)
{
    connect(m_label, SIGNAL(doubleClicked()), this, SLOT(makeEditable()));
    connect(m_lineEdit, SIGNAL(editingFinished()), this, SLOT(makeNonEditable()));
}

void CustomTreeItem::SetLineEdit()
{
    m_label->disconnect();
    m_label = new ClickableLabel(m_label->text());
    connect(m_label, SIGNAL(doubleClicked()), this, SLOT(makeEditable()));
    m_tree->setItemWidget(this, 0, m_lineEdit);
}

void CustomTreeItem::SetLabel()
{
    m_lineEdit->disconnect();
    m_lineEdit = new QLineEdit(m_lineEdit->text());
    connect(m_lineEdit, SIGNAL(editingFinished()), this, SLOT(makeNonEditable()));
    m_tree->setItemWidget(this, 0, m_label);
}

void CustomTreeItem::FirstSetLabel()
{
    m_tree->setItemWidget(this, 0, m_label);
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
    return m_label->text();
}

CustomTreeItem::~CustomTreeItem()
{
    delete m_lineEdit;
    delete m_label;
}

void CustomTreeItem::makeEditable()
{
    SetLineEdit();
}

void CustomTreeItem::makeNonEditable()
{
    m_label->setText(m_lineEdit->text());
    SetLabel();
    Serializator::Instance().RenameItem(this);
}
