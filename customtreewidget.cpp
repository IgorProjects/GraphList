#include "customtreewidget.h"

customTreeWidget::customTreeWidget(QString nameS, QTreeWidget* tree)
{
    this->lineEdit = new QLineEdit();
    this->lineEdit->setText(nameS);
    this->name = this->lineEdit->text();
    tree->setItemWidget(this, 0, this->lineEdit);
}
