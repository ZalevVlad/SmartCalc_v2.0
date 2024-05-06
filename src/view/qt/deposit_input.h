#ifndef DEPOSIT_INPUT_H
#define DEPOSIT_INPUT_H

#include <QDialog>
#include <QMessageBox>

#include "../../model/deposit_calc.h"

namespace Ui {
class deposit_input;
}

class deposit_input : public QDialog
{
    Q_OBJECT

public:
    explicit deposit_input(QWidget *parent = nullptr);
    ~deposit_input();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_add_clicked();

signals:
    void send_paylist(std::list<s21::pay>& pays);

private:
    Ui::deposit_input *ui;
};

#endif // DEPOSIT_INPUT_H
