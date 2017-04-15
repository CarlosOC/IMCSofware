#include "imcsoftware.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Splash Imagen
    QSplashScreen *splash = new QSplashScreen;  //Declaracion del vector donde se carga la imagen del Splash
    splash->setPixmap(QPixmap("C:/Users/Carlos OC/Documents/GitHub/IMCSofware/IMC/SplashScreen.png")); //Direccion de la imagen
    splash->show();                         // Mostramos la imagen ...
    QThread::msleep(1500);
    splash->close();

    IMCsoftware w;
    w.show();

    return a.exec();
}
