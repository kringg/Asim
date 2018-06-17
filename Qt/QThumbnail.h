#ifndef QTHUMBNAIL_H
#define QTHUMBNAIL_H

#include <QPushButton>

class QThumbnail : public QPushButton
{
public:
    QThumbnail(QString& file, QWidget* parent = nullptr);
};

#endif // QTHUMBNAIL_H
