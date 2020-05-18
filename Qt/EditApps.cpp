#include "EditApps.h"


EditApps::EditApps(QWidget* parent) :
    QComboBox(parent)
{
    // Empty...
}

QString EditApps::getCurAppPath()
{
    return "mspaint.exe";
}
