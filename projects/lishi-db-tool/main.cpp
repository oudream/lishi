#include "mainwindow.h"

#include <QApplication>

#include <ccxx/cxapplication_qt.h>

using namespace std;

int main(int argc, const char **argv)
{
//    string s;
//    s = CxFile::getLineString("/opt/limi/lishi/build/deploy/temp/a");
//    cout << CxString::toHexstring(s.c_str(), s.size()) << endl;
//    s = CxFile::getLineString("/opt/limi/lishi/build/deploy/temp/b");
//    cout << CxString::toHexstring(s.c_str(), s.size()) << endl;
//    s = CxFile::getLineString("/opt/limi/lishi/build/deploy/temp/c");
//    cout << CxString::toHexstring(s.c_str(), s.size()) << endl;
//    s = CxFile::getLineString("/opt/limi/lishi/build/deploy/temp/d");
//    cout << CxString::toHexstring(s.c_str(), s.size()) << endl;
//    s = CxFile::getLineString("/opt/limi/lishi/build/deploy/temp/e");
//    cout << CxString::toHexstring(s.c_str(), s.size()) << endl;

//    return 0;
    CxApplicationQt::init(argc, argv);

    QApplication app(argc, (char **)argv);
    MainWindow w;
    w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    w.showMaximized();

    int result = CxApplicationQt::exec();

    return result;
}

//#include <tuple>
//#include <utility>
//#include <iostream>
//
//template<std::size_t I = 0, typename... Tp>
//inline typename std::enable_if<I == sizeof...(Tp), void>::type
//print(std::tuple<Tp...>& t)
//{ }
//
//template<std::size_t I = 0, typename... Tp>
//inline typename std::enable_if<I < sizeof...(Tp), void>::type
//print(std::tuple<Tp...>& t)
//{
//    std::cout << std::get<I>(t) << std::endl;
//    print<I + 1, Tp...>(t);
//}
//
//int
//main()
//{
//    typedef std::tuple<int, float, double> T;
//    T t = std::make_tuple(2, 3.14159F, 2345.678);
//
//    print(t);
//}