#ifndef SMARTCALC2_CONTROLLER_H
#define SMARTCALC2_CONTROLLER_H

#include "../model/credit_calc.h"
#include "../model/deposit_calc.h"
#include "../model/polish.h"
#include "../model/date.h"

class Controller {
public:
    double calculate(std::string expr, double x);

    /*
    * @brief Вычислить выражение в точках <x>
    * @param expr Выражение для вычисления
    * @param x1 Начальная точка
    * @param x2 Конечная точка
    * @param pixels Количество интервалов
    * @return x Ось абсцисс
    * @return y Ось ординат
    */
    void calculate_vec(std::string expr, double x1, double x2, int pixels, std::vector<double>& x,std::vector<double>& y);

    // Дифференцированный расчет платежей
    // in:
    // credit_amount - общая сумма кредита
    // months - количество месяцев
    // interest_rate - процентная ставка
    // dt - месяц и год в который берется кредит (если dt==NULL рассматривается текущая дата)
    // out:
    // credit_pays - платежи
    void differentiated_credit_calc(double credit_amount, int months, double interest_rate, s21::date* dt, s21::credit_pays& credit_pays);


    // Расчет аннуитентного платежа
    // in:
    // credit_amount - общая сумма кредита
    // months - количество месяцев
    // interest_rate - процентная ставка
    // out:
    // credit_pays - платежи
    void annuity_payment_calc(double credit_amount, int months, double interest_rate, s21::credit_pays& credit_pays);

    // Калькулятор депозита
    // in:_______________________
    // start_dt - начало срока
    // deposit_amount - сумма вклада
    // period - срок размещения (измеряется в period_type)
    // period_type - единица измерения срока размещения (дни/месяца/года)
    // interest_rate - процентная ставка
    // tax_rate - ключевая ставка
    // payments_periodicity - периодичность выплат
    // payments_periodicity_type - 0/1/2 (дни/месяцы/года)
    // interest_capitalization - капитализация процентов: 0/1 (нет/да)
    // deposits - список пополнений
    // withdrawals - список снятий
    // out:______________________
    // deposit - начисленные проценты, сумма налога, сумма на вкладе к концу срока
        int deposit_calc(s21::date start_dt, double deposit_amount, int period, int period_type, double interest_rate, double tax_rate, int payments_periodicity,
                         int payments_periodicity_type, int interest_capitalization, std::list<s21::pay> &deposits, std::list<s21::pay> &withdrawals,
                         s21::deposit& deposit);


};


#endif //SMARTCALC2_CONTROLLER_H
