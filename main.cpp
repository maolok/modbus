#include "serialport.h"
#include <QApplication>
#include "modbus.h"
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>
#include <QTimer>
#include <QObject>
#include "form.h"


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    Form formulario;
    formulario.show();


    return a.exec();
}
