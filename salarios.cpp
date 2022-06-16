#include "salarios.h"
#include "ui_salarios.h"


Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_btnCalcular_clicked()
{
    //Obrero modelo("Juan",25,TipoJornada::Matutina);

    //qDebug() << modelo.toString();
    Controlador control;
    control.setDatos("Juan",46,TipoJornada::Matutina);
    control.calcular();
    if (control.calcular()){
        qDebug() << control.getDAtos();
    } else{
        qDebug() << "No se pudo calcular datos";
    }

}

