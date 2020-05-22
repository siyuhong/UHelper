#ifndef BASECONVERSION_H
#define BASECONVERSION_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class BaseConversion;
}

class BaseConversion : public QWidget
{
    Q_OBJECT

public:
    explicit BaseConversion(QWidget *parent = 0);
    ~BaseConversion();

private slots:

    void on_lineEdit_B_editingFinished();

    void on_lineEdit_O_editingFinished();

    void on_lineEdit_D_editingFinished();

    void on_lineEdit_H_editingFinished();

private:
    Ui::BaseConversion *ui;
    void Init();
};

#endif // BASECONVERSION_H
