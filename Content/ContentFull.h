#ifndef CONTENTFULL_H
#define CONTENTFULL_H

#include <QLabel>

class ContentFull : public QLabel
{
public:
    ContentFull(class Content* parent);

    virtual void setImage(QString& fileName);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    class Content* _parent;
};

#endif // CONTENTFULL_H
