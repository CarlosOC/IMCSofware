#ifndef DIALOGLISTACLIENTES_H
#define DIALOGLISTACLIENTES_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class DialogListaClientes;
}

class DialogListaClientes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogListaClientes(QWidget *parent = 0);
    ~DialogListaClientes();
    QString Nombre() const;
    QString Apellido() const;
    QString dni() const;
    QString Sexo() const;
    int Edad() const;
    double Salario() const;


private slots:
    void CargarTabla();
private:

    Ui::DialogListaClientes *ui;
    enum Columna{ID, IDH, NOMBRE,APELLIDO,SEXO,DNI,EDAD,TEL ,FPAGO, FVENC};

};

#endif // DIALOGLISTACLIENTES_H
