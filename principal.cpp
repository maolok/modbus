#include "principal.h"


principal::principal()
{

}


//start regis min 0 max 9
//num regis min 1 max 10
QByteArray principal::Writeholdingregister(int idslave,int startregister,int numregister, uint16_t *data)
{
    uint16_t trama[(7+(2*numregister))];
    QByteArray tramafinal;

    trama[0] = idslave;

    if (numregister == 1)
    {
        trama[1] = 0x06;
    }
    else{
        trama[1] = 0x10;
    }


    trama[2] = 0x00;
    trama[3] = startregister;
    trama[4] = 0x00;
    trama[5] = numregister;
    trama[6] = numregister*2;


    for(int j=7;j<(7+(numregister*2));j++)
    {
        trama[j] = data[j-7];

    }

        int longitud=sizeof(trama)/sizeof(*trama);


        for (int i=0;i<longitud;i++)
        {


            tramafinal.append(trama[i]);
        }


        int crc = CRC16_2(tramafinal,longitud);


        int msb = Getmsb(crc);
        int lsb = Getlsb(crc);




        tramafinal.append(lsb);
        tramafinal.append(msb);



        return tramafinal;

}

QByteArray principal::Readholdingregister(int idslave, int startregister, int numregister)
{
    uint16_t trama[6];
    QByteArray tramafinal;

    trama[0] = idslave;
    trama[1] = 0x03;       //codigo para leer holdingregister
    trama[2] = 0x00;
    trama[3] = startregister;
    trama[4] = 0x00;
    trama[5] = numregister;



    for (int i=0;i<6;i++)
    {


        tramafinal.append(trama[i]);
    }

    int crc = CRC16_2(tramafinal,6);


    int msb = Getmsb(crc);
    int lsb = Getlsb(crc);




    tramafinal.append(lsb);
    tramafinal.append(msb);



    return tramafinal;


}

int principal::validarcrc16(QByteArray trama)
{

    QByteArray crccalculado,crctrama;





    uint16_t crc16 = CRC16_2(trama,(trama.length()-2));
    //qDebug()<<crc16;

    crccalculado.append(Getmsb(crc16));

    crccalculado.append(Getlsb(crc16));





    qDebug()<<"crc calculado :"<<crccalculado;

    crctrama.append(trama.at((trama.length()-1)));
    crctrama.append(trama.at((trama.length()-2)));

    qDebug()<<"crc trama :"<<crctrama;

    if (crctrama == crccalculado)
    {

        qDebug()<<"CRC ES EL MISMO";
        return 1;
    }
    else {qDebug()<<"CRC DISTINTO";
                    return 0;}


}

DataW principal::extraerdatosW(QByteArray trama)
{
    DataW datos;
    if(validarcrc16(trama) == 1)
    {

         datos.validacioncrc = 1;
         datos.idslave = trama.at(0);
         datos.desde = trama.at(3);
         datos.cantidadregistros=trama.at(5);
         //qDebug()<<"crc16validado";





    }else{
    datos.validacioncrc = 0;
    }

    return datos;

}

DataR principal::extraerdatosR(QByteArray trama)
{
    DataR datos;
    if(validarcrc16(trama) == 1)
    {

         datos.validacioncrc = 1;
         datos.idslave = trama.at(0);
         datos.numbytes = trama.at(2);

         for(int i=3;i<3+datos.numbytes;i++)
         {
             datos.data.append(trama.at(i));
         }

         //qDebug()<<"crc16validado";





    }else{
    datos.validacioncrc = 0;
    }

    return datos;


}
unsigned short principal::Getmsb(unsigned short num)  // funcion para conseguir los bytes mas significativos msb
{

  uint16_t palabra = 0xff00;
  unsigned short value2 = num & palabra;
  unsigned short msb = value2>>8;
  //Serial.println(msb, HEX);

  return msb;


  }

unsigned short principal::Getlsb(unsigned short num)// funcion para conseguir los bytes menos significativos lsb
{

  uint16_t palabra = 0x00ff;
  unsigned short lsb = num & palabra;

  return lsb;


}
uint principal::CRC16_2(QByteArray buf, int len)
{
  uint crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (uint)buf[pos];          // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;
}



