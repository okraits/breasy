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
    void openCliUrls(int argc, char *argv[]);

private slots:
    void urlEdit_returnPressed();
    void tabWidget_currentChanged(int index);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QLineEdit* urlEdit;
    QTabWidget* tabWidget;
    QWebView* currWebView();
};

#endif // MAINWINDOW_H
