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
    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(setNewTable()));
    connect(ui->pushButton, SIGNAL(pressed()), imageViewer, SLOT(zoomIn()));
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(unfocus(const QPoint&)));
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
    auto newItem = new CustomTreeItem(ui->newItemName->text(), ui->treeWidget, ui->tableWidget);
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
    static_cast<CustomTreeItem*>(ui->treeWidget->currentItem()->parent())->deleteFromTable(static_cast<CustomTreeItem*>(ui->treeWidget->currentItem()));
    ui->treeWidget->removeItemWidget(ui->treeWidget->currentItem(), 0);
    delete ui->treeWidget->currentItem();
}

void MainWindow::unfocus(const QPoint &pos)
{
    ui->treeWidget->setCurrentItem(nullptr);
}

void MainWindow::on_setCritNum_clicked()
{
    ui->tableWidget->setRowCount(ui->critNum->text().toInt());
}

void MainWindow::setNewTable()
{
    CustomTreeItem* tempItem = static_cast<CustomTreeItem*>(ui->treeWidget->currentItem());
    ui->horizontalLayout_6->addWidget(tempItem->m_table);
//    qInfo("%d", ui->horizontalLayout_6->count());
}

void MainWindow::on_pushButton_2_clicked()
{
    //todo: на эту кнопку либо на слот setNewTable сделать нормальный реплейс таблицы:
    //текущий виджет, который лежит в лейаут6, заменить на m_table, который лежит у currentItem
    ui->horizontalLayout_6->removeWidget(ui->horizontalLayout_6->takeAt(0)->widget());
//    ui->horizontalLayout_6->removeItem(ui->horizontalLayout_6->takeAt(1));
}

void MainWindow::on_pushButton_3_clicked()
{
    static_cast<CustomTreeItem*>(ui->treeWidget->currentItem())->sumTableValues();
}
