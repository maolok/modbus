#include "modbus.h"


principal::principal()
{

}

//start regis min 0 max 9
//num regis min 1 max 10
QByteArray principal::Writeholdingregister(int idslave,int startregister,int numregister, uint16_t *data)
{

    QByteArray tramafinal;

    int longitud;

    if (numregister == 1)
    {


        unsigned char trama[6];
        trama[0] = idslave;
        trama[1] = 0x06; //write single register
        trama[2] = 0x00;
        trama[3] = startregister;

        trama[4] = Getmsb(data[0]);
        trama[5] = Getlsb(data[0]);

        longitud=sizeof(trama)/sizeof(*trama);



        for (int i=0;i<longitud;i++)
        {
          tramafinal.append(trama[i]);
        }

        int crc = CRC16_3(trama,longitud);
        int msb1 = Getmsb(crc);
        int lsb1 = Getlsb(crc);
        tramafinal.append(lsb1);
        tramafinal.append(msb1);




    }
    else{

        uint16_t msb[numregister];
        uint16_t lsb[numregister];
        for (int i = 0;i<numregister;i++)
        {
            msb[i] = Getmsb(data[i]);

            lsb[i] = Getlsb(data[i]);

        }

        unsigned char trama[(7+(2*numregister))];
        trama[0] = idslave;
        trama[1] = 0x10;   //write multiple registers
        trama[2] = 0x00;
        trama[3] = startregister;
        trama[4] = 0x00;
        trama[5] = numregister;
        trama[6] = numregister*2;

        int k = 1;
        int h = 1;
        for(int j=7;j<(7+numregister*2);j++)
        {

           if (j%2 == 0)
           {

               trama[j] = lsb[j-(7+k)];

               k++;
           }
           else{
               if (j==7)
               {
               trama[j] = msb[j-7];
               }
               else {
                   trama[j] = msb[j-(7+h)];

                   h++;
               }

           }


        }




        longitud=sizeof(trama)/sizeof(*trama);


        for (int i=0;i<longitud;i++)
        {


            tramafinal.append(trama[i]);
        }


        int crc = CRC16_3(trama,longitud);
        int msb1 = Getmsb(crc);
        int lsb1 = Getlsb(crc);
        tramafinal.append(lsb1);
        tramafinal.append(msb1);


    }

#ifdef qdebug
        qDebug()<<"TRAMA ENVIADA WRITE :"<<tramafinal;
        qDebug()<<"SENT ADU: "<<tramafinal.toHex();
#endif
        return tramafinal;


}

QByteArray principal::Readholdingregister(int idslave, int startregister, int numregister)
{
    unsigned char trama[6];
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

    int longitud=sizeof(trama)/sizeof(*trama);

    int crc = CRC16_3(trama,longitud);
    int msb1 = Getmsb(crc);
    int lsb1 = Getlsb(crc);
    tramafinal.append(lsb1);
    tramafinal.append(msb1);

#ifdef qdebug
    qDebug()<<"TRAMA ENVIADA READ :"<<tramafinal;
    qDebug()<<"SENT ADU: "<<tramafinal.toHex();
#endif
    return tramafinal;



}

int principal::validarcrc16(QByteArray trama)
{


    unsigned char trama1[trama.length()];
    QByteArray crccalculado,crctrama;

#ifdef qdebug
    qDebug()<<"received ADU:"<<trama.toHex();
#endif



    for (int i=0;i<trama.length();i++)
    {
        trama1[i]=trama.at(i);

    }


    int longitud=sizeof(trama1)/sizeof(*trama1);

    int crc = CRC16_3(trama1,longitud-2);
    int msb1 = Getmsb(crc);
    int lsb1 = Getlsb(crc);

    crccalculado.append(msb1);

    crccalculado.append(lsb1);

#ifdef qdebug
     qDebug()<<"crc calculado :"<<crccalculado.toHex();
#endif



    crctrama.append(trama.at((trama.length()-1)));
    crctrama.append(trama.at((trama.length()-2)));


#ifdef qdebug
    qDebug()<<"crc trama :"<<crctrama.toHex();
#endif

    if (crctrama == crccalculado)
    {
#ifdef qdebug
        qDebug()<<"CRC ES EL MISMO";
#endif
        return 1;
    }
    else {
#ifdef qdebug
        qDebug()<<"CRC DISTINTO";
#endif
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



    }else{

        datos.validacioncrc = 0;
        datos.idslave = 0;
        datos.desde = 0;
        datos.cantidadregistros=0;

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



    }else{
    datos.validacioncrc = 0;
    datos.idslave = 0;
    datos.numbytes = 0;
    datos.data = 0;
    }

    return datos;


}
unsigned short principal::Getmsb(unsigned short num)  // funcion para conseguir los bytes mas significativos msb
{

  uint16_t palabra = 0xff00;
  unsigned short value2 = num & palabra;
  unsigned short msb = value2>>8;


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
unsigned int principal::CRC16_3(unsigned char *buf, int len)
{
  unsigned int crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++)
  {
  crc ^= (unsigned int)buf[pos];    // XOR byte into least sig. byte of crc

  for (int i = 8; i != 0; i--) {    // Loop over each bit
    if ((crc & 0x0001) != 0) {      // If the LSB is set
      crc >>= 1;                    // Shift right and XOR 0xA001
      crc ^= 0xA001;
    }
    else                            // Else LSB is not set
      crc >>= 1;                    // Just shift right
    }
  }

  return crc;
}



