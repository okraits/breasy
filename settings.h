#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QList>
#include <QStringList>
#include "mainwindow.h"

#define SK_STARTPAGE        "global/startpage"
#define SK_ZOOM             "global/zoom"
#define SK_KEYWORDSEARCH    "keywordsearch"

struct KeywordSearch
{
    KeywordSearch(){}
    KeywordSearch(QString keywordIn, QString searchstringIn)
    {
        keyword = keywordIn;
        searchstring = searchstringIn;
    }

    QString keyword;
    QString searchstring;
};

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
    QString getSearchString(const QString & input);

private:
    QSettings* userSettings;
    QList<KeywordSearch>* searchStringList;
};

#endif // SETTINGS_H
