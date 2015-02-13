#include "webview.h"

WebPage::WebPage(QObject *parent)
    : QWebPage(parent)
    , pressedMouseButtons(Qt::NoButton)
{
}

MainWindow *WebPage::mainWindow()
{
    QObject *w = this->parent();
    while (w) {
        if (MainWindow *mw = qobject_cast<MainWindow*>(w))
            return mw;
        w = w->parent();
    }
    // TODO: singleton
    return new MainWindow();
}

bool WebPage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type)
{
    // CTRL modifier or middle mousebutton -> open url in new tab
    if (type == QWebPage::NavigationTypeLinkClicked
        && (keyboardModifiers & Qt::ControlModifier
            || pressedMouseButtons == Qt::MidButton)) {
        mainWindow()->addTab(request.url().toString());
        keyboardModifiers = Qt::NoModifier;
        pressedMouseButtons = Qt::NoButton;
        return false;
    }
    return QWebPage::acceptNavigationRequest(frame, request, type);
}

WebView::WebView(QWidget* parent)
    : QWebView(parent)
    , m_page(new WebPage(this))
{
    setPage(m_page);
}

void WebView::mousePressEvent(QMouseEvent *event)
{
    // remember the mouse button and modifier key pressed
    m_page->pressedMouseButtons = event->buttons();
    m_page->keyboardModifiers = event->modifiers();
    QWebView::mousePressEvent(event);
}
