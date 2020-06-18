#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QObject>
#include <QString>



//int maquinastate;


enum MAQUINA_ESTADOS{

    INICIALIZARTRAMA,
    CALCULARCRC16,
    ENVIARTRAMA,
    LEERTRAMA,
    VERIFICARTRAMALEIDA
};

struct MASTERTRAMADATA{


   uint8_t desde;
   uint8_t hasta;
   uint8_t data[];


};

struct SLAVETRAMADATA{

   int id;
   int data;
   int crc16;

};

class principal
{
public:

    principal();

    void Writeholdingregister(int idslave,int startregister,int numregister);

    public slots:

    void cicloprincipal(void);



};

#endif // PRINCIPAL_H
