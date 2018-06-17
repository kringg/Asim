#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    virtual void onConfigRootPath();
    virtual void onTreeIndex(QModelIndex index);

private:
    Ui::MainWindow *_gui;
    class MainContent* _content;
    class QFileSystemModel* _treeModel;
};

#endif // MAINWINDOW_H
