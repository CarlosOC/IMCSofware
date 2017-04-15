#ifndef DIALOGBUSCARCLIENTE_H
#define DIALOGBUSCARCLIENTE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class DialogBuscarCliente;
}

class DialogBuscarCliente : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBuscarCliente(QWidget *parent = 0);
    ~DialogBuscarCliente();
    QString Nombre() const;
    QString Apellido() const;
    QString dni() const;
    QString FechaPago() const;
    QString FechaVencimiento() const;
    QString Id() const;
    QString Sexo() const;
    QString Dni() const;

private slots:

    void on_pushButton_VerFicha_clicked();
    void on_pushButton_Cancelar_clicked();
    void on_pushButton_Aceptar_clicked();
    void on_pushButton_Buscar_clicked();
    void on_pushButton_ModificarDatos_clicked();

private:
    Ui::DialogBuscarCliente *ui;
    enum Columna{ID, IDH, NOMBRE,APELLIDO,SEXO,EDAD,DNI,TEL ,FPAGO, FVENC};
};

#endif // DIALOGBUSCARCLIENTE_H
