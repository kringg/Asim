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
    virtual void initFull(class QScrollArea* scrollArea);
    virtual void initThumbs(class QScrollArea* scrollArea);
    virtual void initElements(QList<class QWidget*> elements);

    // Mutators
    virtual void setEdit(QString& edit);
    virtual void setPath(QString& path);
    virtual void setSize(int size);
    virtual void setView(int view);

    // Operations
    virtual void onEdit();
    virtual void onNext();
    virtual void onPrev();
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
