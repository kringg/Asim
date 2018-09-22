#include "Image.h"
#include "Qt/QThumbnail.h"

Image::Image(QString& imgPath, QWidget* parent) :
    _isThumbsUp(true),
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

bool Image::isThumbsUp()
{
    return _isThumbsUp;
}

bool Image::isThumbsDown()
{
    return !_isThumbsUp;
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
    _isThumbsUp = true;
    _thumbnail->setIsRejected(false);
}

void Image::setThumbsDown()
{
    _isThumbsUp = false;
    _thumbnail->setIsRejected(true);
}

void Image::setSelected(bool isSelected)
{
    _thumbnail->setSelected(isSelected);
}
