#ifndef CONTENT_H
#define CONTENT_H

#include <QList>

/*
 * Content
 *  <|>
 *   |-- ContentFull
 *   |
 *   '-- ContentThumbs
 */
class Content
{
public:
    Content();
    virtual ~Content();

    // Initialization
    virtual void initFull(class QScrollArea* scrollArea);
    virtual void initThumbs(class QScrollArea* scrollArea);
    virtual void initElements(QList<class QWidget*> elements);

    // Mutators
    virtual void setPath(QString& path);
    virtual void setSize(int size);
    virtual void setView(int view);

    // Operations
    virtual void onReset();
    virtual void onRotateL();
    virtual void onRotateR();
    virtual void onThumbsUp();
    virtual void onThumbsDown();
    virtual void onDoubleClick(class ImagePath* path);

private:
    QList<class QWidget*> _elements;
    class ContentFull* _contentFull;
    class ContentThumbs* _contentThumbs;
    class QScrollArea* _scrollAreaFull;
    class QScrollArea* _scrollAreaThumbs;
};

#endif // CONTENT_H
