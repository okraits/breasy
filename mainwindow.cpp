#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // create widgets
    urlEdit = new QLineEdit();
    tabWidget = new QTabWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    // connect signals and slots
    connect(urlEdit, SIGNAL(returnPressed()), this, SLOT(urlEdit_returnPressed()));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabWidget_currentChanged(int)));

    // layout window
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(urlEdit);
    layout->addWidget(tabWidget);
    this->setLayout(layout);

    // prepare window for startup
    this->setWindowTitle("breasy");
}

void MainWindow::processCliUrls(int argc, char *argv[])
{
    if (argc > 1) // if at least one url is given at the commandline
    {
        // add a tab for each url given at the commandline
        for (int i = 1; i < argc; i++)
        {
            QString url(argv[i]);
            addTab(url);
        }
    }
    else // add a blank tab
    {
        addTab(0);
        urlEdit->setFocus();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        switch (event->key())
        {
            // focus location bar
            case Qt::Key_L:
                urlEdit->selectAll();
                urlEdit->setFocus();
                break;
            // search in page
            case Qt::Key_F:
                urlEdit->setText("/");
                urlEdit->setCursorPosition(1);
                urlEdit->setFocus();
                break;
            // add tab
            case Qt::Key_T:
                addTab(0);
                urlEdit->setText("");
                urlEdit->setFocus();
                break;
            // focus next/previous tab
            case Qt::Key_PageDown:
                if (tabWidget->currentIndex() == (tabWidget->count() - 1))
                    tabWidget->setCurrentIndex(0);
                else
                    tabWidget->setCurrentIndex(tabWidget->currentIndex() + 1);
                break;
            case Qt::Key_PageUp:
                if (tabWidget->currentIndex() == 0)
                    tabWidget->setCurrentIndex(tabWidget->count() - 1);
                else
                    tabWidget->setCurrentIndex(tabWidget->currentIndex() - 1);
                break;
            // remove tab
            case Qt::Key_W:
                if (tabWidget->count() > 1)
                    currWebView()->deleteLater();
                else
                    this->close();
                break;
            // reload page
            case Qt::Key_R:
                currWebView()->reload();
                break;
            // zoom in/out
            case Qt::Key_Plus:
                currWebView()->setZoomFactor(currWebView()->zoomFactor() + 0.1);
                break;
            case Qt::Key_Minus:
                currWebView()->setZoomFactor(currWebView()->zoomFactor() - 0.1);
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }
    else if (event->modifiers() & Qt::AltModifier)
    {
        switch (event->key())
        {
            // go back/forward in the history
            case Qt::Key_Left:
                currWebView()->back();
                break;
            case Qt::Key_Right:
                currWebView()->forward();
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }
    else
    {
        switch (event->key())
        {
            // stop page loading
            case Qt::Key_Escape:
                currWebView()->stop();
                break;
            // reload page
            case Qt::Key_F5:
                currWebView()->reload();
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }
}

void MainWindow::urlEdit_returnPressed()
{
    // "/" at the beginning means searching the page for text
    if (urlEdit->text().at(0) == QString("/"))
        currWebView()->findText(urlEdit->text().mid(1), QWebPage::FindWrapsAroundDocument);
    else // open the URL entered
    {
        // add http prefix to the url if missing
        if (!urlEdit->text().startsWith("http"))
        {
            QString url = "http://" + urlEdit->text();
            currWebView()->load(QUrl(url));
        }
        else
            currWebView()->load(QUrl(urlEdit->text()));
    }
}

void MainWindow::tabWidget_currentChanged(int index)
{
    // set url in location bar and title in tab and window title, if needed
    if (!tabWidget->tabText(tabWidget->currentIndex()).startsWith("New Tab",Qt::CaseSensitive))
        updateURLandTitle(currWebView(), true);
}

void MainWindow::currWebView_loadFinished(bool ok)
{
    if (ok) // page loading was successful
    {
        QWebView* signalView = (QWebView*) QObject::sender();
        if (signalView != 0)
        {
            updateURLandTitle(signalView, signalView == currWebView());
            signalView->setFocus();
        }
    }
}

void MainWindow::addTab(QString url)
{
    // add tab with QWebView, select it, connect it and open url if given
    tabWidget->addTab(new QWebView(), "New Tab");
    tabWidget->setCurrentIndex(tabWidget->count() - 1);
    connect(currWebView(), SIGNAL(loadFinished(bool)), this, SLOT(currWebView_loadFinished(bool)));
    if (!url.isNull())
        currWebView()->load(QUrl(url));
}

QWebView* MainWindow::currWebView()
{
    return (QWebView*) tabWidget->currentWidget();
}

void MainWindow::updateURLandTitle(QWebView* webView, bool windowTitle)
{
    // set url in urlEdit
    urlEdit->setText(webView->url().toString());
    // set page title as tab text
    if (webView->title().length() > 50)
    {
        QString shortTitle = webView->title().left(50); // only show first 50 chars of page title
        shortTitle += "...";
        tabWidget->setTabText(tabWidget->indexOf(webView), shortTitle);
    }
    else
    {
        tabWidget->setTabText(tabWidget->indexOf(webView), webView->title());
    }
    // also set window title if this is the current tab
    if (windowTitle)
        this->setWindowTitle(webView->title() + " - breasy");
}

MainWindow::~MainWindow()
{
    delete(urlEdit);
    delete(tabWidget);
}
