#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QTabWidget>
#include <QWebView>
#include <QVBoxLayout>
#include <QKeyEvent>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void processCliUrls(int argc, char *argv[]);

private slots:
    void urlEdit_returnPressed();
    void tabWidget_currentChanged(int index);
    void currWebView_loadFinished(bool ok);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QLineEdit* urlEdit;
    QTabWidget* tabWidget;
    void addTab(QString url);
    QWebView* currWebView();
    void updateURLandTitle(QWebView* webView, bool windowTitle);
};

#endif // MAINWINDOW_H
