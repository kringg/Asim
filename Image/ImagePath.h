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
    virtual bool isThumbsUp() const; // Is the image thumbs-up? This is the default state
    virtual bool isThumbsDown() const; // Is the image thumbs-down? This means the image is hidden
    virtual QString getPathImage() const; // Current full-sized image path, adapts according to thumbs-state
    virtual QString getPathThumbsUp() const; // Full-sized image path, if image is thumbs-up
    virtual QString getPathThumbsDown() const; // Full-sized image path, if image is thumbs-down
    virtual QString getPathThumbnail() const; // Thumbnail-sized image path (constant regardless of thumbs-up or thumbs-down)
    virtual QString getPathHistory(int revId) const; // Theoretical path to revision (history) given by revId

    // Mutators
    virtual void setThumbsUp();
    virtual void setThumbsDown();

protected:
    static const QString DIR_HIDDEN;
    static const QString DIR_HISTORY;
    static const QString DIR_THUMBS;

private:
    bool _isHidden;
    QString _pathHistory;
    QString _pathThumbsUp;
    QString _pathThumbsDown;
    QString _pathThumbnail;

    static const QString TOKEN_HISTORY;
};

#endif // IMAGEPATH_H
