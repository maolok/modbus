#include "form.h"
#include "ui_form.h"


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    puerto->configuracionpuerto();




}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    uint16_t data[] = {0x4,0x5,0x5,0x7};
    QByteArray tramaescritura = modbus->Writeholdingregister(42,0,2,data);
    puerto->escribirenpuerto(tramaescritura);
    qDebug()<<"PETICION : "<<tramaescritura;

}

void Form::on_pushButton_2_clicked()
{
    QByteArray tramalectura = modbus->Readholdingregister(42,0,1);
    puerto->escribirenpuerto(tramalectura);

    qDebug()<<"PETICION : "<<tramalectura;

}
