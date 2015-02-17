#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    // nothing to do here
}

Settings::~Settings()
{
    delete(userSettings);
}

void Settings::readSettings()
{
    userSettings = new QSettings("breasy", "breasy");
    // check for existing settings
    if (userSettings->allKeys().length() == 0)
    {
        // otherwise set default settings
        userSettings->setValue(SK_STARTPAGE, "http://google.de");
    }
}

void Settings::writeSettings()
{

}

QVariant Settings::getValue(const QString & key)
{
    return userSettings->value(key);
}

void Settings::setValue(const QString & key, const QVariant & value)
{
    userSettings->setValue(key, value);
}
