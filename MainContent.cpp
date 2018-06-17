#include "MainContent.h"
#include <QPushButton>
#include <Qt/QFlowLayout.h>

MainContent::MainContent() :
    _layout(new FlowLayout(this))
{
    for (int i = 0; i < 50; ++i)
    {
        _layout->addWidget(new QPushButton("YOUR MOM"));
    }
    setLayout(_layout);
}

MainContent::~MainContent()
{
    delete _layout;
}

#include <iostream>

void MainContent::setPath(QString& path)
{
    std::cout << "GOT HERE: " << path.toStdString() << std::endl;
}
