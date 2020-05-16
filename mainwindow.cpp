#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ascii_table.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);

     Init();

     //读取用户偏好
     readSettings();

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::writeSettings(){

    QSettings settings("FSF","UHelper");

    // 主窗体位置及大小
    settings.beginGroup("MainWindows");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    settings.endGroup();

    // 接收设置
    settings.beginGroup("DisplaySettings");
    settings.setValue("displayMode",mBGdisplaymode->checkedId());
    settings.setValue("displayNewline",ui->checkBox_displayNewline->isChecked());
    settings.setValue("displayTime",ui->checkBox_displayTime->isChecked());
    settings.endGroup();

    // 发送设置
    settings.beginGroup("SendoutSettings");
    settings.setValue("sendoutMode",mBGsendoutmode->checkedId());
    settings.setValue("sendoutAutoResend",mBGsendoutmode->checkedId());
    settings.setValue("sendoutAutoResendTime",ui->lineEdit_AutoResend->text());
    settings.endGroup();
}

void MainWindow::readSettings(){

    QSettings settings("FSF","UHelper");

    settings.beginGroup("MainWindows");
    resize(settings.value("size",QSize(
                              (QApplication::desktop()->width() - width()) / 2,
                              (QApplication::desktop()->height() - height()) / 2
                              )).toSize());
    move(settings.value("pos",QPoint(DEFAULT_W,DEFAULT_H)).toPoint());
    settings.endGroup();

    settings.beginGroup("DisplaySettings");
    if(DISPLAYMODE_ASCII == settings.value("displayMode",DISPLAYMODE_ASCII).toInt()){
        ui->radioButton_displayASCII->setChecked(true);
    }else{
        ui->radioButton_displayHEX->setChecked(true);
    }
    ui->checkBox_displayNewline->setChecked(
                settings.value("displayNewline",true).toBool());
    ui->checkBox_displayTime->setChecked(
                settings.value("displayTime",false).toBool());
    settings.endGroup();

    settings.beginGroup("SendoutSettings");
    if(SENDOUTMODE_ASCII == settings.value("sendoutMode",SENDOUTMODE_ASCII).toInt()){
        ui->radioButton_sendoutASCII->setChecked(true);
    }else{
        ui->radioButton_sendoutHEX->setChecked(true);
    }
    ui->checkBox_sendoutAutoResend->setChecked(
                settings.value("sendoutAutoResend",false).toBool());
    ui->lineEdit_AutoResend->setText(
                settings.value("sendoutAutoResendTime","1000").toString());
    settings.endGroup();
}

/**
 * @brief MainWindow::Init_UartPort
 * 利用QSerialPortInfo获取端口信息，并更新
 */
void MainWindow::Init_UartPort(){

    ui->comBox_uartPort->clear();

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comBox_uartPort->addItem(info.portName());
    }

}

///**
// * @brief MainWindow::Init_UartDps
// * 利用QSerialPortInfo获取系统支持的波特率，并更新
// */
//void MainWindow::Init_UartDps(){

//    ui->comBox_uartDps->clear();

//    foreach (const qint32 &baudrate,  QSerialPortInfo::standardBaudRates()) {
//        ui->comBox_uartDps->addItem(QString::number(baudrate));
//    }

//    ui->comBox_uartDps->setCurrentIndex(7);

//}

void MainWindow::Init_UI(){

    ui->textBrowser_intput->clear();

    //仅能输入大于0的数字
    ui->lineEdit_AutoResend->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->comBox_uartDataLen->setCurrentIndex(3);
    ui->comBox_uartDps->setCurrentIndex(7);

    ui->radioButton_displayASCII->setChecked(true);
    ui->radioButton_sendoutASCII->setChecked(true);

    ui->pushButton_uartConnect->setEnabled(true);
    ui->pushButton_uartDisconnect->setEnabled(false);
    ui->buttom_sendout->setEnabled(false);

    ui->checkBox_displayNewline->setChecked(true);
    ui->checkBox_displayTime->setChecked(false);
    ui->checkBox_sendoutAutoResend->setChecked(false);

    connect(ui->menu_file,SIGNAL(triggered(QAction*)),this,SLOT(slot_menu_file(QAction*)));
    connect(ui->menu_tools,SIGNAL(triggered(QAction*)),this,SLOT(slot_menu_tools(QAction*)));
//    connect(ui->menu_setting,SIGNAL(triggered(QAction*)),this,SLOT(slot_menu_setting(QAction*)));
    connect(ui->menu_setStyle,SIGNAL(triggered(QAction*)),this,SLOT(slot_menu_setting(QAction*)));
    connect(ui->menu_help,SIGNAL(triggered(QAction*)),this,SLOT(slot_menu_help(QAction*)));;

    //set action Shortcut
    ui->action_ASCII->setShortcut(tr("Ctrl+A"));
    ui->action_baseConversion->setShortcut(tr("Ctrl+B"));
    ui->action_saveRecnews->setShortcut(tr("Ctrl+S"));

    Init_UartPort();

}

