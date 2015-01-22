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

    // do actions on startup
    this->setWindowTitle("breasy");
    webView->load(QUrl("http://google.de/"));
    webView->show();
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
