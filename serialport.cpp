#include "serialport.h"
#include <QTimer>
#include "modbus.h"
#include <QDebug>

serialport::serialport(QWidget *parent)
    : QMainWindow(parent)
{

    connect(serial, &QSerialPort::readyRead, this, &serialport::readData);
    connect (temporizador,&QTimer::timeout,this,&serialport::readbuffer);



}

serialport::~serialport()
{

}

bool serialport::configuracionpuerto()
{

        serial->setPortName("ttyUSB1");
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        if(serial->open(QIODevice::ReadWrite))
        {
            return true;
            qDebug()<<"puerto abierto";


        }

        else {return false;}



}

void serialport::cerrarpuerto()
{
    if (serial->isOpen())
    {
        serial->close();
    }

}

void serialport::readData()
{
    temporizador->start(1500);



}

void serialport::readbuffer()
{
    /*
#ifdef esteban_gay
    qDebug()<<"esteban le gusta ymca";

#else
    qDebug()<<"esteban le gusta lady gaga";
#endif
*/
     temporizador->stop();
     data = serial->readAll();
     qDebug()<<"RESPUESTA : "<<data;
     principal p;


/*
     DataW data1 = p.extraerdatosW(data);
     qDebug()<<"datos :";
     qDebug()<<"id esclavo :"<<data1.idslave;

     qDebug()<<"Registro de inicio:"<<data1.desde;
     qDebug()<<"# Registros escritos :"<<data1.cantidadregistros;
     qDebug()<<"validacion crc :"<<data1.validacioncrc;

*/




     DataR data1 = p.extraerdatosR(data);

     qDebug()<<"datos :";
     qDebug()<<"id esclavo :"<<data1.idslave;

     qDebug()<<"# bytes :"<<data1.numbytes;
     qDebug()<<"datos :"<<data1.data;
     qDebug()<<"validacion crc :"<<data1.validacioncrc;





}



void serialport::escribirenpuerto(QByteArray data)
{

    serial->write(data);

}










