#ifndef WEBVIEW
#define WEBVIEW

#include <QWebView>
#include <QMouseEvent>
#include <QNetworkRequest>
#include "mainwindow.h"

class MainWindow;

class WebPage : public QWebPage {
    Q_OBJECT

public:
    WebPage(QObject *parent = 0);
    MainWindow *mainWindow();

protected:
    bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);

private:
    friend class WebView;
    Qt::KeyboardModifiers keyboardModifiers;
    Qt::MouseButtons pressedMouseButtons;
};

class WebView : public QWebView {
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
