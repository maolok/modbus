#include "serialport.h"
#include <QTimer>
#include "principal.h"
#include <QDebug>

serialport::serialport(QWidget *parent)
    : QMainWindow(parent)
{

    connect(serial, &QSerialPort::readyRead, this, &serialport::readData);


    //QTimer *time = new QTimer();

    //time->start(1000);

    //connect (time,&QTimer::timeout,&principal::cicloprincipal);



}

serialport::~serialport()
{

}

bool serialport::configuracionpuerto()
{

        serial->setPortName("ttyACM0");
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

QByteArray serialport::readData()
{
    QByteArray data = serial->readAll();
     qDebug()<<data;
      return data;

}

void serialport::escribirenpuerto(QByteArray data)
{

    serial->write(data);

}










