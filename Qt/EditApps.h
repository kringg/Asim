#ifndef EDITAPPS_H
#define EDITAPPS_H

#include <QComboBox>

class EditApps : public QComboBox
{
public:
    EditApps(QWidget* parent);
    virtual ~EditApps() = default;

    virtual QString getCurAppPath();
};

#endif // EDITAPPS_H
