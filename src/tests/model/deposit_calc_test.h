#ifndef SMARTCALC2_DEPOSIT_CALC_TEST_H
#define SMARTCALC2_DEPOSIT_CALC_TEST_H

#include <gtest/gtest.h>
#include "../../model/deposit_calc.h"


namespace deposit_calc_test {

    TEST(deposit_calc_test, 0) {
        s21::date start_dt = {23,9,2023};
        double deposit_amount = 1000000;
        int period = 5;
        int period_type = s21::YEARS;
        double interest_rate = 15;
        double tax_rate = 12;
        int payments_periodicity = 1;
        int payments_periodicity_type = s21::DAYS;
        int interest_capitalization = 0;

        std::list<s21::pay> deposits = {{27,9,2023,1000000},
                                        {25,11,2023,1000000},
                                        {29,10,2023,1000000},
                                        {24,9,2023,1000000},
                                        {23,9,2028,1000000}};
        std::list<s21::pay> withdrawals = {{27,9,2023,100000},
                                           {25,11,2023,100000},
                                           {29,10,2023,100000},
                                           {24,9,2023,100000},
                                           {23,9,2028,100000}};

        s21::deposit deposit;
        deposit_calc(start_dt, deposit_amount, period, period_type, interest_rate, tax_rate, payments_periodicity,
                     payments_periodicity_type, interest_capitalization, deposits, withdrawals,
                     deposit);
    }

    TEST(deposit_calc_test, 1) {
        s21::date start_dt = {23,9,2023};
        double deposit_amount = 1000000;
        int period = 48;
        int period_type = s21::MONTHS;
        double interest_rate = 15;
        double tax_rate = 12;
        int payments_periodicity = 1;
        int payments_periodicity_type = s21::MONTHS;
        int interest_capitalization = 0;

        std::list<s21::pay> deposits = {{27,9,2023,1000000},
                                      {25,11,2023,1000000},
                                      {29,10,2023,1000000},
                                      {24,9,2023,1000000},
                                      {23,9,2027,1000000}};

        std::list<s21::pay> withdrawals = {{27,9,2023,100000},
                                         {25,11,2023,100000},
                                         {29,10,2023,100000},
                                         {24,9,2023,100000},
                                         {23,9,2027,100000}};

        s21::deposit deposit;
        deposit_calc(start_dt, deposit_amount, period, period_type, interest_rate, tax_rate, payments_periodicity,
                     payments_periodicity_type, interest_capitalization, deposits, withdrawals,
                     deposit);
    }

    TEST(deposit_calc_test, 2) {
        s21::date start_dt = {23,9,2023};
        double deposit_amount = 1000000;
        int period = 1000;
        int period_type = s21::DAYS;
        double interest_rate = 15;
        double tax_rate = 12;
        int payments_periodicity = 1;
        int payments_periodicity_type = s21::YEARS;
        int interest_capitalization = 0;

        std::list<s21::pay> deposits = {{27,9,2023,1000000},
                                       {25,11,2023,1000000},
                                       {29,10,2023,1000000},
                                       {24,9,2023,1000000},
                                       {19,6,2026,1000000}};

        std::list<s21::pay> withdrawals = {{27,9,2023,100000},
                                          {25,11,2023,100000},
                                          {29,10,2023,100000},
                                          {24,9,2023,100000},
                                          {19,6,2026,100000}};

        s21::deposit deposit;
        deposit_calc(start_dt, deposit_amount, period, period_type, interest_rate, tax_rate, payments_periodicity,
                     payments_periodicity_type, interest_capitalization, deposits, withdrawals,
                     deposit);
    }

    TEST(deposit_calc_test, 3) {
        s21::date start_dt = {23,9,2023};
        double deposit_amount = 1000000;
        int period = 366;
        int period_type = s21::DAYS;
        double interest_rate = 15;
        double tax_rate = 12;
        int payments_periodicity = 1;
        int payments_periodicity_type = s21::DAYS;
        int interest_capitalization = 0;

        std::list<s21::pay> deposits = {{22,9,2024,1000000},
                                        {23,9,2024,1000000}};

        std::list<s21::pay> withdrawals = {{22,9,2024,1000000},
                                           {23,9,2024,100000}};

        s21::deposit deposit;
        deposit_calc(start_dt, deposit_amount, period, period_type, interest_rate, tax_rate, payments_periodicity,
                     payments_periodicity_type, interest_capitalization, deposits, withdrawals,
                     deposit);
    }

    TEST(deposit_calc_test, 4) {
        s21::date start_dt = {23,9,2023};
        double deposit_amount = 1000000;
        int period = 366;
        int period_type = s21::DAYS;
        double interest_rate = 15;
        double tax_rate = 12;
        int payments_periodicity = 1;
        int payments_periodicity_type = s21::MONTHS;
        int interest_capitalization = 0;

        std::list<s21::pay> deposits = {{22,9,2024,1000000},
                                        {23,9,2024,1000000}};

        std::list<s21::pay> withdrawals = {{22,9,2024,1000000},
                                           {23,9,2024,100000}};

        s21::deposit deposit;
        deposit_calc(start_dt, deposit_amount, period, period_type, interest_rate, tax_rate, payments_periodicity,
                     payments_periodicity_type, interest_capitalization, deposits, withdrawals,
                     deposit);
    }

    TEST(deposit_calc_test, 5) {
        s21::date start_dt = {23,9,2023};
        double deposit_amount = 1000000;
        int period = 366;
        int period_type = s21::DAYS;
        double interest_rate = 15;
        double tax_rate = 12;
        int payments_periodicity = 1;
        int payments_periodicity_type = s21::YEARS;
        int interest_capitalization = 0;

        std::list<s21::pay> deposits = {{22,9,2024,1000000},
                                        {23,9,2024,1000000}};

        std::list<s21::pay> withdrawals = {{22,9,2024,1000000},
                                           {23,9,2024,100000}};

        s21::deposit deposit;
        deposit_calc(start_dt, deposit_amount, period, period_type, interest_rate, tax_rate, payments_periodicity,
                     payments_periodicity_type, interest_capitalization, deposits, withdrawals,
                     deposit);
    }

} //namespace deposit_calc_test

#endif //SMARTCALC2_DEPOSIT_CALC_TEST_H
