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

void MainWindow::urlEdit_returnPressed()
{
    webView->load(QUrl(urlEdit->text()));
}

MainWindow::~MainWindow()
{
    delete(urlEdit);
    delete(webView);
}
