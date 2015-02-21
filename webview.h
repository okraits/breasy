#ifndef WEBVIEW
#define WEBVIEW

#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QMouseEvent>
#include <QNetworkRequest>
#include "mainwindow.h"

class MainWindow;

class WebPage : public QWebEnginePage {
    Q_OBJECT

public:
    WebPage(QObject *parent = 0);
    MainWindow *parentWindow();

protected:
    //bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);

private:
    friend class WebView;
    Qt::KeyboardModifiers keyboardModifiers;
    Qt::MouseButtons pressedMouseButtons;
};

class WebView : public QWebEngineView {
    Q_OBJECT

public:
    WebView(QWidget *parent = 0);
    WebPage *webPage() const { return m_page; }

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    WebPage *m_page;
};

#endif // WEBVIEW
