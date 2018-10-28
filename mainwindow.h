#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTreeWidgetItem* item = new QTreeWidgetItem();

private slots:


    void on_addButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
