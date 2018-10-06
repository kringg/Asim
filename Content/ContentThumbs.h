#ifndef MAINCONTENT_H
#define MAINCONTENT_H

#include <QWidget>

class ContentThumbs : public QWidget
{
public:
    ContentThumbs(class Content* parent);
    virtual ~ContentThumbs();

    // Mutators
    virtual void setPath(QString& path);
    virtual void setSize(int size);
    virtual void setView(int view);

    // Operations
    virtual void onReset();
    virtual void onRotateL();
    virtual void onRotateR();
    virtual void onThumbsUp();
    virtual void onThumbsDown();

protected:
    // Operations
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
    QString _lastPath;
    class Content* _parent;
    class FlowLayout* _layout;
    QList<class Image*> _images;

    static const int TIMEOUT = 1000;
};

#endif // MAINCONTENT_H
