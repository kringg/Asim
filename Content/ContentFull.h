#ifndef CONTENTFULL_H
#define CONTENTFULL_H

#include <QPixmap>
#include <QWidget>

class ContentFull : public QWidget
{
public:
    ContentFull(class Content* parent);
    virtual ~ContentFull() = default;

    // Mutators
    virtual void setImage(class ImagePath* path);

    // Operations
    virtual void onRotateL();
    virtual void onRotateR();
    virtual void onThumbsUp();
    virtual void onThumbsDown();

protected:
    // Operations
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    float _opacity;
    QPixmap _pixmap;
    class Content* _parent;
};

#endif // CONTENTFULL_H
