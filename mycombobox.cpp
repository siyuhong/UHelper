#include "mycombobox.h"

MyComboBox::MyComboBox(QWidget *parent):QComboBox(parent)
{
}

MyComboBox::~MyComboBox(){

}

void MyComboBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }

    //传递给父类处理
    QComboBox::mousePressEvent(event);
}
