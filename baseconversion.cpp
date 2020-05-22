#include "baseconversion.h"
#include "ui_baseconversion.h"

BaseConversion::BaseConversion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseConversion)
{
    ui->setupUi(this);
}

BaseConversion::~BaseConversion()
{
    delete ui;
}
