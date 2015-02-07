#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // create widgets
    urlEdit = new QLineEdit();
    loadProgress = new QProgressBar();
    tabWidget = new QTabWidget();
    addressLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    // connect signals and slots
    connect(urlEdit, SIGNAL(returnPressed()), this, SLOT(urlEdit_returnPressed()));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabWidget_currentChanged(int)));

    // layout window
    addressLayout->setMargin(2);
    addressLayout->setSpacing(2);
    addressLayout->addWidget(urlEdit);
    addressLayout->addWidget(loadProgress);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(addressLayout);
    mainLayout->addWidget(tabWidget);
    this->setLayout(mainLayout);

    // initializations
    loadProgress->setFixedWidth(100);
    loadProgress->setTextVisible(false);
    loadProgress->setMinimum(0);
    loadProgress->setMaximum(100);
    loadProgress->reset();
    tabWidget->setTabBarAutoHide(true);
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
    else if (event->modifiers() & Qt::ShiftModifier)
    {
        switch (event->key())
        {
            // search page backward
            case Qt::Key_F3:
                searchPage(false);
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
            // search page forward
            case Qt::Key_F3:
                searchPage(true);
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
        searchPage(true);
    else // open the URL entered
    {
        currWebView()->load(evaluateURL(urlEdit->text()));
    }
}

void MainWindow::tabWidget_currentChanged(int index)
{
    // set url in location bar and title in tab and window title, if needed
    if (!tabWidget->tabText(tabWidget->currentIndex()).startsWith("New Tab",Qt::CaseSensitive))
    {
        updateURLandTitle(currWebView(), true);
        loadProgress->setValue(100); // pretend that page is loaded
    } else
        loadProgress->reset(); // no page has been loaded on a new tab
}

void MainWindow::currWebView_loadProgress(int progress)
{
    QWebView* signalView = (QWebView*) QObject::sender();
    // set progress bar if current web view
    if (currWebView() == signalView)
    {
        loadProgress->setValue(progress);
    }
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

QUrl MainWindow::evaluateURL(QString url)
{
    QString fixedUrl;
    // add http prefix to the url if missing
    if (!url.startsWith("http"))
        fixedUrl = "http://" + url;
    else
        fixedUrl = url;
    // update urlEdit
    urlEdit->setText(fixedUrl);
    return QUrl(fixedUrl);
}

void MainWindow::addTab(QString url)
{
    // add tab with QWebView, select it, connect it and open url if given
    tabWidget->addTab(new QWebView(), "New Tab");
    tabWidget->setCurrentIndex(tabWidget->count() - 1);
    connect(currWebView(), SIGNAL(loadProgress(int)), this, SLOT(currWebView_loadProgress(int)));
    connect(currWebView(), SIGNAL(loadFinished(bool)), this, SLOT(currWebView_loadFinished(bool)));
    if (!url.isNull())
        currWebView()->load(evaluateURL(url));
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

void MainWindow::searchPage(bool forward)
{
    // check if "search mode" is active
    if (urlEdit->text().at(0) == QString("/"))
    {
        if (forward)
            currWebView()->findText(urlEdit->text().mid(1), QWebPage::FindWrapsAroundDocument);
        else
            currWebView()->findText(urlEdit->text().mid(1), QWebPage::FindWrapsAroundDocument|
                                                            QWebPage::FindBackward);
    }
}

MainWindow::~MainWindow()
{
    delete(urlEdit);
    delete(loadProgress);
    delete(tabWidget);
    delete(addressLayout);
    delete(mainLayout);
}
