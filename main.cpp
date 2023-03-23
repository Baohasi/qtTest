#include "comwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    comWidget w;
    w.show();

    return a.exec();
}
