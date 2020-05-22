#ifndef BASECONVERSION_H
#define BASECONVERSION_H

#include <QWidget>

namespace Ui {
class BaseConversion;
}

class BaseConversion : public QWidget
{
    Q_OBJECT

public:
    explicit BaseConversion(QWidget *parent = 0);
    ~BaseConversion();

private:
    Ui::BaseConversion *ui;
};

#endif // BASECONVERSION_H
