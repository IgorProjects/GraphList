#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QListWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->clear();
    this->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    QTreeWidgetItem* tempItem = new QTreeWidgetItem();
    QString tempName;
    QLineEdit* tempLineEdit = new QLineEdit();
    tempLineEdit->setText(ui->newItemName->text());
    if (ui->newItemName->text() == "") {
        QMessageBox::warning(this, "Ошибочка", "Введите имя элемента!");
        return;
    }
    tempName = ui->newItemName->text();
    tempItem->setText(0, tempName);
    QTreeWidgetItem* currentParentItem = ui->treeWidget->currentItem();
    if (currentParentItem != nullptr) {
        currentParentItem->addChild(tempItem);
        ui->treeWidget->setItemWidget(tempItem, 0, tempLineEdit);
        tempLineEdit->setReadOnly(true);
    } else {
        ui->treeWidget->addTopLevelItem(tempItem);
        ui->treeWidget->setItemWidget(tempItem, 0, tempLineEdit);
        tempLineEdit->setReadOnly(true);
    }
    ui->newItemName->clear();

}

void MainWindow::on_deleteButton_clicked()
{
    QTreeWidgetItem* tempItem = ui->treeWidget->currentItem();
    ui->treeWidget->removeItemWidget(tempItem, 0);
    delete tempItem;
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_treeWidget_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    ui->treeWidget->setCurrentItem(nullptr);
}
