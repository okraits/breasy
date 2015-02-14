#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QProgressBar>
#include <QTabWidget>
#include "webview.h"
#include <QVBoxLayout>
#include <QKeyEvent>

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

private slots:
    void urlEdit_returnPressed();
    void tabWidget_currentChanged(int index);
    void currWebView_loadProgress(int progress);
    void currWebView_loadFinished(bool ok);

private:
    QHBoxLayout* addressLayout;
    QVBoxLayout* mainLayout;
    QLineEdit* urlEdit;
    QProgressBar* loadProgress;
    QTabWidget* tabWidget;

    QUrl processUrl(QString url);
    void configureWebView();
    WebView* currentWebView();
    void setPageInfos(WebView* webView, bool windowTitle);
    void searchText(bool forward);
};

#endif // MAINWINDOW_H
