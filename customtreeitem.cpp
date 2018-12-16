#include "customtreeitem.h"
#include "serializator.h"

CustomTreeItem::CustomTreeItem(QString name, QTreeWidget* tree, QTableWidget* table, unsigned int level)
    : m_tree(tree),
      m_id(IdManager::Instance().GetId()),
      m_label(new ClickableLabel(name)),
      m_lineEdit(new QLineEdit(name)),
      m_level(level),
      layoutIndex(-1)
{
    connect(m_label, SIGNAL(doubleClicked()), this, SLOT(makeEditable()));
    connect(m_lineEdit, SIGNAL(editingFinished()), this, SLOT(makeNonEditable()));
    m_table = new QTableWidget();
    initTable(table);
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
    //delete m_table;
    //delete m_label;
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
    static_cast<CustomTreeItem*>(this->QTreeWidgetItem::parent())->renameTableItem(this);
}

void CustomTreeItem::initTable(QTableWidget* table)
{
    m_table->setRowCount(table->rowCount() + 2);
    m_table->setColumnCount(2);
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i < m_table->rowCount() - 1; i++) {
            //TODO: fix read access violation if table is clear
            m_table->setItem(i, j, new QTableWidgetItem(table->item(i - 1, j)->text()));
        }
    }
    m_table->setItem(0, 0, new QTableWidgetItem(QString("Критерий")));
    m_table->setItem(0, 1, new QTableWidgetItem(QString("Вес")));
}

void CustomTreeItem::addToTable(CustomTreeItem* item)
{
    m_table->setColumnCount(m_table->columnCount() + 1);
    m_table->setItem(0, m_table->columnCount() - 1, new QTableWidgetItem(item->GetLabel()));
}

void CustomTreeItem::sumTableValues()
{
    double sum = 0;
    for (int i = 2; i < m_table->columnCount(); i++) {
        sum = 0;
        for (int j = 1; j < m_table->rowCount() - 1; j++) {
            if (m_table->item(j, i) != nullptr)
                sum += m_table->item(j, i)->text().toDouble();
        }
        m_table->setItem(m_table->rowCount() - 1, i, new QTableWidgetItem(QString::number(sum, 'f', 2)));
    }
}

void CustomTreeItem::deleteFromTable(CustomTreeItem* item)
{
    int removeIndex = this->indexOfChild(item);
    m_table->removeColumn(removeIndex + 2);
}

void CustomTreeItem::renameTableItem(CustomTreeItem* item)
{
    m_table->item(0, this->indexOfChild(item) + 2)->setText(item->GetLabel());
}
