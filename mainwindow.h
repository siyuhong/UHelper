#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QButtonGroup>
#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QMetaEnum>

#define DISPLAYMODE_ASCII 0
#define DISPLAYMODE_HEX 1

#define SENDOUTMODE_ASCII 0
#define SENDOUTMODE_HEX 1

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_uartDisconnect_clicked();

    void on_pushButton_uartConnect_clicked();

    void on_buttom_sendout_clicked();

private:
    void Init();
    void Init_UartPort();
    void Init_UartDps();
    void Init_UI();
    void setNewsColor(Qt::GlobalColor color);

    Ui::MainWindow *ui;

    QSerialPort *mSerial;
    QButtonGroup* mBGdisplaymode;
    QButtonGroup* mBGsendoutmode;
    QTimer *mAutosendoutTimer;
    enum state { s_connect, s_disconnect} uart_state;

private slots:
    void on_comBox_uartPort_clicked();
    void slot_uartReadData();
    void slot_Timeout_Uartsendout();
    void slot_uartError(QSerialPort::SerialPortError error);
    void on_checkBox_sendoutAutoResend_clicked(bool checked);
    void on_lineEdit_AutoResend_textChanged(const QString &arg1);
    void on_pushButton_clear_TBinput_clicked();
    void on_pushButton_clear_TBoutput_clicked();
    void on_comBox_uartDps_currentTextChanged(const QString &arg1);
    void on_comBox_uartDataLen_currentIndexChanged(const QString &arg1);
    void on_comBox_uartCheckBit_currentIndexChanged(int index);
    void on_comBox_uartFlowControl_currentIndexChanged(int index);
    void on_comBox_uartStopBit_currentIndexChanged(int index);
    void on_comBox_uartDps_currentIndexChanged(int index);
};

//Dialog
//class QLable;

#endif // MAINWINDOW_H
