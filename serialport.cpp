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

        serial->setPortName("ttyUSB0");
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

     temporizador->stop();
     data = serial->readAll();
     principal p;


#ifdef qdebugwrite

     DataW datoswrite = p.extraerdatosW(data);
     qDebug()<<"datos :";
     qDebug()<<"id esclavo :"<<datoswrite.idslave;

     qDebug()<<"Registro de inicio:"<<datoswrite.desde;
     qDebug()<<"# Registros escritos :"<<datoswrite.cantidadregistros;
     qDebug()<<"validacion crc :"<<datoswrite.validacioncrc;


#else



     DataR datosread = p.extraerdatosR(data);

     qDebug()<<"datos :";
     qDebug()<<"id esclavo :"<<datosread.idslave;

     qDebug()<<"# bytes :"<<datosread.numbytes;
     qDebug()<<"datos :"<<datosread.data;
     qDebug()<<"validacion crc :"<<datosread.validacioncrc;

#endif



}



void serialport::escribirenpuerto(QByteArray data)
{

    serial->write(data);

}










