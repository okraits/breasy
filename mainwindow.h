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

private slots:
    void urlEdit_returnPressed();
    void tabWidget_currentChanged(int index);
    void currWebView_loadProgress(int progress);
    void currWebView_loadFinished(bool ok);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QHBoxLayout* addressLayout;
    QVBoxLayout* mainLayout;
    QLineEdit* urlEdit;
    QProgressBar* loadProgress;
    QTabWidget* tabWidget;
    QUrl evaluateURL(QString url);
    void configureWebView();
    WebView* currWebView();
    void updateURLandTitle(WebView* webView, bool windowTitle);
    void searchPage(bool forward);
};

#endif // MAINWINDOW_H
