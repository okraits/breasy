#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QWebView>
#include <QVBoxLayout>
#include <QKeyEvent>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openCliUrls(int argc, char *argv[]);

private slots:
    void urlEdit_returnPressed();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QWebView* webView;
    QLineEdit* urlEdit;
};

#endif // MAINWINDOW_H
