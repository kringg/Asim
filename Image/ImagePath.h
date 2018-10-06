#ifndef IMAGEPATH_H
#define IMAGEPATH_H

#include <QString>
#include <QFileInfo>

/*
 * Encapsulate various image paths.
 */
class ImagePath
{
friend class ContentThumbs;

public:
    ImagePath(QFileInfo info);
    virtual ~ImagePath() = default;

    // Accessors
    virtual bool isHidden() const;
    virtual QString getPath() const;
    virtual QString getPathThumbsUp() const;
    virtual QString getPathThumbsDown() const;
    virtual QString getPathThumbnail() const;

protected:
    static const QString DIR_HIDDEN;
    static const QString DIR_THUMBS;

private:
    bool _isHidden;
    QString _path;
    QString _pathThumbsUp;
    QString _pathThumbsDown;
    QString _pathThumbnail;
};

#endif // IMAGEPATH_H