/**
 * @brief MainWindow::slot_menu_file
 * @param select
 * 保存接收框消息为txt文件
 */
void MainWindow::slot_menu_file(QAction *select){

    if(ui->action_saveRecnews == select){

        QString saveFile = "";
        //获取保存路径及文件名
        saveFile = QFileDialog::getSaveFileName(this,"保存","","文本文件(*.txt)");

        QString filepath = QFileInfo(saveFile).absolutePath();
        QString filename = QFileInfo(saveFile).fileName();

        QDir mDir;
        //保存当前路径
        QString currentDir = mDir.currentPath();

        QFile *tempFile = new QFile();
        //设置保存路径
        mDir.setCurrent(filepath);

        tempFile->setFileName(filename);

        if(tempFile->open(QIODevice::WriteOnly|QIODevice::Text)){
            QString wStr = ui->textBrowser_intput->document()->toPlainText();

            QTextStream streamFileOut(tempFile);
            streamFileOut.setCodec("UTF-8");
            streamFileOut << wStr;
            streamFileOut.flush();

            // tempFile->write(wStr.toLocal8Bit().data(),wStr.length());
            tempFile->close();
        }
        else{
            setNewsColor(Qt::red);
            mlaybelNews->setText("Save File Error!");
        }

        setNewsColor(Qt::black);
        mlaybelNews->setText("Save File Success!");

        //程序路径复原
        mDir.setCurrent(currentDir);
    }
}

void MainWindow::slot_menu_tools(QAction *select){

    if(ui->action_ASCII == select){

        QWidget *mASCIItabDLg = new ASCII_Table;
        mASCIItabDLg->setWindowTitle("ASCII Table");
        mASCIItabDLg->show();
    }
}

void MainWindow::slot_menu_setting(QAction *select){

    //Radio
    if(ui->action_styleDefault == select){
        ui->action_styleDefault->setChecked(true);
        ui->action_styleDark->setChecked(false);
        ui->action_styleCustom->setChecked(false);
    }
    if(ui->action_styleDark == select){
        ui->action_styleDefault->setChecked(false);
        ui->action_styleDark->setChecked(true);
        ui->action_styleCustom->setChecked(false);
    }
    if(ui->action_styleCustom == select){
        ui->action_styleDefault->setChecked(false);
        ui->action_styleDark->setChecked(false);
        ui->action_styleCustom->setChecked(true);
    }
}

void MainWindow::slot_menu_help(QAction *select){}

/**
 * @brief MainWindow::Init
 * 变量+UI初始化
 */
void MainWindow::Init(){

    uart_state = s_disconnect;
    mAutosendoutTimer = new QTimer(this);
    connect(mAutosendoutTimer,SIGNAL(timeout()),this,SLOT(slot_Timeout_Uartsendout()));

    mBGdisplaymode = new QButtonGroup(this);
    mBGdisplaymode->addButton(ui->radioButton_displayASCII);
    mBGdisplaymode->addButton(ui->radioButton_displayHEX);
    mBGdisplaymode->setId(ui->radioButton_displayASCII,DISPLAYMODE_ASCII);
    mBGdisplaymode->setId(ui->radioButton_displayHEX,DISPLAYMODE_HEX);

    mBGsendoutmode = new QButtonGroup(this);
    mBGsendoutmode->addButton(ui->radioButton_sendoutASCII);
    mBGsendoutmode->addButton(ui->radioButton_sendoutHEX);
    mBGsendoutmode->setId(ui->radioButton_sendoutASCII,SENDOUTMODE_ASCII);
    mBGsendoutmode->setId(ui->radioButton_sendoutHEX,SENDOUTMODE_HEX);

    mlaybeNewsname = new QLabel;
    mlaybeNewsname->setText("News:");
    statusBar()->addWidget(mlaybeNewsname);
    mlaybelNews = new QLabel;
    statusBar()->addWidget(mlaybelNews);

    Init_UI();

    connect(ui->comBox_uartPort,SIGNAL(clicked()),this,SLOT(on_comBox_uartPort_clicked()));

}

