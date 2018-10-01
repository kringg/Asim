#include <QDir>
#include "Image.h"
#include "Qt/QThumbnail.h"

Image::Image(ImagePath& imgPath, QWidget* parent) :
    _isThumbsUp(!imgPath.isHidden()),
    _imgPathThumbsUp(imgPath.getPathThumbsUp()),
    _imgPathThumbsDown(imgPath.getPathThumbsDown()),
    _thumbnail(new QThumbnail(imgPath, parent))
{
    // Empty...
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
    if (!_isThumbsUp)
    {
        _isThumbsUp = true;
        _thumbnail->setIsRejected(false);
        QDir().rename(_imgPathThumbsDown, _imgPathThumbsUp);
    }
}

void Image::setThumbsDown()
{
    if (_isThumbsUp)
    {
        _isThumbsUp = false;
        _thumbnail->setIsRejected(true);
        QDir().rename(_imgPathThumbsUp, _imgPathThumbsDown);
    }
}

void Image::setSelected(bool isSelected)
{
    _thumbnail->setSelected(isSelected);
}
