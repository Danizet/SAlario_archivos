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
    calculos();
}


void Salarios::on_actionNuevo_triggered()
{
    // Limpiar widgets
    clean();
    // Lipmiar ek texto de los calculos
    ui->outCAlculos->clear();
    // Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage("Nuevos calculos de salario", 3000);

}

void Salarios::clean()
{
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true); // Para que vuelva a matutina
    ui->inNombre->setFocus(); // Para volver el cursor al nombre

}

void Salarios::calculos()
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
    clean();
    // Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage("Salario de" + nombre + " calculado.", 5000);

}


void Salarios::on_actionCalcular_triggered()
{
    calculos();
}


void Salarios::on_action_Salir_triggered()
{
    this->close();
}


void Salarios::on_actionGuardar_triggered()
{
    // Abrir un cuadro de dialogo para seleccionar el path y archivo a guardar
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                   "Guardar calculos de salarios",
                                                   QDir::home().absolutePath() + "/salarios.txt",
                                                   "Archivo de texto (*.txt)");

    // Crear un archivo File
    QFile archivo(nombreArchivo);
    // Tratar arch. para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un objeto 'stream' de texto
        QTextStream salida(&archivo);
        //Enviar los datos del resultado a la salida
        salida << ui->outCAlculos->toPlainText();
        //Mostrar mensaje en la barra de estados
        ui->statusbar->showMessage("Archivo guardado en:" + nombreArchivo, 4000);
        // Cerrar archivo
        archivo.close();

    }else {
        // Mensaje de error
        QMessageBox::warning(this,
                             "Guardar archivo",
                             "No se puede acceder al archivo para guardar los datos");
    }
}


void Salarios::on_actionAcerca_de_Salarios_triggered()
{
    //Crear un objeto del cuadro de dialogo
    Acerca *dialog = new Acerca(this);
    // Enviar datos a la otra ventana (Establecer version)
    dialog->setVersion(VERSION);
    //Mostrar la ventana en modo Modal(que se ejecute delante)
    dialog->exec();

}