/**
 * @brief MainWindow::on_pushButton_uartDisconnect_clicked
 * 断开串口连接 - 槽函数
 */
void MainWindow::on_pushButton_uartDisconnect_clicked(){

    if(s_connect == uart_state){

        mAutosendoutTimer->stop();
        mSerial->close();

        uart_state = s_disconnect;
        ui->pushButton_uartConnect->setEnabled(true);
        ui->pushButton_uartDisconnect->setEnabled(false);

        setNewsColor(Qt::black);
        mlaybelNews->setText("SerialPort Close Success!");
    }
}

/**
 * @brief MainWindow::on_pushButton_uartConnect_clicked
 * 串口连接 - 槽函数
 */
void MainWindow::on_pushButton_uartConnect_clicked(){

    //获取串口参数并设置
    mSerial = new QSerialPort();

    QString mPortName = ui->comBox_uartPort->currentText();
    QSerialPort::BaudRate mBaudRate = (QSerialPort::BaudRate)ui->comBox_uartDps->currentText().toInt();
    QSerialPort::DataBits mDataBits = (QSerialPort::DataBits)ui->comBox_uartDataLen->currentText().toInt();
    QSerialPort::FlowControl mFlowControl = (QSerialPort::FlowControl)ui->comBox_uartFlowControl->currentIndex();

    QSerialPort::Parity mParity;
    if(0 == ui->comBox_uartCheckBit->currentIndex()){
       mParity = QSerialPort::NoParity;
    }
    else{
        mParity = (QSerialPort::Parity)(ui->comBox_uartCheckBit->currentIndex() + 1);
    }
    QSerialPort::StopBits mStopBits = (QSerialPort::StopBits)(ui->comBox_uartStopBit->currentIndex() + 1);

    qDebug() << mPortName;
    qDebug() << mBaudRate;
    qDebug() << mDataBits;
    qDebug() << mFlowControl;
    qDebug() << mParity;
    qDebug() << mStopBits;

    mSerial->setPortName(mPortName);
    mSerial->setBaudRate(mBaudRate);
    mSerial->setDataBits(mDataBits);
    mSerial->setFlowControl(mFlowControl);
    mSerial->setParity(mParity);
    mSerial->setStopBits(mStopBits);

    if(mSerial->open((QIODevice::ReadWrite))){
        uart_state = s_connect;
        ui->pushButton_uartConnect->setEnabled(false);
        ui->pushButton_uartDisconnect->setEnabled(true);
        ui->buttom_sendout->setEnabled(true);

        //清缓存
        mSerial->clear();

        connect(mSerial,SIGNAL(readyRead()),this,SLOT(slot_uartReadData()));
        connect(mSerial,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),
                this,SLOT(slot_uartError(QSerialPort::SerialPortError)));
        setNewsColor(Qt::black);
        mlaybelNews->setText("SerialPort Open Success!");
    }
    else{
        uart_state = s_disconnect;
        setNewsColor(Qt::red);
        mlaybelNews->setText("SerialPort Open Fail!");
    }
}

/**
 * @brief MainWindow::on_buttom_sendout_clicked
 * 串口数据发送 - 槽函数
 */
void MainWindow::on_buttom_sendout_clicked(){

    if(uart_state != s_connect){
        setNewsColor(Qt::red);
        mlaybelNews->setText("SerialPort is't Connect.");
        return;
    }

    if(mBGsendoutmode->checkedId() == SENDOUTMODE_ASCII){
        //支持中文需使用toLocal8Bit()
        mSerial->write(ui->textEdit_output->toPlainText().toLocal8Bit().data());
    }
    else if(mBGsendoutmode->checkedId() == SENDOUTMODE_HEX){
        QByteArray bytehex = QByteArray::fromHex(
                    ui->textEdit_output->toPlainText().toLatin1()).data();
         mSerial->write(bytehex);
    }
}

