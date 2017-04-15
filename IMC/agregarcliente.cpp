#include "agregarcliente.h"
#include "ui_agregarcliente.h"
#include <QFile>
#include <QTextStream>

int numerodeclases;
AgregarCliente::AgregarCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarCliente)
{
  ui->setupUi(this);
  connect(ui->radioButton_DeporteNo,SIGNAL(clicked(bool)),ui->lineEdit_DeporteCual,SLOT(setDisibled(bool)));
  connect(ui->radioButton_DeporteSi,SIGNAL(clicked(bool)),ui->lineEdit_DeporteCual,SLOT(setEnabled(bool)));
  //Validacion de los LineEdit
  ui->lineEdit_Dni->setInputMask("99.999.999");

}

AgregarCliente::~AgregarCliente()
{
  delete ui;
}
QString AgregarCliente::Nombre() const
{
 return ui->lineEdit_Nombre->text();
}
QString AgregarCliente::Apellido() const
{
   return ui->lineEdit_Apellido->text();
}
QString AgregarCliente::DNI() const
{
    return ui->lineEdit_Dni->text();
}
QString AgregarCliente::Telefono() const
{
    return ui->lineEdit_Telefono->text();
}
QString AgregarCliente::Edad() const
{
   return QString::number(ui->spinBox_Edad->value());
}
QString AgregarCliente::FechaPago() const
{
  return ui->dateEdit_FechaPago->text();
}
QString AgregarCliente::FechaVencimiento() const
{
 return ui->dateEdit_FechaVencimiento->text();
}
QString AgregarCliente::IDHuella() const
{
 return ui->lineEdit_ID->text();
}

QString AgregarCliente::Sexo() const
{
  if(ui->radioButton_SexoF->isChecked())return "Femenino";
  else if(ui->radioButton_SexoM->isChecked())return "Masculino";
  else return "none";
}

