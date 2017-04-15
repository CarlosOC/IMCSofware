#include "dialogficha.h"
#include "ui_dialogficha.h"
int cntlinea;
QString nombreArchivo;

DialogFicha::DialogFicha(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFicha)
{
    ui->setupUi(this);

}

DialogFicha::~DialogFicha()
{
    delete ui;
}
void DialogFicha::Nombre_Archivo (QString NombreArchivo)
{
  QString TipoArchivo = ".txt";
  NombreArchivo.append(TipoArchivo);
  nombreArchivo = NombreArchivo;
  abrir_archivo(nombreArchivo);
  qDebug() << nombreArchivo;
}

void DialogFicha::abrir_archivo (QString &nombre_archivo)
  {
     QFile archivo(nombre_archivo) ;
     archivo.open(QIODevice::Text | QIODevice::ReadOnly);
     if(!archivo.isOpen())
         {
         qDebug() << "Error Archivo";
         return ;
         }

     QTextStream txtstr(&archivo);
     qDebug() << "Abro Archivo" ;
     cntlinea=0;
     while(!txtstr.atEnd())
      {
        QString linea=txtstr.readLine();
        //qDebug() << "Leo Linea" ;
        procesar_linea(linea,cntlinea);
        cntlinea++;
      }
     archivo.flush();
     archivo.close();

}

