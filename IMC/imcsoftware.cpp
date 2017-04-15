#include "imcsoftware.h"
#include "ui_imcsoftware.h"
#include "agregarcliente.h"
#include "dialoglistaclientes.h"
#include "dialogbuscarcliente.h"
#include "settingsdialog.h"
#include "console.h"
#include <QDebug>
#include <QMessageBox>

#include <QtSerialPort/QSerialPort>
QString idh;

IMCsoftware::IMCsoftware(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IMCsoftware)
{

    ui->setupUi(this);
    // Para el Puerto Serie: Principio

    console = new Console;
    console->setEnabled(false);
    //! [1]
    serial = new QSerialPort(this);
    //! [1]
    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(false);
    ui->actionDisconnect->setEnabled(true);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    openSerialPort();
    initActionsConnections();

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

//! [2]
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
//! [2]
    connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
    // Para el Puerto Serie: FIN



    //Enviamos mensaje en Consola
    qDebug()<<"Se Crea Base de Datos Personas SQlite...";

    // Nombre de la Base de Datos
    QString nombre;
    nombre.append("BaseDatos_Clientes.sqlite");

    //Instanciamos QSqlDatabase y le ponemos nombre a la base de datos
    DataBase = QSqlDatabase::addDatabase("QSQLITE");
    DataBase.setDatabaseName(nombre);

    //Abre la base de datos y muestra un aviso en caso de error
    if (DataBase.open()) qDebug()<<"Se ha conectado a la base de Datos";
     else
        {
        qDebug()<<"No se ha podio conectar a base de Datos";
        QMessageBox::critical(0, qApp->tr("Error Base de Datos"), qApp->tr("Ha sido imposible abrir la Base de Datos"),QMessageBox::Ok);
         }
    // Llamamos a la funcion para llenar la base de datos
    crearBasedeDatos();

    // Tabla de Vencidos en el Dia de la Fecha
    ui->tableWidget_VencenHoy->setColumnCount(6);
    ui->tableWidget_VencenHoy->setHorizontalHeaderItem(0,new QTableWidgetItem("Nombre"));
    ui->tableWidget_VencenHoy->setHorizontalHeaderItem(1,new QTableWidgetItem("Apellido"));
    ui->tableWidget_VencenHoy->setHorizontalHeaderItem(2,new QTableWidgetItem("DNI"));
    ui->tableWidget_VencenHoy->setHorizontalHeaderItem(3,new QTableWidgetItem("Tel"));
    ui->tableWidget_VencenHoy->setHorizontalHeaderItem(4,new QTableWidgetItem("Fecha de Pago"));
    ui->tableWidget_VencenHoy->setHorizontalHeaderItem(5,new QTableWidgetItem("Fecha de Venc"));
    VencenHoy();

    // Tabla de Vencidos antes del Dia de la Fecha
    ui->tableWidget_Vencidos->setColumnCount(6);
    ui->tableWidget_Vencidos->setHorizontalHeaderItem(0,new QTableWidgetItem("Nombre"));
    ui->tableWidget_Vencidos->setHorizontalHeaderItem(1,new QTableWidgetItem("Apellido"));
    ui->tableWidget_Vencidos->setHorizontalHeaderItem(2,new QTableWidgetItem("DNI"));
    ui->tableWidget_Vencidos->setHorizontalHeaderItem(3,new QTableWidgetItem("Tel"));
    ui->tableWidget_Vencidos->setHorizontalHeaderItem(4,new QTableWidgetItem("Fecha de Pago"));
    ui->tableWidget_Vencidos->setHorizontalHeaderItem(5,new QTableWidgetItem("Fecha de Venc"));
    Vencidos();


}

IMCsoftware::~IMCsoftware()
{
    delete ui;
}

void IMCsoftware::crearBasedeDatos()
{
    //Crea la tabla usuarios (Comando  para crear la tabla sqlite)
    QString consulta;
     //{ID,NOMBRE,APELLIDO,EDAD,DNI,TELEFONO,CUOTAS,DIASALASEMANA,CLASESDISPONIBLE};
    consulta.append("CREATE TABLE IF NOT EXISTS Clientes("
                   "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "IDH VARCHAR(10),"
                   "Nombre VARCHAR(100),"
                   "Apellido VARCHAR(100),"
                   "Sexo VARCHAR(10),"
                   "DNI VARCHAR(10),"
                   "Edad VARCHAR(4),"
                   "Tel VARCHAR(50),"
                   "Fpago VARCHAR(100),"
                   "Fvenc VARCHAR(100)"
                   ");");

    //"Nombre,Apellido,DNI,Telefono,Edad,Cuota"
    QSqlQuery crear;
    crear.prepare(consulta);
    if (crear.exec())qDebug()<<"Se creo correctamente la tabla";
        else {
              qDebug()<<"No se creo la tabla";
              qDebug()<<"Error: " << crear.lastError();
              }

}

