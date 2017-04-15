#ifndef DIALOGFICHA_H
#define DIALOGFICHA_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

namespace Ui {
class DialogFicha;
}

class DialogFicha : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFicha(QWidget *parent = 0);
    ~DialogFicha();
    void Nombre_Archivo (QString NombreArchivo);
private slots:
    void abrir_archivo (QString &nombre_archivo);
    void procesar_linea(const QString &line,int cntlinea);

private:
    Ui::DialogFicha *ui;
};

#endif // DIALOGFICHA_H
