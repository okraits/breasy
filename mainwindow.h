#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QWebView>
#include <QVBoxLayout>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void urlEdit_returnPressed();

private:
    QWebView* webView;
    QLineEdit* urlEdit;
};

#endif // MAINWINDOW_H
