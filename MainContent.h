#ifndef MAINCONTENT_H
#define MAINCONTENT_H

#include <QWidget>

class MainContent : public QWidget
{
public:
    MainContent();
    virtual ~MainContent();

    virtual void setPath(QString& path);
    virtual void setSize(int size);

private:
    QString _lastPath;
    class FlowLayout* _layout;
    QList<class Image*> _images;
};

#endif // MAINCONTENT_H
