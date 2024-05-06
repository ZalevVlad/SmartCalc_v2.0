#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QVector>

#include "deposit_input.h"
#include "withdrawals_input.h"

#include "../../model/polish.h"
#include "../../model/credit_calc.h"
#include "../../model/deposit_calc.h"

#include "../../control/controller.h"



#include <iostream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_expand_clicked();

    void on_pushButton_equal_clicked();

    void on_actionGraphic_triggered();

    void on_actionBase_triggered();

    void on_actionCredit_triggered();

    void on_actionDeposit_triggered();

    void on_pushButton_plot_clicked();

    void on_buttonGroup_clicked(QAbstractButton* btn);

    void on_pushButton_delete_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void recieve_deposits(std::list<s21::pay>& deposits);
    void recieve_withdrawals(std::list<s21::pay>& withdrawals);

    void on_pushButton_calc_deposit_clicked();

    void on_pushButton_calc_credit_clicked();

private:
    bool get_limits();
    std::list<s21::pay> deposits_list;
    std::list<s21::pay> withdrawals_list;

private:
    Ui::MainWindow *ui;
    deposit_input deposit_input_ui;
    withdrawals_input withdrawals_input_ui;
    Controller controller;
};
#endif // MAINWINDOW_H
