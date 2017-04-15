#ifndef AGREGARCLIENTE_H
#define AGREGARCLIENTE_H

#include <QDialog>

namespace Ui {
class AgregarCliente;
}

class AgregarCliente : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarCliente(QWidget *parent = 0);
    ~AgregarCliente();
    QString Nombre() const;
    QString Apellido() const;
    QString DNI() const;
    QString Telefono() const;
    QString Edad() const;
    QString FechaPago() const;
    QString FechaVencimiento() const;
    QString IDHuella() const;
    QString Sexo() const;

private slots:
    void on_pushButton_Aceptar_clicked();
    void on_pushButton_Cancelar_clicked();
    void on_pushButton_clicked();
    void CrearArchivoFicha();
    void EscribirArchivoFicha();

private:
    Ui::AgregarCliente *ui;
};

#endif // AGREGARCLIENTE_H
