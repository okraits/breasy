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

    // set window properties
    this->setWindowTitle("breasy");
    tabWidget->addTab(new QWebView(), "New Tab");
}

void MainWindow::openCliUrls(int argc, char *argv[])
{
    //for (int i = 1; i < argc; i++) TODO: change when tabbed interface is implemented
    for (int i = 1; i < 2; i++)
    {
        QString url(argv[i]);
        currWebView()->load(QUrl(url));
        urlEdit->setText(url);
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
                tabWidget->addTab(new QWebView(), "New Tab");
                tabWidget->setCurrentIndex(tabWidget->count() - 1);
                urlEdit->selectAll();
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
    else
    {
        // add http prefix to the url if missing
        if (!urlEdit->text().startsWith("http"))
        {
            QString url = "http://" + urlEdit->text();
            currWebView()->load(QUrl(url));
            urlEdit->setText(url);
        }
        else
            currWebView()->load(QUrl(urlEdit->text()));
    }
}

void MainWindow::tabWidget_currentChanged(int index)
{
    // set url in location bar and title in tab, if needed
    urlEdit->setText(currWebView()->url().toString());
    if (!tabWidget->tabText(tabWidget->currentIndex()).startsWith("New Tab",Qt::CaseSensitive))
    {
        QString title = currWebView()->title().left(15); // only show first 15 chars of page title
        if (currWebView()->title().length() > 15)
            title += "...";
        tabWidget->setTabText(index, title);
    }
}

QWebView* MainWindow::currWebView()
{
    return (QWebView*) tabWidget->currentWidget();
}

MainWindow::~MainWindow()
{
    delete(urlEdit);
    delete(tabWidget);
}
