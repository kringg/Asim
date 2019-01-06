#include "ImagePath.h"

const QString ImagePath::DIR_HIDDEN  = ".hidden";
const QString ImagePath::DIR_HISTORY = ".history";
const QString ImagePath::DIR_THUMBS  = ".thumbs";
const QString ImagePath::TOKEN_HISTORY = ".XXX.";

ImagePath::ImagePath(QFileInfo info)
{
    QString fileName = info.fileName();
    QString basePath = info.absolutePath();
    QString historyName = info.baseName() + TOKEN_HISTORY + info.suffix();
    _isHidden = (basePath.split("/").last() == DIR_HIDDEN);

    if (_isHidden)
    {
        QString parentPath = QFileInfo(basePath + "/../").canonicalFilePath();

        _pathThumbsUp = parentPath + "/" + fileName;
        _pathThumbsDown = basePath + "/" + fileName;
        _pathThumbnail  = parentPath + "/" + DIR_THUMBS + "/" + fileName;
        _pathHistory    = parentPath + "/" + DIR_HISTORY + "/" + historyName;
    }
    else
    {
        _pathThumbsUp = basePath + "/" + fileName;
        _pathThumbsDown = basePath + "/" + DIR_HIDDEN + "/" + fileName;
        _pathThumbnail  = basePath + "/" + DIR_THUMBS + "/" + fileName;
        _pathHistory    = basePath + "/" + DIR_HISTORY + "/" + historyName;
    }
}

/*
 * PUBLIC
 *  Accessors
 */
bool ImagePath::isThumbsUp() const
{
    return !_isHidden;
}

bool ImagePath::isThumbsDown() const
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

QString ImagePath::getPathHistory(int revId) const
{
    QString path = _pathHistory; // Remove const modifier
    QString revStr = QString::number(revId).rightJustified(3, '0');
    return path.replace(TOKEN_HISTORY, ".v" + revStr + ".");
}

/*
 * PUBLIC
 *  Mutators
 */
void ImagePath::setThumbsUp()
{
    _isHidden = false;
}

void ImagePath::setThumbsDown()
{
    _isHidden = true;
}
