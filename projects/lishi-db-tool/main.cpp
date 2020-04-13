#include "mainwindow.h"

#include <QApplication>

#include <ccxx/cxapplication_qt.h>

using namespace std;

int main(int argc, const char **argv)
{
    CxApplicationQt::init(argc, argv);

    QApplication app(argc, (char **)argv);
    MainWindow w;
    w.show();

    int result = CxApplicationQt::exec();

    return result;
}
