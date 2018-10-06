#include <QScrollArea>
#include "Content.h"
#include "ContentFull.h"
#include "ContentThumbs.h"

Content::Content() :
    _contentFull(new ContentFull(this)),
    _contentThumbs(new ContentThumbs(this))
{
    // Empty...
}

Content::~Content()
{
    delete _contentFull;
    delete _contentThumbs;
}

/*
 * PUBLIC
 *  Initialization
 */
void Content::initFull(QScrollArea* scrollArea)
{
    scrollArea->setHidden(true);
    _scrollAreaFull = scrollArea;
    scrollArea->setWidget(_contentFull);
}

void Content::initThumbs(QScrollArea* scrollArea)
{
    _scrollAreaThumbs = scrollArea;
    scrollArea->setWidget(_contentThumbs);
}

/*
 * PUBLIC
 *  Mutators
 */
void Content::setPath(QString& path)
{
    _contentThumbs->setPath(path);
}

void Content::setSize(int size)
{
    _contentThumbs->setSize(size);
}

void Content::setView(int view)
{
    _contentThumbs->setView(view);
}

/*
 * PUBLIC
 *  Operations
 */
void Content::onReset()
{
    _contentThumbs->onReset();
}

void Content::onRotateL()
{
    _contentFull->onRotateL();
    _contentThumbs->onRotateL();
}

void Content::onRotateR()
{
    _contentFull->onRotateR();
    _contentThumbs->onRotateR();
}

void Content::onThumbsUp()
{
    _contentFull->onThumbsUp();
    _contentThumbs->onThumbsUp();
}

void Content::onThumbsDown()
{
    _contentFull->onThumbsDown();
    _contentThumbs->onThumbsDown();
}

void Content::onDoubleClick(class ImagePath* path)
{
    if (path == nullptr)
    {
        //_contentFull->setImage(fileName);
        _scrollAreaFull->setHidden(true);
        _scrollAreaThumbs->setHidden(false);
    }
    else
    {
        _contentFull->setImage(path);
        _scrollAreaFull->setHidden(false);
        _scrollAreaThumbs->setHidden(true);

    }
}
