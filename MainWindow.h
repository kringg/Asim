#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}

/*
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

protected slots:
    virtual void browseRootPath();
    virtual void setRootPath(QString rootPath);
    virtual void setTreeIndex(QModelIndex index);

private:
    Ui::MainWindow *_gui;
    class MainContent* _content;
    class QFileSystemModel* _treeModel;
};

#endif // MAINWINDOW_H
