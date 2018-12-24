#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QListWidget"
#include "serializator.h"
#include "customtreeitem.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->clear();
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    imageViewer = new ImageViewer(ui->scrollArea);
    ui->critNum->setVisible(false);
    ui->setCritNum->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_2->setVisible(false); //delete this if using mac
    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(setNewTable()));
//    connect(ui->pushButton, SIGNAL(pressed()), imageViewer, SLOT(zoomIn()));
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(unfocus(const QPoint&)));
    connect(ui->pushButton_2, SIGNAL(clicked()), imageViewer, SLOT(updateImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{    
    if (ui->newItemName->text() == "") {
        QMessageBox::warning(this, "Ошибочка", "Введите имя элемента!");
        return;
    }
    auto newItem = new CustomTreeItem(ui->newItemName->text(), ui->treeWidget);
    if (ui->treeWidget->currentItem() != nullptr) {
        Serializator::Instance().AddlItem(newItem, static_cast<CustomTreeItem*>(ui->treeWidget->currentItem()));
        ui->treeWidget->currentItem()->addChild(newItem);
        static_cast<CustomTreeItem*>(ui->treeWidget->currentItem())->addToTable(newItem);
    } else {
        Serializator::Instance().AddlItem(newItem);
        ui->treeWidget->addTopLevelItem(newItem);
    }
    newItem->FirstSetLabel();
    ui->newItemName->clear();
}

void MainWindow::on_deleteButton_clicked()
{
    Serializator::Instance().DeleteItem(static_cast<CustomTreeItem*>(ui->treeWidget->currentItem()));
    if (ui->treeWidget->currentItem()->parent() != nullptr) {
        static_cast<CustomTreeItem*>(ui->treeWidget->currentItem()->parent())->deleteFromTable(static_cast<CustomTreeItem*>(ui->treeWidget->currentItem()));
    }
    ui->treeWidget->removeItemWidget(ui->treeWidget->currentItem(), 0);
    delete ui->treeWidget->currentItem();
}

void MainWindow::unfocus(const QPoint &pos)
{
    ui->treeWidget->setCurrentItem(nullptr);
}

void MainWindow::on_setCritNum_clicked()
{
    if (ui->critNum->text().toInt() < 1) {
        QMessageBox::warning(this, "Ошибка!", "Количество критериев должно быть больше нуля!");
        return;
    }
    if (ui->treeWidget->currentItem() != nullptr) {
        static_cast<CustomTreeItem*>(ui->treeWidget->currentItem())->setCritCount(ui->critNum->text().toInt());
    }
    ui->critNum->clear();


}

void MainWindow::setNewTable()
{
    CustomTreeItem* tempItem = static_cast<CustomTreeItem*>(ui->treeWidget->currentItem());
    if (tempItem == nullptr) {
        for (int i = 0; i < ui->horizontalLayout_6->count(); ++i)
            ui->horizontalLayout_6->itemAt(i)->widget()->setVisible(false);
        ui->critNum->setVisible(false);
        ui->setCritNum->setVisible(false);
        ui->pushButton_3->setVisible(false);
        return;
    }
    ui->critNum->setVisible(true);
    ui->setCritNum->setVisible(true);
    ui->pushButton_3->setVisible(true);
    for (int i = 0; i < ui->horizontalLayout_6->count(); ++i)
        ui->horizontalLayout_6->itemAt(i)->widget()->setVisible(false);
    auto& idx = tempItem->layoutIndex;
    if (idx == -1)
    {
        idx = ui->horizontalLayout_6->count();
        ui->horizontalLayout_6->addWidget(tempItem->m_table);
    }
    else
    {
        ui->horizontalLayout_6->itemAt(idx)->widget()->setVisible(true);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if (!static_cast<CustomTreeItem*>(ui->treeWidget->currentItem())->sumTableValues()) {
        QMessageBox::warning(this, "Ошибка", "Проверьте введенные значения!");
    }
}

