#ifndef WITHDRAWALS_INPUT_H
#define WITHDRAWALS_INPUT_H

#include <QDialog>
#include <QMessageBox>

#include "../../model/deposit_calc.h"

namespace Ui {
class withdrawals_input;
}

class withdrawals_input : public QDialog
{
    Q_OBJECT

public:
    explicit withdrawals_input(QWidget *parent = nullptr);
    ~withdrawals_input();

private slots:

    void on_pushButton_add_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_save_clicked();

signals:
    void send_paylist(std::list<s21::pay>& pays);

private:
    Ui::withdrawals_input *ui;
};

#endif // WITHDRAWALS_INPUT_H