/**
 * @brief MainWindow::on_comBox_uartPort_clicked
 * 点击comBox_uartPort - 槽函数
 * 用以更新端口信息
 */
void MainWindow::on_comBox_uartPort_clicked(){
    Init_UartPort();
}

/**
 * @brief MainWindow::slot_Timeout_Uartsendout
 * 定时重发 - 定时间超时槽函数
 */
void MainWindow::slot_Timeout_Uartsendout(){
    on_buttom_sendout_clicked();
}

/**
 * @brief MainWindow::slot_uartReadData
 * 串口接收数据 - 槽函数
 */
void MainWindow::slot_uartReadData(){

    if(ui->checkBox_displayNewline->isChecked()){
        if(ui->textBrowser_intput->document()->toPlainText() != "")
            ui->textBrowser_intput->insertPlainText("\r\n");
    }

    if(ui->checkBox_displayTime->isChecked()){
        ui->textBrowser_intput->insertPlainText(QDateTime::currentDateTime().toString("[hh:mm:ss:zzz] "));
    }

    if(DISPLAYMODE_ASCII == mBGdisplaymode->checkedId()){

        ui->textBrowser_intput->insertPlainText(QString::fromLocal8Bit(mSerial->readAll()));

    }

    else if(DISPLAYMODE_HEX == mBGdisplaymode->checkedId()){

        QString re = "";
        QByteArray bytearray = mSerial->readAll();

        //hex char[] 转QString
        for(int i = 0; i < bytearray.length(); i++){
            if((unsigned char)bytearray[i] > 255)
                re.append("Error ");
            re.append("0x" + QString::number((unsigned char)bytearray[i],16) + " ");
        }

        ui->textBrowser_intput->insertPlainText(re);
    }

}

/**
 * @brief MainWindow::slot_uartError
 * @param error
 * 串口出错 - 槽函数
 * 用以显示错误信息
 */
void MainWindow::slot_uartError(QSerialPort::SerialPortError error){

    QMetaEnum metaError = QMetaEnum::fromType<QSerialPort::SerialPortError>();
    mlaybelNews->setText(metaError.valueToKey(error));
    setNewsColor(Qt::red);
}

/**
 * @brief MainWindow::on_checkBox_sendoutAutoResend_clicked
 * @param checked
 * 定时重发功能 - 槽函数
 */
void MainWindow::on_checkBox_sendoutAutoResend_clicked(bool checked){

    if(checked){

        if(s_connect == uart_state){
            mAutosendoutTimer->start(ui->lineEdit_AutoResend->text().toInt());
        }
        else{
            setNewsColor(Qt::red);
            mlaybelNews->setText("SerialPort is't Connect.");
            return;
        }
    }
    else{
        if(mAutosendoutTimer->isActive())
            mAutosendoutTimer->stop();
    }
}

/**
 * @brief MainWindow::on_lineEdit_AutoResend_textChanged
 * @param arg1
 * 更改定时重发时间 - 槽函数
 * 为支持开启定时重发状态更改定时时间
 */
void MainWindow::on_lineEdit_AutoResend_textChanged(const QString &arg1){

    if(ui->checkBox_sendoutAutoResend->isChecked()){
        if(mAutosendoutTimer->isActive()){
            mAutosendoutTimer->stop();
            mAutosendoutTimer->start(arg1.toInt());
        }
    }
}

/**
 * @brief MainWindow::setNewsColor
 * @param color
 * 设置News提醒颜色
 */
void MainWindow::setNewsColor(Qt::GlobalColor color){
    QPalette pa;
    pa.setColor(QPalette::WindowText,color);
    mlaybelNews->setPalette(pa);
}

void MainWindow::on_pushButton_clear_TBinput_clicked(){
    ui->textBrowser_intput->clear();
}

void MainWindow::on_pushButton_clear_TBoutput_clicked(){
    ui->textEdit_output->clear();
}

