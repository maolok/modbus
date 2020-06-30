#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

//#define qdebugwrite


class serialport : public QMainWindow
{
    Q_OBJECT

public:
    serialport(QWidget *parent = 0);
    ~serialport();

    QSerialPort *serial = new QSerialPort(this);

    QByteArray data;
    bool configuracionpuerto(void);
    void cerrarpuerto(void);
    void escribirenpuerto(QByteArray data);
    void readData(void);

    QTimer *temporizador = new QTimer();

public slots:

    void readbuffer(void);

};

#endif // SERIALPORT_H
