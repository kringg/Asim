#include <QPainter>
#include <QMouseEvent>
#include "Content.h"
#include "ContentFull.h"

ContentFull::ContentFull(Content* parent) :
    _parent(parent)
{
    // Empty...
}

/*
 * PUBLIC
 *  Mutators
 */
void ContentFull::setImage(QString& fileName)
{
    _pixmap.load(fileName);
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

/*
 * PROTECTED
 *  Operations
 */
void ContentFull::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
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
        _parent->onDoubleClick(QString());
    }
}
