#ifndef IMAGE_H
#define IMAGE_H

#include <QFileInfo>

/*
 * Image
 *  <|>
 *   |-- ImagePath
 *   |
 *   '-- ImageThumb
 */
class Image
{
public:
    Image(QFileInfo& info, class Content* parent);

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

    // Operations
    virtual void onEdit(QString& editAppPath);

private:
    class ImagePath* _path;
    class ImageThumb* _thumb;
};

#endif // IMAGE_H
