#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "mainwindow.h"

#define SK_STARTPAGE "global/startpage"

class Settings : public QObject
{
    Q_OBJECT

public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    void readSettings();
    void writeSettings();
    QVariant getValue(const QString & key);
    void setValue(const QString & key, const QVariant & value);

private:
    QSettings* userSettings;
};

#endif // SETTINGS_H