void AgregarCliente::on_pushButton_Aceptar_clicked()
{
  CrearArchivoFicha();
  accept();
}
void AgregarCliente::on_pushButton_Cancelar_clicked()
{
 //cerrar ventana
 reject();
}
void AgregarCliente::on_pushButton_clicked()
{
    // Enviar comandos RS232
}
void AgregarCliente::CrearArchivoFicha()
{
    QString nombreArchivo = IDHuella();
    QString TipoArchivo = ".txt";

    nombreArchivo.append(TipoArchivo);

    //Crear Archivo
    QFile archivo(nombreArchivo);

          archivo.open(QIODevice::Text | QIODevice::WriteOnly);
          if(!archivo.isOpen())
              {
              return ;
              }
    //Escribe el Archivo
   QTextStream txtstr (&archivo);
   txtstr << ui->lineEdit_Nombre->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_Apellido->text();
   //Imformacion Filiatoria

   txtstr << "\n";
   txtstr << ui->lineEdit_ObraSocial->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_Barrio->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_Calle->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_NumeroCasa->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_Piso->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_EstadoCivil->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_CasodeEmergenciaAvisar->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_TelefonodeEmergencia->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_email->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_Ocupacion->text();
   txtstr << "\n";
   if (ui->radioButton_CHTmenos20->isChecked())txtstr       <<"menos20";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_CHTentre2040->isChecked())txtstr     <<"entre2040";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_CHTentre4161->isChecked())txtstr     <<"entre416";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_CHTmas60->isChecked())txtstr         <<"mas60";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_MPTPSentado->isChecked())txtstr      <<"Sentado";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_MPTPDePie->isChecked())txtstr        <<"DePie";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_MPTPLenvand->isChecked())txtstr      <<"Lenvand";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_MPTPCaminando->isChecked())txtstr    <<"Caminando";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_MPTPManejando->isChecked())txtstr    <<"Manejando";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_numerodesocio->text();
   txtstr << "\n";
   txtstr << ui->dateEdit_fechadeinscripcion->text();
   txtstr << "\n";
   if (ui->radioButton_DClunes->isChecked())txtstr      <<"Lunes";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_DCMartes->isChecked())txtstr     <<"Martes";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_DCMiercoles->isChecked())txtstr  <<"Miercoles";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_DCJueves->isChecked())txtstr     <<"Jueves";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_DCViernes->isChecked())txtstr    <<"Viernes";
   else txtstr << " ";
   txtstr << "\n";
   if (ui->radioButton_DCSabado->isChecked())txtstr     <<"Sabado";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->timeEdit_horariodeclase_desde->text();
   txtstr << "\n";
   txtstr << ui->timeEdit_horariodeclase_hasta->text();
   txtstr << "\n";

   //Informacion Medica/Nutricional
   txtstr << ui->lineEdit_PesoKG->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_Talla->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_PesoDeseado->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_UvisitaMedico->text();
   txtstr << "\n";
   if(ui->radioButton_FSACorazonPadre->isChecked())     txtstr <<"Padre";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_FSACorazonMadre->isChecked())     txtstr <<"Madre";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_FSACorazonHermano->isChecked())   txtstr <<"Hermano";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_FSACorazonHermana->isChecked())   txtstr <<"Hermana";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_FSACorazonAbuelo->isChecked())    txtstr <<"Abuelo";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_FSACorazonAbuela->isChecked())    txtstr <<"Abuela";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_OperacionGraveSi->isChecked())    txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_OperacionGraveNo->isChecked())    txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_OperacionGraveCual->text();
   txtstr << "\n";
   if(ui->radioButton_DoloresEspalda->isChecked())  txtstr <<"Espalda";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DoloresRodilla->isChecked())  txtstr <<"Rodilla";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DoloresCuello->isChecked())   txtstr <<"Cuello";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DoloresTobillo->isChecked())  txtstr <<"Tobillo";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DoloresCodo->isChecked())     txtstr <<"Codo";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DoloresCadera->isChecked())   txtstr <<"Cadera";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_MedicamentoSi->isChecked())   txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_MedicamentoNo->isChecked())   txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_Medicamento->text();
   txtstr << "\n";
   if(ui->radioButton_VitaminaSuplementoSi->isChecked())   txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_VitaminaSuplementoNo->isChecked())   txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_SuplementoNutricional->text();
   txtstr << "\n";
   if(ui->radioButton_DietaSi->isChecked())   txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DietaNo->isChecked())   txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_Dieta->text();
   txtstr << "\n";
   txtstr << QString::number(ui->spinBox_ComidaporDia->value());
   txtstr << "\n";
   if(ui->radioButton_DesayunaSi->isChecked())   txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DesayunaNo->isChecked())   txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_VaricesSi->isChecked())    txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_VaricesNo->isChecked())    txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_CelulitisSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_CelulitisNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";

   //Estilo de Vida y Salud
   if(ui->radioButton_FumaSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_FumaNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_Cigarrillo1a9->isChecked())   txtstr <<"Cigarrillo1a9";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_Cigarrillo10a19->isChecked()) txtstr <<"Cigarrillo10a19";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_Cigarrillomas20->isChecked()) txtstr <<"Cigarrillomas20";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DeporteSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_DeporteNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_DeporteCual->text();
   txtstr << "\n";
   if(ui->radioButton_GimnasioSi->isChecked())      txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_GimnasioNo->isChecked())      txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_GimnasioBuena->isChecked())   txtstr <<"Buena";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_GimnasioRegular->isChecked()) txtstr <<"Regular";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_GimnasioMala->isChecked())    txtstr <<"Mala";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_GimnasioPorque->text();
   txtstr << "\n";
   if(ui->radioButton_EjerciciosRegularesSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_EjerciciosRegularesNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_EjerciciosRegularesCual->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_NoRealizaActidadFisica->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_SiRealizaActividadFisica->text();
   txtstr << "\n";

   //Objetivos Generales
   if(ui->radioButton_AumentaMasaMuscularSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_AumentaMasaMuscularNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_TonificarSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_TonificarNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_BajarPesoSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_BajarPesoNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_SentireseMejorSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_SentireseMejorNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_PrescripcionMedicaSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_PrescripcionMedicaNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_OtroMotivoSi->isChecked()) txtstr <<"Si";
   else txtstr << " ";
   txtstr << "\n";
   if(ui->radioButton_OtroMotivoNo->isChecked()) txtstr <<"No";
   else txtstr << " ";
   txtstr << "\n";
   txtstr << ui->lineEdit_OtroMotivoCual->text();
   txtstr << "\n";
   //ParQ
   txtstr << ui->lineEdit_ParQ01->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_ParQ02->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_ParQ03->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_ParQ04->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_ParQ05->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_ParQ06->text();
   txtstr << "\n";
   txtstr << ui->lineEdit_ParQ07->text();
   txtstr << "\n";
   // FIN del Archivo

   archivo.flush();
   archivo.close();

}

void AgregarCliente::EscribirArchivoFicha()
{

}
