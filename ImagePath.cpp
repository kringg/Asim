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
bool ImagePath::isHidden()
{
    return _isHidden;
}

QString ImagePath::getPath()
{
    return _path;
}

QString ImagePath::getPathThumbsUp()
{
    return _pathThumbsUp;
}

QString ImagePath::getPathThumbsDown()
{
    return _pathThumbsDown;
}

QString ImagePath::getPathThumbnail()
{
    return _pathThumbnail;
}
