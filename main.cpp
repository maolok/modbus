#include "serialport.h"
#include <QApplication>
#include "principal.h"
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serialport w;
    w.configuracionpuerto();

    //QByteArray trama;

    uint16_t tramawrite[] = {0x2a,0x10,0x00,0x00,0x00,0x02,0x04,0x00,0x01,0x00,0x05,0xec,0x88};
    uint16_t tramaread[] = {0x2a,0x03,0x00,0x00,0x00,0x02,0xc2,0x10};

    QByteArray tramawrite1;
    QByteArray tramaread1;
    //trama2.append(trama[2]);

    //trama.append(0x0);

    //qDebug()<<QString::fromh;

    w.show();

    for(int i=0;i<13;i++)
    {

        tramawrite1.append(tramawrite[i]);

    }

    for (int j=0;j<8;j++)
    {
        tramaread1.append(tramaread[j]);
    }
    qDebug()<<tramaread1;
    w.escribirenpuerto(tramaread1);
    return a.exec();
}
