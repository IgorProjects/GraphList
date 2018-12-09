#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QListWidget"
#include "serializator.h"
#include "customtreeitem.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->clear();
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    imageViewer->show();
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(unfocus(const QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{    
    ImageViewer* iv = this->imageViewer;
    if (ui->newItemName->text() == "") {
        QMessageBox::warning(this, "Ошибочка", "Введите имя элемента!");
        return;
    }
    auto newItem = new CustomTreeItem(ui->newItemName->text(), ui->treeWidget);
    if (ui->treeWidget->currentItem() != nullptr) {
        Serializator::Instance().AddlItem(newItem, static_cast<CustomTreeItem*>(ui->treeWidget->currentItem()), imageViewer);
        ui->treeWidget->currentItem()->addChild(newItem);
    } else {
        Serializator::Instance().AddlItem(newItem, nullptr, imageViewer);
        ui->treeWidget->addTopLevelItem(newItem);
    }
    newItem->FirstSetLabel();
    ui->newItemName->clear();
}

void MainWindow::on_deleteButton_clicked()
{
    Serializator::Instance().DeleteItem(static_cast<CustomTreeItem*>(ui->treeWidget->currentItem()), false, imageViewer);
    ui->treeWidget->removeItemWidget(ui->treeWidget->currentItem(), 0);
    delete ui->treeWidget->currentItem();
}

void MainWindow::unfocus(const QPoint &pos)
{
    ui->treeWidget->setCurrentItem(nullptr);
}
