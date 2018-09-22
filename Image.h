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
    Image(QString& imgPath, QWidget* parent = nullptr);

    // Accessors
    virtual bool isSelected();
    virtual bool isThumbsUp();
    virtual bool isThumbsDown();
    virtual class QThumbnail* getThumbnail();

    // Mutators
    virtual void setThumbsUp();
    virtual void setThumbsDown();
    virtual void setSelected(bool);

private:
    bool _isThumbsUp;
    class QThumbnail* _thumbnail;
};

#endif // IMAGE_H
