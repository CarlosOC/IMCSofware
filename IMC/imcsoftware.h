#ifndef IMCSOFTWARE_H
#define IMCSOFTWARE_H

#include <QMainWindow>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSerialPort/QSerialPort>
#include <QSplashScreen>
#include <QTimer>
#include "QThread"

namespace Ui {
class IMCsoftware;
}
QT_END_NAMESPACE

class Console;
class SettingsDialog;

class IMCsoftware : public QMainWindow
{
    Q_OBJECT

public:
    explicit IMCsoftware(QWidget *parent = 0);
    ~IMCsoftware();

private slots:

    void crearBasedeDatos();
    void VencenHoy();
    void Vencidos();
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void Ingreso (QString dato);
    void on_actionNuevo_Cliente_triggered();
    void on_actionBuscar_Cliente_triggered();
    void on_actionVer_Lista_de_Clientes_triggered();

private:
    void initActionsConnections();

private:
    Ui::IMCsoftware *ui;
    QSqlDatabase DataBase;
    enum Columna{ID, IDH, NOMBRE,APELLIDO,SEXO,DNI,EDAD,TEL ,FPAGO, FVENC};
    Console *console;
    SettingsDialog *settings;
    QSerialPort *serial;
};

#endif // IMCSOFTWARE_H
