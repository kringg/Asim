#include <QMouseEvent>
#include "Content.h"
#include "ContentFull.h"

ContentFull::ContentFull(Content* parent) :
    _parent(parent)
{

}

void ContentFull::setImage(QString& fileName)
{
    QPixmap pixmap(fileName);
    QLabel::setPixmap(pixmap);
}

/*
 * PROTECTED
 *  Operations
 */
void ContentFull::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _parent->onDoubleClick(QString());
    }
}
