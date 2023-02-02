#include "startwindow.h"
#include "controller/controller.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    std::cout << "start creating startWindow" << std::endl;
    StartWindow w;
    TController contr(&w);
    contr.connect();

    w.show();
    return a.exec();
}



