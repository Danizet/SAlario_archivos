#include "salarios.h"
#include "ui_salarios.h"


Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador = new Controlador;
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_btnCalcular_clicked()
{
    /*
    //Obrero modelo("Juan",25,TipoJornada::Matutina);

    //qDebug() << modelo.toString();
    Controlador control;
    //control.setDatos("Juan",46,TipoJornada::Matutina);
    control.calcular();
    if (control.calcular()){
        qDebug() << control.getDAtos();
    } else{
        qDebug() << "No se pudo calcular datos";
    }
    */
    QString nombre = ui->inNombre->text();
    int horas = ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
        jornada = TipoJornada::Matutina;
    } else if(ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    } else{
        jornada = TipoJornada::Nocturna;
    }
    // Validacion de datos
    if(nombre == "" || horas == 0){
        QMessageBox::warning(this,
                             "Advertencia",
                             "El nombre y/o el numero de horas es incorrecto");
        return;
    }

    // Establecer datos al controlador
    m_controlador->setDatos(nombre, horas, jornada);
    // Calcular salarios
    if (m_controlador->calcular()){
        //Muestra los resultados
        //qDebug() << m_controlador->getDAtos();
        ui->outCAlculos->appendPlainText(m_controlador->getDAtos());
    } else{
        QMessageBox::critical(
                    this,
                    "ERROR",
                    "No se peude calcular el salario");

    }

    // Limpiar widgets
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true); // Para que vuelva a matutina
    ui->inNombre->setFocus(); // Para volver el cursor al nombre
    // Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage("Salario de" + nombre + " calculado.", 5000);

}

