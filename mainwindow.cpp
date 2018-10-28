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
    QTreeWidgetItem* item = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(item);
    ui->treeWidget->topLevelItem(0)->setText(0, "Tree");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_addButton_clicked()
{
    QTreeWidgetItem* tempItem = new QTreeWidgetItem();
    QString tempName;
    if (ui->newItemName->text() == "") {
        QMessageBox::warning(this, "Ошибочка", "Введите имя элемента!");
        return;
    }
    tempName = ui->newItemName->text();
    tempItem->setText(0, tempName);
    QTreeWidgetItem* currentParentItem = ui->treeWidget->currentItem();
    if (currentParentItem != nullptr) {
        currentParentItem->addChild(tempItem);
    } else {
        ui->treeWidget->addTopLevelItem(tempItem);
    }
    ui->newItemName->clear();
}

void MainWindow::on_deleteButton_clicked()
{
    QTreeWidgetItem* tempItem = ui->treeWidget->currentItem();
    ui->treeWidget->removeItemWidget(tempItem, 0);
    delete tempItem;
}
