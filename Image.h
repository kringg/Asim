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
    virtual bool isThumbsUp();
    virtual bool isThumbsDown();
    virtual class QThumbnail* getThumbnail();

    // Mutators
    virtual void setThumbsUp();
    virtual void setThumbsDown();

private:
    bool _isThumbsUp;
    class QThumbnail* _thumbnail;
};

#endif // IMAGE_H