void IMCsoftware::on_actionNuevo_Cliente_triggered()
{
    int respuesta;
    AgregarCliente NuevoCliente (this);
    respuesta =NuevoCliente.exec();
    if (respuesta == QDialog::Rejected) return;

    //Insertar registros en la tabla usuarios
    //query.prepare("INSERT INTO contacts (id, first_name, last_name) "" VALUES (:id, :first_name, :last_name)");

    QSqlQuery insertar;
    //"Nombre,Apellido,DNI,Telefono,Edad,Cuota"
    insertar.prepare("INSERT INTO Clientes(IDH, Nombre, Apellido, Sexo, DNI, Edad, Tel, Fpago, Fvenc) "" VALUES(:IDH, :Nombre, :Apellido, :Sexo, :DNI, :Edad, :Tel, :Fpago, :Fvenc)");

    insertar.bindValue(":IDH", NuevoCliente.IDHuella());
    qDebug()<<"ID Huella: "<< NuevoCliente.IDHuella();

    insertar.bindValue(":Nombre", NuevoCliente.Nombre());
    qDebug()<<"Nombre: "<< NuevoCliente.Nombre();

    insertar.bindValue(":Apellido", NuevoCliente.Apellido());
    qDebug()<<"Apellido: "<< NuevoCliente.Apellido();

    insertar.bindValue(":Sexo", NuevoCliente.Sexo());
    qDebug()<<"Sexo: "<< NuevoCliente.Sexo();

    insertar.bindValue(":DNI", NuevoCliente.DNI());
    qDebug()<<"DNI: "<< NuevoCliente.DNI();

    insertar.bindValue(":Edad", NuevoCliente.Edad());
    qDebug()<<"Edad: "<< NuevoCliente.Edad();

    insertar.bindValue(":Tel", NuevoCliente.Telefono());
    qDebug()<<"Tel: "<< NuevoCliente.Telefono();

    insertar.bindValue(":Fpago", NuevoCliente.FechaPago());
    qDebug()<<"Fpago: "<< NuevoCliente.FechaPago();

    insertar.bindValue(":Fvenc", NuevoCliente.FechaVencimiento());
    qDebug()<<"FVenc: "<< NuevoCliente.FechaVencimiento();


    if (insertar.exec())
    {
        qDebug()<<"Se inserto el registro en la tabla";
    }else {
        qDebug()<<"No se pudo insertar el registro";
        qDebug()<<"Error! " << insertar.lastError();
           }
}

void IMCsoftware::on_actionBuscar_Cliente_triggered()
{
    int respuesta;
    DialogBuscarCliente BuscadorCliente;
    respuesta = BuscadorCliente.exec();
    if (respuesta == QDialog::Rejected) return;
    if (BuscadorCliente.Nombre()!=NULL)                 //Para saber si se busco a Alguien o NO
    {
        QString SentenciaActualizar;
        // Cargamos el codigo para Actualizar la tabla
        SentenciaActualizar.append("UPDATE Clientes SET "
                  "Nombre    ='"+BuscadorCliente.Nombre()+"'"
                  ",Apellido ='"+BuscadorCliente.Apellido()+"'"
                  //",DNI      ='"+ui->lineEdit_Documento->text()+"'"
                  ",SEXO     ='"+BuscadorCliente.Sexo()+"'"
                  ",FPago    ='"+BuscadorCliente.FechaPago()+"'"
                  ",FVenc    ='"+BuscadorCliente.FechaVencimiento()+"'"
                  "WHERE id  ='"+BuscadorCliente.Id()+"'");



          QSqlQuery insertarActualizar;           // Creamos la variable del tipo clase QSql insertarActualizar
          insertarActualizar.prepare(SentenciaActualizar);    // Ejecutamos la clase insertarActualizar con el String cargado
          if (insertarActualizar.exec())
          {
              qDebug()<<"Se inserto el registro en la tabla";
          }else {
              qDebug()<<"No se pudo insertar el registro";
              qDebug()<<"Error! " << insertarActualizar.lastError();

          }
      }
}

void IMCsoftware::on_actionVer_Lista_de_Clientes_triggered()
{
    int respuesta;
    DialogListaClientes ListaClientes;
    respuesta = ListaClientes.exec();
    if (respuesta == QDialog::Rejected) return;

}


