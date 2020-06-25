#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "serialport.h"
#include "principal.h"
#include <QDebug>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Form *ui;
    serialport *puerto = new serialport();
    principal *modbus = new principal();

};

#endif // FORM_H
