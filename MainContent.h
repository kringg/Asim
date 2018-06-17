#ifndef MAINCONTENT_H
#define MAINCONTENT_H

#include <QWidget>

class MainContent : public QWidget
{
public:
    MainContent();
    virtual ~MainContent();

    virtual void setPath(QString& path);

private:
    class FlowLayout* _layout;
};

#endif // MAINCONTENT_H
