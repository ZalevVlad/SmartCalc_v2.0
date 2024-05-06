#include "deposit_calc.h"

#include <vector>

namespace s21 {

int deposit_calc_years(date start_dt, double deposit_amount, date end_dt,
                       double interest_rate, double tax_rate,
                       int payments_periodicity, int interest_capitalization,
                       std::list<pay> &deposits, std::list<pay> &withdrawals,
                       deposit &deposit) {
  date curr_dt = start_dt;
  deposit.final_amount = deposit_amount;
  deposit.tax_amount = 0;
  deposit.accrued_interest = 0;

  double s0 = 1e6 * tax_rate / 100.;  // Сумма необлагаемая доходом
  double s1;  //Сумма облагаемая доходом
  double s2 = 0;  // Сумма, по которой налог уже уплачен
  int tax_year = curr_dt.year;  // Текущий налоговый год
  double accrued_interest;

  auto deposits_it = deposits.begin();
  auto withdrawals_it = withdrawals.begin();

  date prev_dt = curr_dt;
  curr_dt.year += payments_periodicity;
  while (date_lt(curr_dt, end_dt) && deposit.final_amount) {
    if (tax_year < curr_dt.year) {
      s1 = deposit.accrued_interest - s2 - s0;
      s2 = deposit.accrued_interest;
      if (s1 > 0) {
        deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
      }
      tax_year = curr_dt.year;
    }

    while (deposits_it != deposits.end() && date_lt(deposits_it->dt, curr_dt)) {
      deposit.final_amount += deposits_it->amount;
      deposits_it++;
    }
    while (withdrawals_it != withdrawals.end() &&
           date_lt(withdrawals_it->dt, curr_dt)) {
      deposit.final_amount -= withdrawals_it->amount;
      if (deposit.final_amount < 0) {
        deposit.final_amount = 0;
      }
      withdrawals_it++;
    }

    accrued_interest = deposit.final_amount * interest_rate / 100. / 365. *
                       date_diff(curr_dt, prev_dt);
    deposit.accrued_interest += accrued_interest;
    if (interest_capitalization) {
      deposit.final_amount += accrued_interest;
    }

    prev_dt = curr_dt;
    curr_dt.year += payments_periodicity;
  }
  // Если с прошлого платежа изменился год считаем налог
  if (tax_year < curr_dt.year) {
    s1 = deposit.accrued_interest - s2 - s0;
    s2 = deposit.accrued_interest;
    if (s1 > 0) {
      deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
    }
    tax_year = curr_dt.year;
  }
  // Производим оставшиеся пополнения и снятия, кроме последней даты
  while (deposits_it != deposits.end() && date_lt(deposits_it->dt, end_dt)) {
    deposit.final_amount += deposits_it->amount;
    deposits_it++;
  }
  while (withdrawals_it != withdrawals.end() &&
         date_lt(withdrawals_it->dt, end_dt)) {
    deposit.final_amount -= withdrawals_it->amount;
    if (deposit.final_amount < 0) {
      deposit.final_amount = 0;
    }
    withdrawals_it++;
  }
  // Начисляем проценты на последний период
  accrued_interest = deposit.final_amount * interest_rate / 100. / 365. *
                     (date_diff(end_dt, prev_dt));
  deposit.accrued_interest += accrued_interest;
  if (interest_capitalization) {
    deposit.final_amount += accrued_interest;
  }
  // После того как последний процент начислен производим пополнения и снятия в
  // последний день
  while (deposits_it != deposits.end() && date_eq(deposits_it->dt, end_dt)) {
    deposit.final_amount += deposits_it->amount;
    deposits_it++;
  }
  while (withdrawals_it != withdrawals.end() &&
         date_eq(withdrawals_it->dt, end_dt)) {
    deposit.final_amount -= withdrawals_it->amount;
    if (deposit.final_amount < 0) {
      deposit.final_amount = 0;
    }
    withdrawals_it++;
  }
  //  Считаем налог в этом году
  s1 = deposit.accrued_interest - s2 - s0;
  s2 = deposit.accrued_interest;
  if (s1 > 0) {
    deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
  }
  tax_year = curr_dt.year;

  return 0;
}

int deposit_calc_months(date start_dt, double deposit_amount, date end_dt,
                        double interest_rate, double tax_rate,
                        int payments_periodicity, int interest_capitalization,
                        std::list<pay> &deposits, std::list<pay> &withdrawals,
                        deposit &deposit) {
  date curr_dt = start_dt;
  deposit.final_amount = deposit_amount;
  deposit.tax_amount = 0;
  deposit.accrued_interest = 0;

  double s0 = 1e6 * tax_rate / 100.;  // Сумма необлагаемая доходом
  double s1;  //Сумма облагаемая доходом
  double s2 = 0;  // Сумма, по которой налог уже уплачен
  int tax_year = curr_dt.year;  // Текущий налоговый год
  double accured_interest;

  auto deposits_it = deposits.begin();
  auto withdrawals_it = withdrawals.begin();

  date prev_dt = curr_dt;
  curr_dt = add_months(curr_dt, payments_periodicity);
  while (date_lt(curr_dt, end_dt) && deposit.final_amount) {
    if (tax_year < curr_dt.year) {
      s1 = deposit.accrued_interest - s2 - s0;
      s2 = deposit.accrued_interest;
      if (s1 > 0) {
        deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
      }
      tax_year = curr_dt.year;
    }

    while (deposits_it != deposits.end() && date_lt(deposits_it->dt, curr_dt)) {
      deposit.final_amount += deposits_it->amount;
      deposits_it++;
    }
    while (withdrawals_it != withdrawals.end() &&
           date_lt(withdrawals_it->dt, curr_dt)) {
      deposit.final_amount -= withdrawals_it->amount;
      if (deposit.final_amount < 0) {
        deposit.final_amount = 0;
      }
      withdrawals_it++;
    }

    accured_interest = deposit.final_amount * interest_rate / 100. / 365. *
                       date_diff(curr_dt, prev_dt);
    deposit.accrued_interest += accured_interest;
    if (interest_capitalization) {
      deposit.final_amount += accured_interest;
    }

    prev_dt = curr_dt;
    curr_dt = add_months(curr_dt, payments_periodicity);
  }
  // Если с прошлого платежа изменился год считаем налог
  if (tax_year < curr_dt.year) {
    s1 = deposit.accrued_interest - s2 - s0;
    s2 = deposit.accrued_interest;
    if (s1 > 0) {
      deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
    }
    tax_year = curr_dt.year;
  }
  // Производим оставшиеся пополнения и снятия, кроме последней даты
  while (deposits_it != deposits.end() && date_lt(deposits_it->dt, end_dt)) {
    deposit.final_amount += deposits_it->amount;
    deposits_it++;
  }
  while (withdrawals_it != withdrawals.end() &&
         date_lt(withdrawals_it->dt, end_dt)) {
    deposit.final_amount -= withdrawals_it->amount;
    if (deposit.final_amount < 0) {
      deposit.final_amount = 0;
    }
    withdrawals_it++;
  }
  // Начисляем проценты на последний период
  accured_interest = deposit.final_amount * interest_rate / 100. / 365. *
                     date_diff(end_dt, prev_dt);
  deposit.accrued_interest += accured_interest;
  if (interest_capitalization) {
    deposit.final_amount += accured_interest;
  }
  // После того как последний процент начислен производим пополнения и снятия в
  // последний день
  while (deposits_it != deposits.end() && date_eq(deposits_it->dt, end_dt)) {
    deposit.final_amount += deposits_it->amount;
    deposits_it++;
  }
  while (withdrawals_it != withdrawals.end() &&
         date_eq(withdrawals_it->dt, end_dt)) {
    deposit.final_amount -= withdrawals_it->amount;
    if (deposit.final_amount < 0) {
      deposit.final_amount = 0;
    }
    withdrawals_it++;
  }
  //  Считаем налог в этом году
  s1 = deposit.accrued_interest - s2 - s0;
  s2 = deposit.accrued_interest;
  if (s1 > 0) {
    deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
  }
  tax_year = curr_dt.year;

  return 0;
}

int deposit_calc_days(date start_dt, double deposit_amount, date end_dt,
                      double interest_rate, double tax_rate,
                      int payments_periodicity, int interest_capitalization,
                      std::list<pay> &deposits, std::list<pay> &withdrawals,
                      deposit &deposit) {
  date curr_dt = start_dt;
  deposit.final_amount = deposit_amount;
  deposit.tax_amount = 0;
  deposit.accrued_interest = 0;

  double s0 = 1e6 * tax_rate / 100.;  // Сумма необлагаемая доходом
  double s1;  //Сумма облагаемая доходом
  double s2 = 0;  // Сумма, по которой налог уже уплачен
  int tax_year = curr_dt.year;  // Текущий налоговый год
  double accrued_interest;
  curr_dt = add_days(curr_dt, payments_periodicity);

  auto deposits_it = deposits.begin();
  auto withdrawals_it = withdrawals.begin();

  while (date_lt(curr_dt, end_dt) && deposit.final_amount) {
    if (tax_year < curr_dt.year) {
      s1 = deposit.accrued_interest - s2 - s0;
      s2 = deposit.accrued_interest;
      if (s1 > 0) {
        deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
      }
      tax_year = curr_dt.year;
    }

    while (deposits_it != deposits.end() && date_lt(deposits_it->dt, curr_dt)) {
      deposit.final_amount += deposits_it->amount;
      deposits_it++;
    }
    while (withdrawals_it != withdrawals.end() &&
           date_lt(withdrawals_it->dt, curr_dt)) {
      deposit.final_amount -= withdrawals_it->amount;
      if (deposit.final_amount < 0) {
        deposit.final_amount = 0;
      }
      withdrawals_it++;
    }

    accrued_interest = deposit.final_amount * interest_rate / 100. / 365. *
                       payments_periodicity;
    deposit.accrued_interest += accrued_interest;
    if (interest_capitalization) {
      deposit.final_amount += accrued_interest;
    }

    curr_dt = add_days(curr_dt, payments_periodicity);
  }
  // Если с прошлого платежа изменился год считаем налог
  if (tax_year < curr_dt.year) {
    s1 = deposit.accrued_interest - s2 - s0;
    s2 = deposit.accrued_interest;
    if (s1 > 0) {
      deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
    }
    tax_year = curr_dt.year;
  }
  // Производим оставшиеся пополнения и снятия, кроме последней даты
  while (deposits_it != deposits.end() && date_lt(deposits_it->dt, end_dt)) {
    deposit.final_amount += deposits_it->amount;
    deposits_it++;
  }
  while (withdrawals_it != withdrawals.end() &&
         date_lt(withdrawals_it->dt, end_dt)) {
    deposit.final_amount -= withdrawals_it->amount;
    if (deposit.final_amount < 0) {
      deposit.final_amount = 0;
    }
    withdrawals_it++;
  }
  // Начисляем проценты на последний период
  accrued_interest = deposit.final_amount * interest_rate / 100. / 365. *
                     (payments_periodicity - date_diff(curr_dt, end_dt));
  deposit.accrued_interest += accrued_interest;
  if (interest_capitalization) {
    deposit.final_amount += accrued_interest;
  }
  // После того как последний процент начислен производим пополнения и снятия в
  // последний день
  while (deposits_it != deposits.end() && date_eq(deposits_it->dt, end_dt)) {
    deposit.final_amount += deposits_it->amount;
    deposits_it++;
  }
  while (withdrawals_it != withdrawals.end() &&
         date_eq(withdrawals_it->dt, end_dt)) {
    deposit.final_amount -= withdrawals_it->amount;
    if (deposit.final_amount < 0) {
      deposit.final_amount = 0;
    }
    withdrawals_it++;
  }
  //  Считаем налог в этом году
  s1 = deposit.accrued_interest - s2 - s0;
  s2 = deposit.accrued_interest;
  if (s1 > 0) {
    deposit.tax_amount += s1 * 13. / 100.;  // Прибавляем размер НДФЛ
  }
  tax_year = curr_dt.year;

  return 0;
}

int deposit_calc(date start_dt, double deposit_amount, int period,
                 int period_type, double interest_rate, double tax_rate,
                 int payments_periodicity, int payments_periodicity_type,
                 int interest_capitalization, std::list<pay> &deposits,
                 std::list<pay> &withdrawals, deposit &deposit) {
  date end_dt = start_dt;
  switch (period_type) {
    case DAYS:
      end_dt = add_days(start_dt, period);
      break;
    case MONTHS:
      end_dt = add_months(start_dt, period);
      break;
    case YEARS:
      end_dt.year += period;
  }

  // Сортировка пополнений и выводов в порядке возрастания дат
  deposits.sort();
  withdrawals.sort();

  // Перейдем к пополнениям и выводам средств, которые попали в срок открытия
  // вклада

  while (deposits.size() > 0 && date_lt(deposits.front().dt, start_dt)) {
    deposits.pop_front();
  }

  while (withdrawals.size() > 0 && date_lt(withdrawals.front().dt, start_dt)) {
    withdrawals.pop_front();
  }

  if (payments_periodicity_type == DAYS) {
    deposit_calc_days(start_dt, deposit_amount, end_dt, interest_rate, tax_rate,
                      payments_periodicity, interest_capitalization, deposits,
                      withdrawals, deposit);
  } else if (payments_periodicity_type == MONTHS) {
    deposit_calc_months(start_dt, deposit_amount, end_dt, interest_rate,
                        tax_rate, payments_periodicity, interest_capitalization,
                        deposits, withdrawals, deposit);
  } else if (payments_periodicity_type == YEARS) {
    deposit_calc_years(start_dt, deposit_amount, end_dt, interest_rate,
                       tax_rate, payments_periodicity, interest_capitalization,
                       deposits, withdrawals, deposit);
  }
  return 0;
}

}  // namespace s21