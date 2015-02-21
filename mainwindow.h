#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSettings>
#include <QLineEdit>
#include <QProgressBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QKeyEvent>
#include "settings.h"
#include "webview.h"

class Settings;
class WebView;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void processCliUrls(int argc, char *argv[]);
    void addTab(QString url);

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void urlEdit_returnPressed();
    void tabWidget_currentChanged(int index);
    void currWebView_loadProgress(int progress);
    void currWebView_loadFinished(bool ok);

private:
    Settings* settings;
    QHBoxLayout* addressLayout;
    QVBoxLayout* mainLayout;
    QLineEdit* urlEdit;
    QProgressBar* loadProgress;
    QTabWidget* tabWidget;

    QUrl processUrl(QString url);
    WebView* currentWebView();
    void setPageInfos(WebView* webView, bool windowTitle);
    void searchText(bool forward);
};

#endif // MAINWINDOW_H
