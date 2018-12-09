#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <imageviewer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void unfocus(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    ImageViewer imageViewer;

};

#endif // MAINWINDOW_H
