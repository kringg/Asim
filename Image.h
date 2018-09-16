#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QWidget>

/*
 *
 */
class Image
{
public:
    Image(QString& imgPath, QWidget* parent);

    // Accessors
    virtual bool isSelected();
    virtual class QThumbnail* getThumbnail();

    // Mutators
    virtual void setThumbsUp();
    virtual void setThumbsDown();

private:
    class QThumbnail* _thumbnail;
};

#endif // IMAGE_H
