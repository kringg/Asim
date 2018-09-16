#include "Image.h"
#include "Qt/QThumbnail.h"

Image::Image(QString& imgPath, QWidget* parent) :
    _thumbnail(new QThumbnail(imgPath, parent))
{

}

/*
 * PUBLIC
 *  Accessors
 */
bool Image::isSelected()
{
    return _thumbnail->isSelected();
}

QThumbnail* Image::getThumbnail()
{
    return _thumbnail;
}

/*
 * PUBLIC
 *  Mutatos
 */
void Image::setThumbsUp()
{
    _thumbnail->setIsRejected(false);
}

void Image::setThumbsDown()
{
    _thumbnail->setIsRejected(true);
}
