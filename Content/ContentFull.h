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
    virtual void setImage(QString& fileName);

    // Operations
    virtual void onRotateL();
    virtual void onRotateR();

protected:
    // Operations
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    QPixmap _pixmap;
    class Content* _parent;
};

#endif // CONTENTFULL_H
