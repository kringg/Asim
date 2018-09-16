#include "Image.h"
#include "Qt/QThumbnail.h"

Image::Image(QString& imgPath, QWidget* parent) :
    _thumbnail(new QThumbnail(imgPath, parent))
{

}


QThumbnail* Image::getThumbnail()
{
    return _thumbnail;
}
