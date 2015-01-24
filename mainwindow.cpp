#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // create widgets
    urlEdit = new QLineEdit();
    webView = new QWebView();
    QVBoxLayout *layout = new QVBoxLayout();

    // connect signals and slots
    connect(urlEdit, SIGNAL(returnPressed()), this, SLOT(urlEdit_returnPressed()));

    // layout window
    layout->addWidget(urlEdit);
    layout->addWidget(webView);
    this->setLayout(layout);

    // set window properties
    this->setWindowTitle("breasy");
}

void MainWindow::openCliUrls(int argc, char *argv[])
{
    //for (int i = 1; i < argc; i++) TODO: change when tabbed interface is implemented
    for (int i = 1; i < 2; i++)
    {
        QString url(argv[i]);
        webView->load(QUrl(url));
        urlEdit->setText(url);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        switch (event->key())
        {
            case Qt::Key_L:
                urlEdit->selectAll();
                urlEdit->setFocus();
                break;
            case Qt::Key_W:
                this->close();
                break;
            case Qt::Key_R:
                webView->reload();
                break;
            case Qt::Key_F:
                urlEdit->setText("/");
                urlEdit->setCursorPosition(1);
                urlEdit->setFocus();
                break;
            case Qt::Key_Plus:
                webView->setZoomFactor(webView->zoomFactor() + 0.1);
                break;
            case Qt::Key_Minus:
                webView->setZoomFactor(webView->zoomFactor() - 0.1);
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    } else
    {
        switch (event->key())
        {
            case Qt::Key_Escape:
                webView->stop();
                break;
            case Qt::Key_F5:
                webView->reload();
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
        webView->findText(urlEdit->text().mid(1), QWebPage::FindWrapsAroundDocument);
    else
    {
        // add http prefix to the url if missing
        if (!urlEdit->text().startsWith("http"))
        {
            QString url = "http://" + urlEdit->text();
            webView->load(QUrl(url));
            urlEdit->setText(url);
        }
        else
            webView->load(QUrl(urlEdit->text()));
    }
}

MainWindow::~MainWindow()
{
    delete(urlEdit);
    delete(webView);
}
