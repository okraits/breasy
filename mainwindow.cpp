#include "mainwindow.h"

// public #############################

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // create objects
    settings = new Settings();
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
    settings->readSettings();
    loadProgress->setFixedWidth(100);
    loadProgress->setTextVisible(false);
    loadProgress->setMinimum(0);
    loadProgress->setMaximum(100);
    loadProgress->reset();
    tabWidget->setTabBarAutoHide(true);
    this->setWindowTitle("breasy");
}

MainWindow::~MainWindow()
{
    delete(settings);
    delete(urlEdit);
    delete(loadProgress);
    delete(tabWidget);
    delete(addressLayout);
    delete(mainLayout);
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
        addTab(settings->getValue(SK_STARTPAGE).toString());
        urlEdit->setFocus();
    }
}

void MainWindow::addTab(QString url)
{
    // add tab with WebView, select it, connect it and open url if given
    tabWidget->addTab(new WebView(), "New Tab");
    tabWidget->setCurrentIndex(tabWidget->count() - 1);
    configureWebView();
    connect(currentWebView(), SIGNAL(loadProgress(int)), this, SLOT(currWebView_loadProgress(int)));
    connect(currentWebView(), SIGNAL(loadFinished(bool)), this, SLOT(currWebView_loadFinished(bool)));
    if (!url.isNull())
        currentWebView()->load(processUrl(url));
}

// protected #############################

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
                    currentWebView()->deleteLater();
                else
                    this->close();
                break;
            // reload page
            case Qt::Key_R:
                currentWebView()->reload();
                break;
            // zoom in/out
            case Qt::Key_Plus:
                currentWebView()->setZoomFactor(currentWebView()->zoomFactor() + 0.1);
                break;
            case Qt::Key_Minus:
                currentWebView()->setZoomFactor(currentWebView()->zoomFactor() - 0.1);
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
                currentWebView()->back();
                break;
            case Qt::Key_Right:
                currentWebView()->forward();
                break;
            // load startpage
            case Qt::Key_Home:
                currentWebView()->load(processUrl(settings->getValue(SK_STARTPAGE).toString()));
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
                searchText(false);
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
                currentWebView()->stop();
                break;
            // search page forward
            case Qt::Key_F3:
                searchText(true);
                break;
            // reload page
            case Qt::Key_F5:
                currentWebView()->reload();
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    settings->writeSettings();
    event->accept();
}

// private slots #############################

void MainWindow::urlEdit_returnPressed()
{
    // "/" at the beginning means searching the page for text
    if (urlEdit->text().at(0) == QString("/"))
        searchText(true);
    else
    {
        // check if a keyword search was initiated
        QString searchstring = settings->getSearchString(urlEdit->text());
        if (searchstring != "")
            currentWebView()->load(processUrl(searchstring));
        else // simply open the URL entered
            currentWebView()->load(processUrl(urlEdit->text()));
    }
}

void MainWindow::tabWidget_currentChanged(int index)
{
    // set url in location bar and title in tab and window title, if needed
    if (!tabWidget->tabText(tabWidget->currentIndex()).startsWith("New Tab",Qt::CaseSensitive))
    {
        setPageInfos(currentWebView(), true);
        loadProgress->setValue(100); // pretend that page is loaded
    } else
        loadProgress->reset(); // no page has been loaded on a new tab
}

void MainWindow::currWebView_loadProgress(int progress)
{
    WebView* signalView = (WebView*) QObject::sender();
    // set progress bar if current web view
    if (currentWebView() == signalView)
    {
        loadProgress->setValue(progress);
    }
}

void MainWindow::currWebView_loadFinished(bool ok)
{
    if (ok) // page loading was successful
    {
        WebView* signalView = (WebView*) QObject::sender();
        if (signalView != 0)
        {
            setPageInfos(signalView, signalView == currentWebView());
            signalView->setFocus();
        }
    }
}

// private #############################

QUrl MainWindow::processUrl(QString url)
{
    QUrl validatedUrl = QUrl::fromUserInput(url);
    // update urlEdit
    urlEdit->setText(validatedUrl.toString());
    return validatedUrl;
}

void MainWindow::configureWebView() // TODO: member method of WebView
{
    QWebSettings* settings = currentWebView()->settings()->globalSettings();
    settings->setAttribute(QWebSettings::PluginsEnabled, true);
}

WebView* MainWindow::currentWebView()
{
    return (WebView*) tabWidget->currentWidget();
}

void MainWindow::setPageInfos(WebView* webView, bool windowTitle)
{
    // set url in urlEdit
    urlEdit->setText(webView->url().toString());
    // set page title as tab text
    if (webView->title().length() > 30)
    {
        QString shortTitle = webView->title().left(30); // only show first 30 chars of page title
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

void MainWindow::searchText(bool forward)
{
    // check if "search mode" is active
    if (urlEdit->text().at(0) == QString("/"))
    {
        if (forward)
            currentWebView()->findText(urlEdit->text().mid(1), QWebPage::FindWrapsAroundDocument);
        else
            currentWebView()->findText(urlEdit->text().mid(1), QWebPage::FindWrapsAroundDocument|
                                                            QWebPage::FindBackward);
    }
}
