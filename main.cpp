#include "qtClassPrecast.h"
#include "precastingWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // qtClassPrecast w;
    precastingWidget w;
    w.show();
    return a.exec();
}
