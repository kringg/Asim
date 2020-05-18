#ifndef CONTENT_H
#define CONTENT_H

#include <QList>

/*
 * Content
 *  <|>
 *   |-- ContentFull
 *   |
 *   '-- ContentThumbs
 *
 * Note: All heavy-lifting is done in ContentThumbs, ContentFull is strictly a viewer.
 */
class Content
{
public:
    Content();
    virtual ~Content();

    // Initialization
    virtual void initFull(class QScrollArea* scrollArea, QList<class QWidget*> elements);
    virtual void initThumbs(class QScrollArea* scrollArea, QList<class QWidget*> elements);

    // Mutators
    virtual void setPath(QString path);
    virtual void setSize(int size);
    virtual void setView(int view);

    // Operations
    virtual void onEdit(QString editAppPath);
    virtual void onNext();
    virtual void onPrev();
    virtual void onReset();
    virtual void onRotateL();
    virtual void onRotateR();
    virtual void onThumbsUp();
    virtual void onThumbsDown();
    virtual void onDoubleClick(class ImagePath* path);

private:
    class ContentFull* _contentFull;
    class ContentThumbs* _contentThumbs;

    class QScrollArea* _scrollAreaFull;
    class QScrollArea* _scrollAreaThumbs;

    QList<class QWidget*> _elementsFull;
    QList<class QWidget*> _elementsThumbs;
};

#endif // CONTENT_H
