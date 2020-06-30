#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>

#define qdebug//poner en ingles debug


struct DataW{

   int validacioncrc;
   int idslave;
   int desde;
   int cantidadregistros;

};

struct DataR{

    int validacioncrc;
    int idslave;
    int numbytes;
    QByteArray data;



};

class principal
{
public:

    principal();


    QByteArray Writeholdingregister(int idslave,int startregister,int numregister,uint16_t *data);
    QByteArray Readholdingregister(int idslave,int startregister,int numregister);
    DataW extraerdatosW(QByteArray trama);
    DataR extraerdatosR(QByteArray trama);


private:

    unsigned short Getmsb(unsigned short num);
    unsigned short Getlsb(unsigned short num);
    uint CRC16_2(QByteArray buf, int len);
    unsigned int CRC16_3(unsigned char *buf, int len);
    int validarcrc16(QByteArray trama);


};



#endif // PRINCIPAL_H
