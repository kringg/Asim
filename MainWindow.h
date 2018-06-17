#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *_gui;
    class QFileSystemModel* _treeModel;
};

#endif // MAINWINDOW_H
