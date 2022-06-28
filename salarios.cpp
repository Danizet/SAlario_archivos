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
    // Lipmiar el texto de los calculos
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
                    "No se puede calcular el salario");
    }

    // Limpiar widgets
    clean();
    // Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage("Salario de" + nombre + " calculado.", 5000);

}

void Salarios::save()
{

    // Abrir un cuadro de dialogo para seleccionar el path y archivo a guardar
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar calculos de salarios",
                                                         QDir::home().absolutePath() +
                                                         "/salarios.txt",
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
        ui->statusbar->showMessage("Archivo guardado en:" +
                                   nombreArchivo,
                                   4000);
        // Cerrar archivo
        archivo.close();

    }else {
        // Mensaje de error
        QMessageBox::warning(this,
                             "Guardar archivo",
                             "No se puede acceder al archivo para guardar los datos");
    }
}

void Salarios::save_as()
{
    ///QString nombre = ui->inNombre->text();
    ///int horas = ui->inHoras->value();
    QString lala = ui->outCAlculos->toPlainText();
    if(lala == ""){
        this->close();
    }else {
        QMessageBox::StandardButton reply = QMessageBox::question(
                    this,
                    "Salir","Desea guardar el archivo",
                    QMessageBox::Save | QMessageBox::Close | QMessageBox::Cancel);
        /*
                    "Guardar" ,
                    "No guardar",
                    "Cancelar");
                    */
        if(reply == QMessageBox::Save ) {
            save();
        } else if (reply == QMessageBox::Cancel){
            return;
        } else{
            this->close();
        }
        /*
void MainWindow::on_pushButton_clicked()

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                   "My Title", "This is my custom message",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        QApplication::quit();
    } else {
        qDebug() << "No is clicked";
    }
}
 *
 * */

    }

}

void Salarios::on_actionCalcular_triggered()
{
    calculos();
}


void Salarios::on_action_Salir_triggered()
{
    save_as();

}


void Salarios::on_actionGuardar_triggered()
{
    save();
}


void Salarios::on_actionAcerca_de_Salarios_triggered()
{
    //Crear un objeto del cuadro de dialogo
    Acerca *dialog = new Acerca(this);
    // Enviar datos a la otra ventana (Establecer version)
    dialog->setVersion(VERSION);
    //Mostrar la ventana en modo Modal(que se ejecute delante)
    dialog->exec();
    // Luego de cerrar la ventana

}


void Salarios::on_actionAbrir_triggered()
{
    // Abrir un cuadro de dialogo para seleccionar el path y archivo a abrir
    QString nombreArchivo1 = QFileDialog::getOpenFileName(this,
                                                          "Abrir archivo de calculo de salarios",
                                                          QDir::home().absolutePath(),
                                                          "Archivo de texto (*.txt)");

    QFile file(nombreArchivo1);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        ui->outCAlculos->appendPlainText(linea);
    }
    ui->statusbar->showMessage("Archivo:" + nombreArchivo1 + "abierto", 4000);
    file.close() ;

}



