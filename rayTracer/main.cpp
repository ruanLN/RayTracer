#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(a.arguments().size() == 1) {
        MainWindow w;
        w.show();

    return a.exec();
    } /*else if(a.arguments().size() == 3) {
        RayTracer tracer;
        tracer.setInFile(a.arguments().at(1));
        tracer.setOutFile(a.arguments().at(2));
    } else {
        return -1;
    }*/
}
