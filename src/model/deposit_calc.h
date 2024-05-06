#ifndef DEPOSIT_CALC_H_
#define DEPOSIT_CALC_H_

#include <list>
#include <vector>

#include "date.h"
//#include "pays_list.h"

// #define TAX_RATE 12.

namespace s21{

    struct pay{
        date dt;
        double amount;

        bool operator<(const pay& other) const {
            return this->dt < other.dt;
        }
    };

    struct deposit {
        double accrued_interest;
        double tax_amount;
        double final_amount;
    };

    enum period_type {
        DAYS,
        MONTHS,
        YEARS,
        ONCE
    };

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
    int deposit_calc(date start_dt, double deposit_amount, int period, int period_type, double interest_rate, double tax_rate, int payments_periodicity,
                     int payments_periodicity_type, int interest_capitalization, std::list<pay> &deposits, std::list<pay> &withdrawals,
                     deposit& deposit);


} //namespace s21

#endif  // DEPOSIT_CALC_H_
