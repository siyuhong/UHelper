#ifndef ASCII_TABLE_H
#define ASCII_TABLE_H

#include <QWidget>

namespace Ui {
class ASCII_Table;
}

class ASCII_Table : public QWidget
{
    Q_OBJECT

public:
    explicit ASCII_Table(QWidget *parent = 0);
    ~ASCII_Table();

private slots:
    void on_lineedit_findControlASCII_textChanged(const QString &arg1);

    void on_lineEdit_findDisplayASCII_textChanged(const QString &arg1);

private:
    Ui::ASCII_Table *ui;
};

#endif // ASCII_TABLE_H
