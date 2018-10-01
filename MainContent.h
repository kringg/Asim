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

    virtual void onRotateL();
    virtual void onRotateR();
    virtual void onThumbsUp();
    virtual void onThumbsDown();
    virtual void onViewMode(int viewMode);

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
    QString _lastPath;
    class FlowLayout* _layout;
    QList<class Image*> _images;

    static const int TIMEOUT = 1000;
};

#endif // MAINCONTENT_H