void IMCsoftware::VencenHoy()
{
    QDate Hoy;
    QDate FVencimiento;
    QString SHoy;
    QString Cliente;
    int fila=0;
    Hoy = QDate::currentDate();
    SHoy= Hoy.toString("dd/MM/yyyy");
    qDebug()<< SHoy;
    Hoy= QDate::fromString(SHoy,"dd/MM/yyyy");
    QString sentencia;
    sentencia.append("SELECT *FROM Clientes");

    QSqlQuery consultar;
    consultar.prepare(sentencia);
    if (consultar.exec())
    {
        qDebug()<<"Se cargaron los registros en la tabla";
    }else {
        qDebug()<<"No se pudo cargar los registros";
        qDebug()<<"Error! " << consultar.lastError();
    }
    while(consultar.next()) // enum Columna{ID, IDH, NOMBRE,APELLIDO,SEXO,DNI,EDAD,TEL ,FPAGO, FVENC};
    {
      Cliente= consultar.value(FVENC).toByteArray().constData();
      FVencimiento=QDate::fromString(Cliente,"dd/MM/yyyy");
      if(FVencimiento == Hoy )
      {
        ui->tableWidget_VencenHoy->insertRow(fila);
        ui->tableWidget_VencenHoy->setItem(fila,0,new QTableWidgetItem(consultar.value(NOMBRE).toByteArray().constData()));
        ui->tableWidget_VencenHoy->setItem(fila,1,new  QTableWidgetItem(consultar.value(APELLIDO).toByteArray().constData()));
        ui->tableWidget_VencenHoy->setItem(fila,2,new QTableWidgetItem(consultar.value(DNI).toByteArray().constData()));
        ui->tableWidget_VencenHoy->setItem(fila,3,new QTableWidgetItem(consultar.value(TEL).toByteArray().constData()));
        ui->tableWidget_VencenHoy->setItem(fila,4,new QTableWidgetItem(consultar.value(FPAGO).toByteArray().constData()));
        ui->tableWidget_VencenHoy->setItem(fila,5,new QTableWidgetItem(consultar.value(FVENC).toByteArray().constData()));
        fila++;
      }
    }

}

void IMCsoftware::Vencidos()
{
    QDate Hoy;
    QDate FVencimiento;
    QString SHoy;
    QString Cliente;
    int fila=0;
    Hoy = QDate::currentDate();
    SHoy= Hoy.toString("dd/MM/yyyy");
    qDebug()<< SHoy;
    Hoy= QDate::fromString(SHoy,"dd/MM/yyyy");
    QString sentencia;
    sentencia.append("SELECT *FROM Clientes");

    QSqlQuery consultar;
    consultar.prepare(sentencia);
    if (consultar.exec())
    {
        qDebug()<<"Se cargaron los registros en la tabla";
    }else {
        qDebug()<<"No se pudo cargar los registros";
        qDebug()<<"Error! " << consultar.lastError();
    }
    while(consultar.next()) // enum Columna{ID, IDH, NOMBRE,APELLIDO,SEXO,DNI,EDAD,TEL ,FPAGO, FVENC};
    {
      Cliente= consultar.value(FVENC).toByteArray().constData();
      FVencimiento=QDate::fromString(Cliente,"dd/MM/yyyy");
      if(FVencimiento < Hoy )
      {
        qDebug()<< "Vencieron";
        ui->tableWidget_Vencidos->insertRow(fila);
        ui->tableWidget_Vencidos->setItem(fila,0,new QTableWidgetItem(consultar.value(NOMBRE).toByteArray().constData()));
        ui->tableWidget_Vencidos->setItem(fila,1,new QTableWidgetItem(consultar.value(APELLIDO).toByteArray().constData()));
        ui->tableWidget_Vencidos->setItem(fila,2,new QTableWidgetItem(consultar.value(DNI).toByteArray().constData()));
        ui->tableWidget_Vencidos->setItem(fila,3,new QTableWidgetItem(consultar.value(TEL).toByteArray().constData()));
        ui->tableWidget_Vencidos->setItem(fila,4,new QTableWidgetItem(consultar.value(FPAGO).toByteArray().constData()));
        ui->tableWidget_Vencidos->setItem(fila,5,new QTableWidgetItem(consultar.value(FVENC).toByteArray().constData()));
        fila++;
      }
    }
}

// Funciones para el Serial Port
void IMCsoftware::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    if (serial->open(QIODevice::ReadWrite)) {
        if (serial->setBaudRate(p.baudRate)
                && serial->setDataBits(p.dataBits)
                && serial->setParity(p.parity)
                && serial->setStopBits(p.stopBits)
                && serial->setFlowControl(p.flowControl)) {

            console->setEnabled(true);
            console->setLocalEchoEnabled(p.localEchoEnabled);
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

        } else {
            serial->close();
            QMessageBox::critical(this, tr("Error"), serial->errorString());

            ui->statusBar->showMessage(tr("Open error"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Configure error"));
    }
}
//! [4]

//! [5]
void IMCsoftware::closeSerialPort()
{
    serial->close();
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}
//! [5]

void IMCsoftware::about()
{
    console->show();
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

//! [6]
void IMCsoftware::writeData(const QByteArray &data)
{
    serial->write(data);
}
//! [6]

//! [7]
void IMCsoftware::readData()
{
    QByteArray data = serial->readAll();
    //ui->textBrowser->insertPlainText(data);
    console->putData(data);
    //QString bandera(data);
    Ingreso(data);
}
//! [7]

//! [8]
void IMCsoftware::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void IMCsoftware::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void IMCsoftware::Ingreso (QString dato)
{
  int i;
  idh.append(dato);
  i=idh.toInt();
  if (i>1000) idh.clear();
  qDebug()<<i;
  qDebug()<<idh;
}

