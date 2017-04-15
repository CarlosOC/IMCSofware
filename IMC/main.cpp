#include "imcsoftware.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IMCsoftware w;
    w.show();

    return a.exec();
}
