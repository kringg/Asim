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

    virtual class QThumbnail* getThumbnail();

private:
    class QThumbnail* _thumbnail;
};

#endif // IMAGE_H
