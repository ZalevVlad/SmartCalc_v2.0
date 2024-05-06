#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

//#include <math.h>
//#include <stdlib.h>
//#include <time.h>
#include <cmath>
#include <vector>

#include "date.h"

namespace s21{
    struct credit_pays {
        int pays_count;
        std::vector<double> pays;
        double overpayment;
        double total_payout;
    };

//typedef struct credit_pays credit_pays;

// Освободить память структуры
//    void free_credit_pays(credit_pays* credit_pays);

// Дифференцированный расчет платежей
// in:
// credit_amount - общая сумма кредита
// months - количество месяцев
// interest_rate - процентная ставка
// dt - месяц и год в который берется кредит (если dt==NULL рассматривается текущая дата)
// out:
// credit_pays - платежи
    void differentiated_credit_calc(double credit_amount, int months, double interest_rate, date* dt, credit_pays& credit_pays);

// Расчет аннуитентного платежа
// in:
// credit_amount - общая сумма кредита
// months - количество месяцев
// interest_rate - процентная ставка
// out:
// credit_pays - платежи
    void annuity_payment_calc(double credit_amount, int months, double interest_rate, credit_pays& credit_pays);

} //namespace s21

#endif  // CREDIT_CALC_H