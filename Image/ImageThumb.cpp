#include <QImageReader>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include "Content/Content.h"
#include "ImageThumb.h"

const int ImageThumb::BORDER_SIZE = 5;
const QList<int> ImageThumb::IMAGE_SIZES = {128, 160, 192, 224, 256};

ImageThumb::ImageThumb(ImagePath* imgPath, Content* parent) :
    _isRejected(imgPath->isHidden()),
    _isSelected(false),
    _parent(parent),
    _pixmap(new QPixmap()),
    _path(imgPath)
{
    QString pathImage = _path->getPathImage();
    QString pathThumb = _path->getPathThumbnail();

    // Does a thumbnail already exist?
    if (!QFileInfo(pathThumb).exists())
    {
        // No, configure fast image reader
        QImageReader reader(pathImage);
        QSize size = reader.size();
        int maxSize = IMAGE_SIZES.last();
        size.scale(maxSize, maxSize, Qt::KeepAspectRatio);
        reader.setScaledSize(size);

        // Load small image from disk
        QImage image = reader.read();
        image.save(pathThumb);

        // Populate pixmap with image
        _pixmap->convertFromImage(image);
    }
    else
    {
        // Yes, just load thumbnail
        _pixmap->load(pathThumb);
    }

    // Initialize thumbnail
    setIsSelected(false);
    setSizeId(3);
}

ImageThumb::~ImageThumb()
{
    delete _pixmap;
}

/*
 * PUBLIC
 *  Accessors
 */
bool ImageThumb::isSelected()
{
    return _isSelected;
}

/*
 * PUBLIC
 *  Mutators
 */
void ImageThumb::setRotation(QMatrix& matrix)
{
    QFile(_path->getPathThumbnail()).remove();
    *_pixmap = _pixmap->transformed(matrix);
    setPixmap(pixmap()->transformed(matrix));
}

void ImageThumb::setSizeId(int sizeId)
{
    int size = IMAGE_SIZES.at(qMax(1, qMin(5, sizeId)) - 1);
    setPixmap(_pixmap->scaled(size, size, Qt::KeepAspectRatio));
}

void ImageThumb::setIsRejected(bool isRejected)
{
    _isRejected = isRejected;
    repaint(); // Force update
}

void ImageThumb::setIsSelected(bool isSelected)
{
    if (isSelected)
    {
        //setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba(159, 246, 255, 255);");
        //setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba(121, 197, 255, 255);");
        setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba( 94, 149, 255, 255);");
        //setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba( 67,  91, 255, 255);");
        //setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba( 59,  48, 255, 255);");
    }
    else
    {
        setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba(0, 0, 0, 0);");
    }
    _isSelected = isSelected;
}

/*
 * PROTECTED
 *  Operations
 */
void ImageThumb::paintEvent(QPaintEvent* event)
{
    if (_isRejected)
    {
        QPainter painter(this);
        painter.setOpacity(0.5);
        painter.drawPixmap(BORDER_SIZE, BORDER_SIZE, *pixmap());
    }
    else
    {
        QLabel::paintEvent(event);
    }
}

void ImageThumb::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        bool isSelected = _isSelected;
        QTimer::singleShot(1, [=](){setIsSelected(!isSelected);});
    }
    QLabel::mousePressEvent(event);
}

void ImageThumb::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _parent->onDoubleClick(_path->getPathImage());
    }
    QLabel::mouseDoubleClickEvent(event);
}
