#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    // nothing to do here
}

Settings::~Settings()
{
    delete(userSettings);
    delete(searchStringList);
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
    else
    {
        // read searchstrings
        userSettings->beginGroup(SK_KEYWORDSEARCH);
        searchStringList = new QList<KeywordSearch>();
        QStringList searchKeys = userSettings->childKeys();
        // if searchstrings are defined
        if (searchKeys.size() != 0)
        {
            // append all keywords and searchstrings to the list
            for (int i = 0; i < searchKeys.size(); ++i)
                searchStringList->append(KeywordSearch(searchKeys.at(i),
                                         userSettings->value(searchKeys.at(i)).toString()));
        }
        userSettings->endGroup();
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

QString Settings::getSearchString(const QString & input)
{
    for (int i = 0; i < searchStringList->size(); ++i)
    {
        // if the input contains one of the keywords in the list
        if (input.startsWith(searchStringList->at(i).keyword + " "))
        {
            // get words to search for and insert them into the searchstring
            QString searchKeywords = input.right(input.size() - input.indexOf(" ") - 1);
            QString searchstring(searchStringList->at(i).searchstring);
            searchstring.replace("%s", searchKeywords);
            return searchstring;
        }
    }
    return "";
}
