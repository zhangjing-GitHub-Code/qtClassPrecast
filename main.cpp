#include "qtClassPrecast.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtClassPrecast w;
    w.show();
    return a.exec();
}
