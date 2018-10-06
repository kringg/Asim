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
public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

protected:
    virtual void loadSettings();
    virtual void loadSettings(QString fileName);
    virtual void saveSettings();
    virtual void saveSettings(QString fileName);
    virtual void resetSettings(QString fileName);

protected slots:
    virtual void setRootPath();
    virtual void setRootPath(QString rootPath);
    virtual void setTreeIndex(QModelIndex index);

private:
    bool _doSave;
    Ui::MainWindow *_gui;
    class MainContent* _content;
    class QFileSystemModel* _treeModel;
    class QSortFilterProxyModel* _treeProxy;

    static const QString SETTINGS_FILE_NAME;
};

#endif // MAINWINDOW_H
