#include "dialogbuscarcliente.h"
#include "ui_dialogbuscarcliente.h"
#include "dialogficha.h"


QString id;
DialogBuscarCliente::DialogBuscarCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBuscarCliente)
{
    ui->setupUi(this);
    //Validacion de los LineEdit
    ui->lineEdit_Dni->setInputMask("99.999.999");
}

DialogBuscarCliente::~DialogBuscarCliente()
{
    delete ui;
}

void DialogBuscarCliente::on_pushButton_Buscar_clicked()
{
  QDate FPago;
  QDate FVenc;
  QString SFPago;
  QString SFVenc;
  QString Sentencia;
  QString Sexo;
  Sentencia.append ("SELECT *FROM Clientes WHERE DNI = '"+ui->lineEdit_Dni->text()+"'"); //Para Cargar el Dato de la base de datos con el id que se escribio
    QSqlQuery  consultar;           // Variable de la clase QSql base de datos
    consultar.prepare(Sentencia);

    if (consultar.exec())           // Ejecutamos la instruccion de la base de datos
    {
     qDebug()<<"Se creo abrio la Tabla";

     consultar.first();         // Nos ubicamos en el primero que encuentren (al buscar por id es uno solo, si buscaramos por otro podemos usar first, next, last)
     id=consultar.value(ID).toByteArray().constData();
     // Pasamos los datos desde la variable consultar a los lugares correspondinete en la pantalla (wigdets)
     ui->lineEdit_Nombre->setText( consultar.value(NOMBRE).toByteArray().constData());
     qDebug()<<"Nombre:" << consultar.value(NOMBRE).toByteArray().constData();
     ui->lineEdit_Apellido->setText( consultar.value(APELLIDO).toByteArray().constData());
     qDebug()<<"Apellido:" <<  consultar.value(APELLIDO).toByteArray().constData();
     //ui->lineEdit_Sexo->setText(consultar.value(SEXO).toByteArray().constData());
     Sexo = consultar.value(SEXO).toByteArray().constData();
     if(Sexo == "Femenino") ui->radioButton_SexoF->setChecked(1);
         else if (Sexo == "Masculino") ui->radioButton_SexoM->setChecked(1);
           else if (Sexo == "none")
     qDebug()<<"Sexo:" <<  consultar.value(SEXO).toByteArray().constData();
     ui->lineEdit_ID->setText(consultar.value(IDH).toByteArray().constData());
     qDebug()<<"IDH:" <<  consultar.value(IDH).toByteArray().constData();
     SFPago=consultar.value(FPAGO).toByteArray().constData();
     SFVenc=consultar.value(FVENC).toByteArray().constData();
     FPago= QDate::fromString(SFPago,"dd/MM/yyyy");
     FVenc=QDate::fromString(SFVenc,"dd/MM/yyyy");
     ui->dateEdit_FechaPago->setDate(FPago);
     qDebug()<<"Fpago:" <<  FPago;
     ui->dateEdit_FechaVencimiento->setDate(FVenc);
     qDebug()<<"Fpago:" <<  FVenc;
    }
    else qDebug()<<"Error!!! No se efectua la consulta"  << consultar.lastError();;

}


void DialogBuscarCliente::on_pushButton_VerFicha_clicked()
{
    int respuesta;
    DialogFicha FichaCliente;
    FichaCliente.Nombre_Archivo(ui->lineEdit_ID->text()); // Envia el Nombre de la Ficha a Buscar
    respuesta = FichaCliente.exec();
    if (respuesta == QDialog::Rejected) return;
}

void DialogBuscarCliente::on_pushButton_Cancelar_clicked()
{
 reject();
}

void DialogBuscarCliente::on_pushButton_Aceptar_clicked()
{
  accept();

}

QString DialogBuscarCliente::Nombre() const
{
 return ui->lineEdit_Nombre->text();
}
QString DialogBuscarCliente::Apellido() const
{
   return ui->lineEdit_Apellido->text();
}
QString DialogBuscarCliente::FechaPago() const
{
  return ui->dateEdit_FechaPago->text();
}
QString DialogBuscarCliente::FechaVencimiento() const
{
 return ui->dateEdit_FechaVencimiento->text();
}
QString DialogBuscarCliente::Id() const
{
 return id;
}
QString DialogBuscarCliente::Sexo() const
{
    if(ui->radioButton_SexoF->isChecked())return "Femenino";
    else if(ui->radioButton_SexoM->isChecked())return "Masculino";
    else return "none";
}

QString DialogBuscarCliente::Dni() const
{
  return ui->lineEdit_Dni->text();
}

void DialogBuscarCliente::on_pushButton_ModificarDatos_clicked()
{
    ui->lineEdit_Nombre->setEnabled(1);
    ui->lineEdit_Apellido->setEnabled(1);
    ui->radioButton_SexoF->setEnabled(1);
    ui->radioButton_SexoM->setEnabled(1);
    ui->dateEdit_FechaPago->setEnabled(1);
    ui->dateEdit_FechaVencimiento->setEnabled(1);
}
