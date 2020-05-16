#include "ascii_table.h"
#include "ui_ascii_table.h"

ASCII_Table::ASCII_Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ASCII_Table)
{
    ui->setupUi(this);

}

ASCII_Table::~ASCII_Table()
{
    delete ui;
}

void ASCII_Table::on_lineedit_findControlASCII_textChanged(const QString &arg1)
{
    int row = ui->tab_controlASCII->rowCount();

    //全显
    if( arg1 == ""){
        for(int i = 0; i < row ;i++){
            ui->tab_controlASCII->setRowHidden(i,false);
        }
    }else{

        QList<QTableWidgetItem *> item = ui->tab_controlASCII->findItems(arg1,Qt::MatchContains);

        //全隐
        for(int i = 0; i < row; i++){
            ui->tab_controlASCII->setRowHidden(i,true);
        }

        //匹配则显
        if(!item.isEmpty()){
            for(int i = 0; i < item.count(); i++){
                ui->tab_controlASCII->setRowHidden(item.at(i)->row(),false);
            }
        }
    }
}

void ASCII_Table::on_lineEdit_findDisplayASCII_textChanged(const QString &arg1)
{

    int row = ui->tab_displayASCII->rowCount();

    //全显
    if( arg1 == ""){
        for(int i = 0; i < row ;i++){
            ui->tab_displayASCII->setRowHidden(i,false);
        }
    }else{

        QList<QTableWidgetItem *> item = ui->tab_displayASCII->findItems(arg1,Qt::MatchContains);

        //全隐
        for(int i = 0; i < row; i++){
            ui->tab_displayASCII->setRowHidden(i,true);
        }

        //匹配则显
        if(!item.isEmpty()){
            for(int i = 0; i < item.count(); i++){
                ui->tab_displayASCII->setRowHidden(item.at(i)->row(),false);
            }
        }
    }

}
