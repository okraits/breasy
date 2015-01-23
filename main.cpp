#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if (argc > 1)
        w.openCliUrls(argc, argv);
    w.show();

    return a.exec();
}
