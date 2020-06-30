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
    uint16_t data[] = {'@','@',0xcccc};
    QByteArray tramaescritura = Modbus->Writeholdingregister(42,0,3,data);
    puerto->escribirenpuerto(tramaescritura);


}

void Form::on_pushButton_2_clicked()
{
    QByteArray tramalectura = Modbus->Readholdingregister(42,0,3);
    puerto->escribirenpuerto(tramalectura);

}
