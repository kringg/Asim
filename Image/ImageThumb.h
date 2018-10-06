#ifndef IMAGETHUMB_H
#define IMAGETHUMB_H

#include <QLabel>
#include "ImagePath.h"

/*
 *
 */
class ImageThumb : public QLabel
{
public:
    ImageThumb(ImagePath& imgPath, QWidget* parent);
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

private:
    bool _isRejected;
    bool _isSelected;
    QPixmap* _pixmap;
    QString _pathThumb;

    static const int BORDER_SIZE;
    static const QList<int> IMAGE_SIZES;
};

#endif // IMAGETHUMB_H
