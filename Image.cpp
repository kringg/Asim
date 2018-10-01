#include <QDir>
#include "Image.h"
#include "Qt/QThumbnail.h"

Image::Image(ImagePath& imgPath, QWidget* parent) :
    _isThumbsUp(!imgPath.isHidden()),
    _pathThumbsUp(imgPath.getPathThumbsUp()),
    _pathThumbsDown(imgPath.getPathThumbsDown()),
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
        QDir().rename(_pathThumbsDown, _pathThumbsUp);
    }
}

void Image::setThumbsDown()
{
    if (_isThumbsUp)
    {
        _isThumbsUp = false;
        _thumbnail->setIsRejected(true);
        QDir().rename(_pathThumbsUp, _pathThumbsDown);
    }
}

void Image::setRotation(int rotation)
{
    QString path = (_isThumbsUp) ? _pathThumbsUp : _pathThumbsDown;
    QImage image(path);

    QMatrix matrix;
    matrix.rotate(rotation);

    _thumbnail->setRotation(matrix);
    image.transformed(matrix).save(path);
}


void Image::setSelected(bool isSelected)
{
    _thumbnail->setIsSelected(isSelected);
}
