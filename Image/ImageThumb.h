#ifndef IMAGETHUMB_H
#define IMAGETHUMB_H

#include <QLabel>
#include "ImagePath.h"
class Content;

/*
 *
 */
class ImageThumb : public QLabel
{
public:
    ImageThumb(ImagePath* imgPath, Content* parent);
    virtual ~ImageThumb();

    // Accessors
    virtual bool isSelected();

    // Mutators
    virtual void setRotation(QMatrix&);
    virtual void setSizeId(int sizeId);
    virtual void setIsRejected(bool isRejected);
    virtual void setIsSelected(bool isSelected);

protected:
    // Operations
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    bool _isRejected;
    bool _isSelected;
    Content* _parent;
    QPixmap* _pixmap;
    ImagePath* _path;

    static const int BORDER_SIZE;
    static const QList<int> IMAGE_SIZES;
};

#endif // IMAGETHUMB_H
