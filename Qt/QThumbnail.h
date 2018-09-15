#ifndef QTHUMBNAIL_H
#define QTHUMBNAIL_H

#include <QLabel>

/*
 *
 */
class QThumbnail : public QLabel
{
public:
    QThumbnail(QString& file, QWidget* parent = nullptr);
    virtual ~QThumbnail();

    //
    virtual void setSizeId(int sizeId);

private:
    QPixmap* _pixmap;
    QList<int> _sizes;
};

#endif // QTHUMBNAIL_H
