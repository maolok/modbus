#include "principal.h"

#include "Crc16.h"
#include <QDebug>


int maquinastate;
principal::principal()
{
     maquinastate = INICIALIZARTRAMA;
    //trama = "0";
}

void principal::cicloprincipal()
{

























}

void principal::Writeholdingregister(int idslave,int startregister,int numregister)
{
    MASTERTRAMADATA trama1;
    trama1.data[0] = idslave;
    trama1.data[1] = 0x10;
    trama1.data[2] = startregister;
    trama1.data[3] = numregister;


    Crc16 crc;

    crc.clearCrc();
   // u_int8_t entero[3] = {0x01,0x02,0x03};
   unsigned int crc16 = crc.Modbus(trama1.data,0,3);

   qDebug()<<"crc16 "<<crc16;


   qDebug()<<trama1.data[1];


}



