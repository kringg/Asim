#include <QtConcurrent/QtConcurrent>
#include <QDir>
#include "Image.h"
#include "ImageThumb.h"

Image::Image(QFileInfo& info, Content* parent) :
    _path(new ImagePath(info)),
    _thumb(new ImageThumb(_path, parent))
{
    // Empty...
}

/*
 * PUBLIC
 *  Accessors
 */
bool Image::isSelected()
{
    return _thumb->isSelected();
}

bool Image::isThumbsUp()
{
    return _path->isThumbsUp();
}

bool Image::isThumbsDown()
{
    return _path->isThumbsDown();
}

ImageThumb* Image::getThumbnail()
{
    return _thumb;
}

/*
 * PUBLIC
 *  Mutators
 */
void Image::setThumbsUp()
{
    if (_path->isThumbsDown())
    {
        _path->setThumbsUp();
        _thumb->repaint(); // Force draw update
        QDir().rename(_path->getPathThumbsDown(), _path->getPathThumbsUp());
    }
}

void Image::setThumbsDown()
{
    if (_path->isThumbsUp())
    {
        _path->setThumbsDown();
        _thumb->repaint(); // Force draw update
        QDir().rename(_path->getPathThumbsUp(), _path->getPathThumbsDown());
    }
}

void Image::setRotation(int rotation)
{
    QtConcurrent::run([=]()
    {
        QString path = _path->getPathImage();
        QImage image(path);

        QMatrix matrix;
        matrix.rotate(rotation);

        _thumb->setRotation(matrix);
        image.transformed(matrix).save(path);
    });
}

void Image::setSelected(bool isSelected)
{
    _thumb->setIsSelected(isSelected);
}
