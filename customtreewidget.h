#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidgetItem>
#include <QLineEdit>

class customTreeWidget : public QTreeWidgetItem
{
public:
    customTreeWidget(QString name, QTreeWidget* tree);
private:
    QLineEdit* lineEdit;
    QString name;
};

#endif // CUSTOMTREEWIDGET_H
