#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QListWidget"
#include "customtreewidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->clear();
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
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

    if (ui->treeWidget->currentItem() != nullptr) {
        ui->treeWidget->currentItem()->addChild(new customTreeWidget(ui->newItemName->text(), ui->treeWidget));
    } else {
        ui->treeWidget->addTopLevelItem(new customTreeWidget(ui->newItemName->text(), ui->treeWidget));
    }

    ui->newItemName->clear();
}

void MainWindow::on_deleteButton_clicked()
{
    ui->treeWidget->removeItemWidget(ui->treeWidget->currentItem(), 0);
    delete ui->treeWidget->currentItem();
}

void MainWindow::unfocus(const QPoint &pos)
{
    ui->treeWidget->setCurrentItem(nullptr);
}
