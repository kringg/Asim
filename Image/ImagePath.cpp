#include "ImagePath.h"

const QString ImagePath::DIR_HIDDEN = ".hidden";
const QString ImagePath::DIR_THUMBS = ".thumbs";

ImagePath::ImagePath(QFileInfo info) :
    _path(info.absoluteFilePath())
{
    QString fileName = info.fileName();
    QString basePath = info.absolutePath();
    _isHidden = (basePath.split("/").last() == DIR_HIDDEN);

    if (_isHidden)
    {
        QString parentPath = QFileInfo(basePath + "/../").canonicalFilePath();

        _pathThumbsUp = parentPath + "/" + fileName;
        _pathThumbsDown = basePath + "/" + fileName;
        _pathThumbnail = parentPath + "/" + DIR_THUMBS + "/" + fileName;
    }
    else
    {
        _pathThumbsUp = basePath + "/" + fileName;
        _pathThumbsDown = basePath + "/" + DIR_HIDDEN + "/" + fileName;
        _pathThumbnail  = basePath + "/" + DIR_THUMBS + "/" + fileName;
    }
}

/*
 * PUBLIC
 *  Accessors
 */
bool ImagePath::isHidden() const
{
    return _isHidden;
}

QString ImagePath::getPathImage() const
{
    if (_isHidden)
    {
        return _pathThumbsDown;
    }
    else
    {
        return _pathThumbsUp;
    }
}

QString ImagePath::getPathThumbsUp() const
{
    return _pathThumbsUp;
}

QString ImagePath::getPathThumbsDown() const
{
    return _pathThumbsDown;
}

QString ImagePath::getPathThumbnail() const
{
    return _pathThumbnail;
}

/*
 * PUBLIC
 *  Mutators
 */
void ImagePath::setIsHidden(bool isHidden)
{
    _isHidden = isHidden;
}
