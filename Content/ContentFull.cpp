#include <QPainter>
#include <QMouseEvent>
#include "Content.h"
#include "ContentFull.h"
#include "Image/ImagePath.h"

ContentFull::ContentFull(Content* parent) :
    _parent(parent)
{
    // Empty...
}

/*
 * PUBLIC
 *  Mutators
 */
void ContentFull::setImage(ImagePath* path)
{
    if (path != nullptr)
    {
        _pixmap.load(path->getPathImage());
        _opacity = (path->isThumbsUp()) ? 1.0 : 0.5;
    }
}

/*
 * PUBLIC
 *  Operations
 */
void ContentFull::onRotateL()
{
    QMatrix matrix;
    matrix.rotate(-90.0);
    _pixmap = _pixmap.transformed(matrix);
    repaint();
}

void ContentFull::onRotateR()
{
    QMatrix matrix;
    matrix.rotate(+90.0);
    _pixmap = _pixmap.transformed(matrix);
    repaint();
}

void ContentFull::onThumbsUp()
{
    _opacity = 1.0;
    repaint();
}

void ContentFull::onThumbsDown()
{
    _opacity = 0.5;
    repaint();
}

/*
 * PROTECTED
 *  Operations
 */
void ContentFull::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setOpacity(_opacity);

    QSize winSize(width(), height());
    QSize imgSize = _pixmap.size().scaled(winSize, Qt::KeepAspectRatio);

    float offsetX = (winSize.width() - imgSize.width()) / 2.0;
    float offsetY = (winSize.height() - imgSize.height()) / 2.0;
    painter.drawPixmap(QRect(QPoint(offsetX, offsetY), imgSize), _pixmap);

    QWidget::paintEvent(event);
}

void ContentFull::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _parent->onDoubleClick(nullptr);
    }
}
