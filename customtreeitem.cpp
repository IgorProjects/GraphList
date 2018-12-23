#include "customtreeitem.h"
#include "serializator.h"

CustomTreeItem::CustomTreeItem(QString name, QTreeWidget* tree, unsigned int level)
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
    initTable();
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
    if (this->QTreeWidgetItem::parent() != nullptr) {
        static_cast<CustomTreeItem*>(this->QTreeWidgetItem::parent())->renameTableItem(this);
    }
}

void CustomTreeItem::initTable()
{
    m_table->setRowCount(2);
    m_table->setColumnCount(3);
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i < m_table->rowCount() - 1; i++) {
            m_table->setItem(i, j, new QTableWidgetItem());
        }
    }
    m_table->setItem(0, 0, new QTableWidgetItem(QString("Критерий")));
    m_table->setItem(0, 1, new QTableWidgetItem(QString("Вес")));
    m_table->setItem(0, 2, new QTableWidgetItem(QString("Суммы")));
    m_table->setItem(1, 0, new QTableWidgetItem());
    m_table->setItem(1, 1, new QTableWidgetItem());
    m_table->item(1, 0)->setFlags(m_table->item(1, 0)->flags() ^ Qt::ItemIsEditable);
    m_table->item(1, 0)->setBackgroundColor(QColor(192,192,192));
    m_table->item(1, 1)->setFlags(m_table->item(1, 1)->flags() ^ Qt::ItemIsEditable);
    m_table->item(1, 1)->setBackgroundColor(QColor(192,192,192));

}

void CustomTreeItem::addToTable(CustomTreeItem* item)
{
    m_table->setColumnCount(m_table->columnCount() + 1);
    m_table->setItem(0, m_table->columnCount() - 1, new QTableWidgetItem(item->GetLabel()));
}

bool CustomTreeItem::sumTableValues()
{
    double sum = 0;
    bool isIncorret = false;
    for (int i = 2; i < m_table->columnCount(); i++) {
        sum = 0;
        for (int j = 1; j < m_table->rowCount() - 1; j++) {
            if ((m_table->item(j, i) != nullptr) && (m_table->item(j, 1) != nullptr))
                sum += (m_table->item(j, i)->text().toDouble()) * (m_table->item(j, 1)->text().toDouble());
        }
        m_table->setItem(m_table->rowCount() - 1, i, new QTableWidgetItem(QString::number(sum, 'f', 2)));
    }
    sum = 0;
    for (int i = 1; i < m_table->rowCount() - 1; i++) {
        if (m_table->item(i, 1) != nullptr)
            sum += (m_table->item(i, 1)->text().toDouble());
    }
    m_table->setItem(m_table->rowCount() - 1, 1, new QTableWidgetItem(QString("Sum:") + QString::number(sum, 'f', 2)));
    if (qRound(sum*10000000)/10000000 != 1) {
        m_table->item(m_table->rowCount() - 1, 1)->setTextColor(QColor(255, 0, 0));
        isIncorret = true;
    } else {
        m_table->item(m_table->rowCount() - 1, 1)->setTextColor(QColor(0, 0, 0));
    }
    for (int i = 1; i < m_table->rowCount(); i++) {
        sum = 0;
        for (int j = 3; j < m_table->columnCount(); j++) {
            if (m_table->item(i, j) != nullptr)
                sum += (m_table->item(i, j)->text().toDouble());
        }
        m_table->setItem(i, 2, new QTableWidgetItem(QString::number(sum, 'f', 2)));
        if (qRound(sum*10000000)/10000000 != 1) {
            m_table->item(i, 2)->setTextColor(QColor(255, 0, 0));
            isIncorret = true;
        } else {
            m_table->item(i, 2)->setTextColor(QColor(0, 0, 0));
        }
    }
    if (isIncorret) {
        return false;
    }
}

void CustomTreeItem::deleteFromTable(CustomTreeItem* item)
{
    int removeIndex = this->indexOfChild(item);
    m_table->removeColumn(removeIndex + 3);
}

void CustomTreeItem::renameTableItem(CustomTreeItem* item)
{
    m_table->item(0, this->indexOfChild(item) + 3)->setText(item->GetLabel());
}

void CustomTreeItem::setCritCount(int count) {
    if (count > m_table->rowCount() - 2) {
        for (int i = m_table->rowCount() - 1; i < count + 1; i++) {
            m_table->insertRow(i);
        }
    } else {
        int j = m_table->rowCount() - 2;
        for (int i = j; i > count; i--) {
            m_table->removeRow(i);
        }
    }

}
