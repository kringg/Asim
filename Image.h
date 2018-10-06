#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QWidget>
#include "ImagePath.h"

/*
 *
 */
class Image
{
public:
    Image(ImagePath& imgPath, QWidget* parent = nullptr);

    // Accessors
    virtual bool isSelected();
    virtual bool isThumbsUp();
    virtual bool isThumbsDown();
    virtual class ImageThumb* getThumbnail();

    // Mutators
    virtual void setThumbsUp();
    virtual void setThumbsDown();
    virtual void setRotation(int);
    virtual void setSelected(bool);

private:
    bool _isThumbsUp;
    QString _pathThumbsUp;
    QString _pathThumbsDown;
    class ImageThumb* _thumbnail;
};

#endif // IMAGE_H
