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
    uint16_t data[] = {0xffff,0xaaaa,0xcccc,0xbbbb,0xabcd};
    QByteArray tramaescritura = modbus->Writeholdingregister(42,0,5,data);
    puerto->escribirenpuerto(tramaescritura);
    qDebug()<<"PETICION : "<<tramaescritura;
    qDebug()<<"SENT ADU: "<<tramaescritura.toHex();

}

void Form::on_pushButton_2_clicked()
{
    QByteArray tramalectura = modbus->Readholdingregister(42,0,5);
    puerto->escribirenpuerto(tramalectura);

    qDebug()<<"PETICION : "<<tramalectura;
    qDebug()<<"SENT ADU: "<<tramalectura.toHex();

}
