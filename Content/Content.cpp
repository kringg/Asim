#include <QScrollArea>
#include "Content.h"
#include "ContentFull.h"
#include "ContentThumbs.h"

Content::Content() :
    _contentFull(new ContentFull()),
    _contentThumbs(new ContentThumbs())
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
    scrollArea->hide();
    scrollArea->setWidget(_contentFull);
}

void Content::initThumbs(QScrollArea* scrollArea)
{
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
    _contentThumbs->onRotateL();
}

void Content::onRotateR()
{
    _contentThumbs->onRotateR();
}

void Content::onThumbsUp()
{
    _contentThumbs->onThumbsUp();
}

void Content::onThumbsDown()
{
    _contentThumbs->onThumbsDown();
}
