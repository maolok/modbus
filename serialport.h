#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>




class serialport : public QMainWindow
{
    Q_OBJECT

public:
    serialport(QWidget *parent = 0);
    ~serialport();

    QSerialPort *serial = new QSerialPort(this);


    bool configuracionpuerto(void);
    void cerrarpuerto(void);
    void escribirenpuerto(QByteArray data);
    QByteArray readData(void);

};

#endif // SERIALPORT_H
