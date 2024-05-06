#ifndef TESTS_CREDIT_CALC_TEST_H
#define TESTS_CREDIT_CALC_TEST_H

#include <gtest/gtest.h>
#include "../../model/credit_calc.h"

#define EPS 1e-7

namespace credit_calc_test {
    s21::credit_pays cp;
    s21::date dt{20,8,2023};

    TEST(differentiated_credit_calc, 1) {
        s21::differentiated_credit_calc(1000000, 1, 15, &dt, cp);
        ASSERT_EQ(cp.pays.size(), 1);
        ASSERT_EQ(cp.pays_count, 1);
        ASSERT_NEAR(cp.pays[0], 1012739.7260273972, EPS);
        ASSERT_NEAR(cp.overpayment, 12739.726027397261, EPS);
        ASSERT_NEAR(cp.total_payout, 1012739.7260273972, EPS);
    }

    TEST(differentiated_credit_calc, 2) {
        s21::differentiated_credit_calc(1000000, 199, 15, &dt, cp);
        ASSERT_EQ(cp.pays.size(), 199);
        ASSERT_EQ(cp.pays_count, 199);
        ASSERT_NEAR(cp.pays[0], 17764.851655537965, EPS);
        ASSERT_NEAR(cp.pays[198], 5084.8504819177861, EPS);
        ASSERT_NEAR(cp.overpayment, 1250095.2832882132, EPS);
        ASSERT_NEAR(cp.total_payout, 2250095.2832882134, EPS);
    }

    TEST(differentiated_credit_calc, 3) {
        s21::differentiated_credit_calc(1000000, 199, 15, nullptr, cp);
        ASSERT_EQ(cp.pays.size(), 199);
        ASSERT_EQ(cp.pays_count, 199);
    }

    TEST(annuity_payment_calc, 1) {
        s21::annuity_payment_calc(1000000, 1, 15, cp);
        ASSERT_EQ(cp.pays.size(),1);
        ASSERT_EQ(cp.pays_count,1);
        ASSERT_NEAR(cp.pays[0],1012500,EPS);
        ASSERT_NEAR(cp.overpayment,12500,EPS);
        ASSERT_NEAR(cp.total_payout,1012500,EPS);
    }

    TEST(annuity_payment_calc, 2) {
        s21::annuity_payment_calc(1000000, 2, 15, cp);
        ASSERT_EQ(cp.pays.size(), 2);
        ASSERT_EQ(cp.pays_count, 2);
        ASSERT_NEAR(cp.pays[0], 5.0939440993788800E+05, EPS);
        ASSERT_NEAR(cp.pays[1], 5.0939440993788800E+05, EPS);
        ASSERT_NEAR(cp.overpayment, 1.8788819875776700E+04, EPS);
        ASSERT_NEAR(cp.total_payout, 1.0187888198757800E+06, EPS);
    }

    TEST(annuity_payment_calc, 3) {
        s21::annuity_payment_calc(1000000, 199, 15, cp);
        ASSERT_EQ(cp.pays.size(), 199);
        ASSERT_EQ(cp.pays_count, 199);
        ASSERT_NEAR(cp.pays[198], 1.3652383796882200E+04, EPS);
        ASSERT_NEAR(cp.overpayment, 1.7168243755795600E+06, EPS);
        ASSERT_NEAR(cp.total_payout, 2.7168243755795600E+06, EPS);
    }

} //namespace credit_calc_test


#endif //TESTS_CREDIT_CALC_TEST_H