void DialogFicha::procesar_linea(const QString &line,int cntlinea)
{
  // bool ok;
    QDate FechadeInscripcion;
    QTime HorariodeClaseDesde;
    QTime HorariodeClaseHasta;
    int numero;

    if (cntlinea==0) ui->lineEdit_Nombre->setText(line);
    if (cntlinea==1) ui->lineEdit_Apellido->setText(line);
    //Imformacion Filiatoria
    if (cntlinea==2) ui->lineEdit_ObraSocial->setText(line);
    if (cntlinea==3) ui->lineEdit_Barrio->setText(line);
    if (cntlinea==4) ui->lineEdit_Calle->setText(line);
    if (cntlinea==5) ui->lineEdit_NumeroCasa->setText(line);
    if (cntlinea==6) ui->lineEdit_Piso->setText(line);
    if (cntlinea==7) ui->lineEdit_EstadoCivil->setText(line);
    if (cntlinea==8) ui->lineEdit_CasodeEmergenciaAvisar->setText(line);
    if (cntlinea==9) ui->lineEdit_TelefonodeEmergencia->setText(line);
    if (cntlinea==10) ui->lineEdit_email->setText(line);
    if (cntlinea==11) ui->lineEdit_Ocupacion->setText(line);
    if (cntlinea==12 && line=="menos20")    ui->radioButton_CHTmenos20->setChecked(1);
    if (cntlinea==13 && line=="entre2040")  ui->radioButton_CHTentre2040->setChecked(1);
    if (cntlinea==14 && line=="menos20")    ui->radioButton_CHTentre4161->setChecked(1);
    if (cntlinea==15 && line=="entre416")   ui->radioButton_CHTmas60->setChecked(1);
    if (cntlinea==16 && line=="Sentado")    ui->radioButton_MPTPSentado->setChecked(1);
    if (cntlinea==17 && line=="DePie")      ui->radioButton_MPTPDePie->setChecked(1);
    if (cntlinea==18 && line=="Lenvand")    ui->radioButton_MPTPLenvand->setChecked(1);
    if (cntlinea==19 && line=="Caminando")  ui->radioButton_MPTPCaminando->setChecked(1);
    if (cntlinea==20 && line=="Manejando")  ui->radioButton_MPTPManejando->setChecked(1);
    if (cntlinea==21) ui->lineEdit_numerodesocio->setText(line);
    if (cntlinea==22)
    {
     FechadeInscripcion = QDate::fromString(line,"dd/MM/yyyy");
     ui->dateEdit_fechadeinscripcion->setDate(FechadeInscripcion);
    }
    if (cntlinea==23 && line=="Lunes")      ui->radioButton_DClunes->setChecked(1);
    if (cntlinea==24 && line=="Martes")     ui->radioButton_DCMartes->setChecked(1);
    if (cntlinea==25 && line=="Miercoles")  ui->radioButton_DCMiercoles->setChecked(1);
    if (cntlinea==26 && line=="Jueves")     ui->radioButton_DCJueves->setChecked(1);
    if (cntlinea==27 && line=="Viernes")    ui->radioButton_DCViernes->setChecked(1);
    if (cntlinea==28 && line=="Sabado")     ui->radioButton_DCSabado->setChecked(1);
    if (cntlinea==29)
        {
        //HorariodeClaseDesde.fromString(line,"hh:mm AP");//
        HorariodeClaseDesde = QTime::fromString(line,"hh:mm AP");
        qDebug() << line;
        qDebug() << HorariodeClaseDesde.toString() ;
        ui->timeEdit_horariodeclase_desde->setTime(HorariodeClaseDesde);
        }
    if (cntlinea==30)
        {

        HorariodeClaseHasta = QTime::fromString(line,"h:m AP");//QTime::fromString();
        qDebug() << line;
        qDebug() << HorariodeClaseHasta ;
        ui->timeEdit_horariodeclase_hasta->setTime(HorariodeClaseHasta);
        }

    //Informacion Medica/Nutricional
    if (cntlinea==31)   ui->lineEdit_PesoKG->setText(line);
    if (cntlinea==32)   ui->lineEdit_Talla->setText(line);
    if (cntlinea==33)   ui->lineEdit_PesoDeseado->setText(line);
    if (cntlinea==34)   ui->lineEdit_UvisitaMedico->setText(line);
    if (cntlinea==35 && line=="Padre")  ui->radioButton_FSACorazonPadre->setChecked(1);
    if (cntlinea==36 && line== "Madre")ui->radioButton_FSACorazonMadre->setChecked(1);
    if (cntlinea==37 && line== "Hermano")ui->radioButton_FSACorazonHermano->setChecked(1);
    if (cntlinea==38 && line== "Hermana")ui->radioButton_FSACorazonHermana->setChecked(1);
    if (cntlinea==39 && line== "Abuelo")ui->radioButton_FSACorazonAbuelo->setChecked(1);
    if (cntlinea==40 && line== "Abuela")ui->radioButton_FSACorazonAbuela->setChecked(1);
    if (cntlinea==41 && line== "Si")ui->radioButton_OperacionGraveSi->setChecked(1);
    if (cntlinea==42 && line== "No")ui->radioButton_OperacionGraveNo->setChecked(1);
    if (cntlinea==43) ui->lineEdit_OperacionGraveCual->setText(line);
    if (cntlinea==44 && line== "Espalda") ui->radioButton_DoloresEspalda->setChecked(1);
    if (cntlinea==45 && line== "Rodilla") ui->radioButton_DoloresRodilla->setChecked(1);
    if (cntlinea==46 && line== "Cuello")  ui->radioButton_DoloresCuello->setChecked(1);
    if (cntlinea==47 && line== "Tobillo") ui->radioButton_DoloresTobillo->setChecked(1);
    if (cntlinea==48 && line== "Codo")    ui->radioButton_DoloresCodo->setChecked(1);
    if (cntlinea==49 && line== "Cadera")  ui->radioButton_DoloresCadera->setChecked(1);
    if (cntlinea==50 && line== "Si")      ui->radioButton_MedicamentoSi->setChecked(1);
    if (cntlinea==51 && line== "No")      ui->radioButton_MedicamentoNo->setChecked(1);
    if (cntlinea==52) ui->lineEdit_Medicamento->setText(line);
    if (cntlinea==53 && line== "Si")    ui->radioButton_VitaminaSuplementoSi->setChecked(1);
    if (cntlinea==54 && line== "No")    ui->radioButton_VitaminaSuplementoNo->setChecked(1);
    if (cntlinea==55) ui->lineEdit_SuplementoNutricional->setText(line);
    if (cntlinea==56 && line== "Si")    ui->radioButton_DietaSi->setChecked(1);
    if (cntlinea==57 && line== "No")    ui->radioButton_DietaNo->setChecked(1);
    if (cntlinea==58) ui->lineEdit_Dieta->setText(line);
    if (cntlinea==59)
    {
    numero=line.toInt();
    ui->spinBox_ComidaporDia->setValue(numero);
    }
    if (cntlinea==60 && line== "Si") ui->radioButton_DesayunaSi->setChecked(1);
    if (cntlinea==61 && line== "No") ui->radioButton_DesayunaNo->setChecked(1);
    if (cntlinea==62 && line== "Si") ui->radioButton_VaricesSi->setChecked(1);
    if (cntlinea==63 && line== "No") ui->radioButton_VaricesNo->setChecked(1);
    if (cntlinea==64 && line== "Si") ui->radioButton_CelulitisSi->setChecked(1);
    if (cntlinea==65 && line== "No") ui->radioButton_CelulitisNo->setChecked(1);

    //Estilo de Vida y Salud
    if (cntlinea==66 && line== "Si")ui->radioButton_FumaSi->setChecked(1);
    if (cntlinea==67 && line== "No")ui->radioButton_FumaNo->setChecked(1);
    if (cntlinea==68 && line== "Cigarrillo1a9")ui->radioButton_Cigarrillo1a9->setChecked(1);
    if (cntlinea==69 && line== "Cigarrillo10a19")ui->radioButton_Cigarrillo10a19->setChecked(1);
    if (cntlinea==70 && line== "Cigarrillomas20")ui->radioButton_Cigarrillomas20->setChecked(1);
    if (cntlinea==71 && line== "Si")ui->radioButton_DeporteSi->setChecked(1);
    if (cntlinea==72 && line== "No")ui->radioButton_DeporteNo->setChecked(1);
    if (cntlinea==73) ui->lineEdit_DeporteCual->setText(line);
    if (cntlinea==74 && line== "Si")ui->radioButton_GimnasioSi->setChecked(1);
    if (cntlinea==75 && line== "No")ui->radioButton_GimnasioNo->setChecked(1);
    if (cntlinea==76 && line== "Buena")ui->radioButton_GimnasioBuena->setChecked(1);
    if (cntlinea==77 && line== "Regular")ui->radioButton_GimnasioRegular->setChecked(1);
    if (cntlinea==78 && line== "Mala")ui->radioButton_GimnasioMala->setChecked(1);
    if (cntlinea==79) ui->lineEdit_GimnasioPorque->setText(line);
    if (cntlinea==80 && line== "Si")ui->radioButton_EjerciciosRegularesSi->setChecked(1);
    if (cntlinea==81 && line== "No")ui->radioButton_EjerciciosRegularesNo->setChecked(1);
    if (cntlinea==82)ui->lineEdit_EjerciciosRegularesCual->setText(line);
    if (cntlinea==83)ui->lineEdit_NoRealizaActidadFisica->setText(line);
    if (cntlinea==84)ui->lineEdit_SiRealizaActividadFisica->setText(line);

    //Objetivos Generales
    if (cntlinea==85 && line== "Si")ui->radioButton_AumentaMasaMuscularSi->setChecked(1);
    if (cntlinea==86 && line== "No")ui->radioButton_AumentaMasaMuscularNo->setChecked(1);
    if (cntlinea==87 && line== "Si")ui->radioButton_TonificarSi->setChecked(1);
    if (cntlinea==88 && line== "No")ui->radioButton_TonificarNo->setChecked(1);
    if (cntlinea==89 && line== "Si")ui->radioButton_BajarPesoSi->setChecked(1);
    if (cntlinea==90 && line== "No")ui->radioButton_BajarPesoNo->setChecked(1);
    if (cntlinea==91 && line== "Si")ui->radioButton_SentireseMejorSi->setChecked(1);
    if (cntlinea==92 && line== "No")ui->radioButton_SentireseMejorNo->setChecked(1);
    if (cntlinea==93 && line== "Si")ui->radioButton_PrescripcionMedicaSi->setChecked(1);
    if (cntlinea==94 && line== "No")ui->radioButton_PrescripcionMedicaNo->setChecked(1);
    if (cntlinea==95 && line== "Si")ui->radioButton_OtroMotivoSi->setChecked(1);
    if (cntlinea==96 && line== "No")ui->radioButton_OtroMotivoNo->setChecked(1);
    if (cntlinea==97) ui->lineEdit_OtroMotivoCual->setText(line);

    //ParQ
    if (cntlinea==98) ui->lineEdit_ParQ01->setText(line);
    if (cntlinea==99) ui->lineEdit_ParQ02->setText(line);
    if (cntlinea==100) ui->lineEdit_ParQ03->setText(line);
    if (cntlinea==101) ui->lineEdit_ParQ04->setText(line);
    if (cntlinea==102) ui->lineEdit_ParQ05->setText(line);
    if (cntlinea==103) ui->lineEdit_ParQ06->setText(line);
    if (cntlinea==104) ui->lineEdit_ParQ07->setText(line);
    //qDebug() << line ;

}