/**
 * 以下用于开启串口后设置串口参数
 */
void MainWindow::on_comBox_uartDps_currentTextChanged(const QString &arg1){

    if(s_connect == uart_state){

        //自定义波特率
        if(ui->comBox_uartDps->currentIndex() == 8){
            return;
        }

        QSerialPort::BaudRate mBaudRate = (QSerialPort::BaudRate)arg1.toInt();

        if(mSerial->setBaudRate(mBaudRate)){
            setNewsColor(Qt::black);
            mlaybelNews->setText("SerialPort setBaudRate is OK.");
        }
        else{
            setNewsColor(Qt::red);
            mlaybelNews->setText("SerialPort setBaudRate is Error.");
        }
    }

}

/**********************串口参数改动时触发的槽函数***************************************/
void MainWindow::on_comBox_uartDataLen_currentIndexChanged(const QString &arg1){

    if(s_connect == uart_state){

        QSerialPort::DataBits mDataBits = (QSerialPort::DataBits)arg1.toInt();

        if(mSerial->setDataBits(mDataBits)){
            setNewsColor(Qt::black);
            mlaybelNews->setText("SerialPort setDataBits is OK.");
        }
        else{
            setNewsColor(Qt::red);
            mlaybelNews->setText("SerialPort setDataBits is Error.");
        }
    }
}

void MainWindow::on_comBox_uartCheckBit_currentIndexChanged(int index){

    if(s_connect == uart_state){

        QSerialPort::Parity mParity;
        if(0 == index){
           mParity = QSerialPort::NoParity;
        }
        else{
            mParity = (QSerialPort::Parity)(index + 1);
        }


        if(mSerial->setParity(mParity)){
            setNewsColor(Qt::black);
            mlaybelNews->setText("SerialPort setParity is OK.");
        }
        else{
            setNewsColor(Qt::red);
            mlaybelNews->setText("SerialPort setParity is Error.");
        }
    }
}



void MainWindow::on_comBox_uartFlowControl_currentIndexChanged(int index){

    if(s_connect == uart_state){

        QSerialPort::FlowControl mFlowControl = (QSerialPort::FlowControl)index;


        if(mSerial->setFlowControl(mFlowControl)){
            setNewsColor(Qt::black);
            mlaybelNews->setText("SerialPort setFlowControl is OK.");
        }
        else{
            setNewsColor(Qt::red);
            mlaybelNews->setText("SerialPort setFlowControl is Error.");
        }
    }
}

void MainWindow::on_comBox_uartStopBit_currentIndexChanged(int index){

    if(s_connect == uart_state){

         QSerialPort::StopBits mStopBits = (QSerialPort::StopBits)(index + 1);


        if(mSerial->setStopBits(mStopBits)){
            setNewsColor(Qt::black);
            mlaybelNews->setText("SerialPort setStopBits is OK.");
        }
        else{
            setNewsColor(Qt::red);
            mlaybelNews->setText("SerialPort setStopBits is Error.");
        }
    }
}

/**
 * @brief MainWindow::on_comBox_uartDps_currentIndexChanged
 * @param index
 * 主要实现自定义波特率
 */
void MainWindow::on_comBox_uartDps_currentIndexChanged(int index){

    //自定义波特率
    if(8 == index){
        QLineEdit *lineEdit = new QLineEdit(this);
        ui->comBox_uartDps->setLineEdit(lineEdit);

        lineEdit->clear();
        lineEdit->setFocus();

        //正则限制输入
        QRegExp rx("[0-9]+$");
        QRegExpValidator *validator = new QRegExpValidator(rx, this);
        lineEdit->setValidator(validator);
    }
    else{
        ui->comBox_uartDps->setEditable(false);
    }
}

void MainWindow::closeEvent(QCloseEvent *event){

    //保存用户偏好
    writeSettings();
}


void MainWindow::on_textBrowser_intput_cursorPositionChanged()
{
    ////    QTextCursor cursor =  ui->textBrowser_intput->textCursor();
    ////    cursor.movePosition(QTextCursor::End);
    ////    ui->textBrowser_intput->setTextCursor(cursor);

    ui->textBrowser_intput->moveCursor(QTextCursor::End);
}
