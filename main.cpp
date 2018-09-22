#include <QThreadPool>
#include "MainWindow.h"


int main(int argc, char *argv[])
{
    QThreadPool::globalInstance()->setMaxThreadCount(4);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
