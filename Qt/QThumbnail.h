#ifndef QTHUMBNAIL_H
#define QTHUMBNAIL_H

#include <QLabel>
#include "ImagePath.h"

/*
 *
 */
class QThumbnail : public QLabel
{
public:
    QThumbnail(ImagePath& imgPath, QWidget* parent);
    virtual ~QThumbnail();

    // Accessors
    virtual bool isSelected();

    // Mutators
    virtual void setSizeId(int sizeId);
    virtual void setSelected(bool isSelected);
    virtual void setIsRejected(bool isRejected);

protected:
    // Operations
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
    bool _isRejected;
    bool _isSelected;
    QPixmap* _pixmap;

    static const int BORDER_SIZE;
    static const QList<int> IMAGE_SIZES;
};

#endif // QTHUMBNAIL_H
