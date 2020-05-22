#include "baseconversion.h"
#include "ui_baseconversion.h"

BaseConversion::BaseConversion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseConversion)
{
    ui->setupUi(this);

    Init();
}

BaseConversion::~BaseConversion()
{
    delete ui;
}

void BaseConversion::Init(){

    QRegExp regBinary("[0-1]*");
    QValidator *mB_validator = new QRegExpValidator(regBinary,this);
    ui->lineEdit_B->setValidator(mB_validator);

    QRegExp regOctal("[0-7]*");
    QValidator *mO_validator = new QRegExpValidator(regOctal,this);
    ui->lineEdit_O->setValidator(mO_validator);

    QRegExp regDecimal("[0-9]*");
    QValidator *mD_validator = new QRegExpValidator(regDecimal,this);
    ui->lineEdit_D->setValidator(mD_validator);

    QRegExp regHex("[a-fA-F0-9]*");
    QValidator *mH_validator = new QRegExpValidator(regHex,this);
    ui->lineEdit_H->setValidator(mH_validator);

}

void BaseConversion::on_lineEdit_B_editingFinished()
{
    int number = 0;
    QByteArray qarray_number = ui->lineEdit_B->text().toLatin1();
    int len = qarray_number.length();

    //BtoD
    for(int i = 0; i < len; i++){
        if('1' == qarray_number.at(i)){
            number += (1 << (len -i -1));
        }
    }

    ui->lineEdit_O->setText(QString(QByteArray::number(number,8)));
    ui->lineEdit_D->setText(QString(QByteArray::number(number)));
    ui->lineEdit_H->setText(QString(QByteArray::number(number,16).toUpper()));
}

void BaseConversion::on_lineEdit_O_editingFinished()
{
    QString qarray_number = ui->lineEdit_O->text();

    //OtoD
    bool ok;
    int number = qarray_number.toInt(&ok,8);

    ui->lineEdit_B->setText(QString(QByteArray::number(number,2)));
    ui->lineEdit_D->setText(QString(QByteArray::number(number)));
    ui->lineEdit_H->setText(QString(QByteArray::number(number,16).toUpper()));
}

void BaseConversion::on_lineEdit_D_editingFinished()
{
    int number = ui->lineEdit_D->text().toInt();

    ui->lineEdit_B->setText(QString(QByteArray::number(number,2)));
    ui->lineEdit_O->setText(QString(QByteArray::number(number,8)));
    ui->lineEdit_H->setText(QString(QByteArray::number(number,16).toUpper()));
}


void BaseConversion::on_lineEdit_H_editingFinished()
{
    QString qarray_number = ui->lineEdit_H->text();

    //HtoD
    bool ok;
    int number = qarray_number.toInt(&ok,16);

    ui->lineEdit_B->setText(QString(QByteArray::number(number,2)));
    ui->lineEdit_O->setText(QString(QByteArray::number(number,8)));
    ui->lineEdit_D->setText(QString(QByteArray::number(number)));

}
