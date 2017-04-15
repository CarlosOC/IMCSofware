#include "dialoglistaclientes.h"
#include "ui_dialoglistaclientes.h"

DialogListaClientes::DialogListaClientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogListaClientes)
{
    ui->setupUi(this);
    ////ID, IDH, NOMBRE,APELLIDO,SEXO,DNI,EDAD,TEL ,FPAGO, FVE
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("IDH"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Nombre"));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Apellido"));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Sexo"));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("DNI"));
    ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem("Edad"));
    ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem("Tel"));
    ui->tableWidget->setHorizontalHeaderItem(8,new QTableWidgetItem("Fecha de Pago"));
    ui->tableWidget->setHorizontalHeaderItem(9,new QTableWidgetItem("Fecha de Venc"));

    CargarTabla();
}

DialogListaClientes::~DialogListaClientes()
{
    delete ui;
}

void DialogListaClientes::CargarTabla()
{
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

    // Inserto en la tabla
    int fila=0;
    ui->tableWidget->setRowCount(0);
    while(consultar.next())
    {
        // Agregamos una fila

        ui->tableWidget->insertRow(fila);
        // ..->setItem(fila,columna,widgetItem) //ID, IDH, NOMBRE,APELLIDO,SEXO,DNI,EDAD,TEL ,FPAGO, FVENC
        ui->tableWidget->setItem(fila,ID,new QTableWidgetItem(consultar.value(ID).toByteArray().constData()));
        ui->tableWidget->setItem(fila,IDH,new QTableWidgetItem(consultar.value(IDH).toByteArray().constData()));
        ui->tableWidget->setItem(fila,NOMBRE,new QTableWidgetItem(consultar.value(NOMBRE).toByteArray().constData()));
        ui->tableWidget->setItem(fila,APELLIDO,new  QTableWidgetItem(consultar.value(APELLIDO).toByteArray().constData()));
        ui->tableWidget->setItem(fila,SEXO,new QTableWidgetItem(consultar.value(SEXO).toByteArray().constData()));
        ui->tableWidget->setItem(fila,DNI,new QTableWidgetItem(consultar.value(DNI).toByteArray().constData()));
        ui->tableWidget->setItem(fila,EDAD,new QTableWidgetItem(consultar.value(EDAD).toByteArray().constData()));
        ui->tableWidget->setItem(fila,TEL,new QTableWidgetItem(consultar.value(TEL).toByteArray().constData()));
        ui->tableWidget->setItem(fila,FPAGO,new QTableWidgetItem(consultar.value(FPAGO).toByteArray().constData()));
        ui->tableWidget->setItem(fila,FVENC,new QTableWidgetItem(consultar.value(FVENC).toByteArray().constData()));
        fila++;
    }
}

