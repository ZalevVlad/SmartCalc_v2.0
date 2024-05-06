#include "credit_calc.h"

namespace s21 {

// Освободить память структуры
// void free_credit_pays(credit_pays* credit_pays) {
//  credit_pays->pays_count = 0;
//  free(credit_pays->pays);
//}

// Дифференцированный расчет платежей
// credit amount - сумма кредита
// months - количество месяцев
// interest_rate - процентная ставка
//
// out: credit_pays - инфо по кредиту
void differentiated_credit_calc(double credit_amount, int months,
                                double interest_rate, date *dt,
                                credit_pays &credit_pays) {
  int month, year;
  if (dt) {
    month = dt->month;
    year = dt->year;
  } else {
    time_t curr_time = time(NULL);
    struct tm *tm = localtime(&curr_time);
    month = tm->tm_mon + 1;
    year = tm->tm_year + 1900;  // Отсчет времени ведется с 1900 года
  }

  credit_pays.pays.resize(months);
  credit_pays.pays_count = months;
  credit_pays.overpayment = 0;
  double interest_payment;  // Платеж по процентам
  double debt_payment = credit_amount / months;  // Платеж по основному долгу
  for (int i = 0; i < months; i++) {
    interest_payment = (credit_amount - debt_payment * i) * interest_rate /
                       100. * days_in_month(month, year) / days_in_year(year);
    credit_pays.overpayment += interest_payment;
    credit_pays.pays[i] = debt_payment + interest_payment;
    month++;
    if (month == 13) {
      year++;
      month = 1;
    }
  }
  credit_pays.total_payout = credit_amount + credit_pays.overpayment;
}

// Расчет аннуитентного платежа
void annuity_payment_calc(double credit_amount, int months,
                          double interest_rate, credit_pays &credit_pays) {
  double monthly_interest_rate = interest_rate / 12. / 100.;
  double annuite_koef =
      (monthly_interest_rate *
       std::pow(1. + monthly_interest_rate, (double)months) /
       (std::pow(1. + monthly_interest_rate, (double)months) - 1.));
  credit_pays.pays.resize(months);

  if (annuite_koef > 0) {
    credit_pays.pays_count = months;
    double monthly_payment = credit_amount * annuite_koef;
    credit_pays.total_payout = months * monthly_payment;
    credit_pays.overpayment = credit_pays.total_payout - credit_amount;
    for (int i = 0; i < months; i++) {
      credit_pays.pays[i] = monthly_payment;
    }
  }
}

}  // namespace s21
