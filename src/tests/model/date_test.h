#ifndef SMARTCALC2_DATE_TEST_H
#define SMARTCALC2_DATE_TEST_H

#include <gtest/gtest.h>
#include "../../model/date.h"

namespace date_test {

    TEST(date_test, 0) {
        s21::date dt = {30,9,2023},res={1,10,2023};
        dt = s21::add_days(dt,1);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 1) {
        s21::date dt = {30,9,2023},res={1,10,2023};
        dt = s21::add_days(dt,1);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 2) {
        s21::date dt = {31,12,2023}, res = {1,1,2024};
        dt = s21::add_days(dt, 1);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 3) {
        s21::date dt = {19, 8, 2023}, res = {20,8,2023};
        dt = s21::add_days(dt, 1);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 4) {
        s21::date dt = {19, 8, 2023}, res = {21,8,2023};
        dt = s21::add_days(dt, 2);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 5) {
        s21::date dt = {19, 8, 2023}, res = {22,8,2023};
        dt = s21::add_days(dt, 3);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 6) {
        s21::date dt = {19, 8, 2023}, res = {26,8,2023};
        dt = s21::add_days(dt, 7);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 7) {
        s21::date dt = {19, 8, 2023}, res = {1,9,2023};
        dt = s21::add_days(dt, 13);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 8) {
        s21::date dt = {19, 8, 2023}, res = {2,9,2023};
        dt = s21::add_days(dt, 14);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 9) {
        s21::date dt = {19, 8, 2023}, res = {19,9,2023};
        dt = s21::add_days(dt, 31);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 10) {
        s21::date dt = {19, 8, 2023}, res = {20,10,2023};
        dt = s21::add_days(dt, 62);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 11) {
        s21::date dt = {19, 8, 2023}, res = {18,8,2024};
        dt = s21::add_days(dt, 365);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 12) {
        s21::date dt = {19, 8, 2023}, res = {19,2,2036};
        dt = s21::add_days(dt, 4567);
        ASSERT_TRUE(dt==res);
    }

    TEST(date_test, 13) {
        s21::date dt = s21::get_date();
        ASSERT_TRUE(s21::date_is_correct(dt));
    }

    TEST(date_test, 14) {
        s21::date dt1 = s21::get_date();
        s21::date dt2 = add_days(dt1,1);
        ASSERT_TRUE(s21::date_le(dt1,dt2));
    }

    TEST(date_test, 15) {
        s21::date dt1 = s21::get_date();
        s21::date dt2 = add_days(dt1,1000);
        ASSERT_TRUE(s21::date_diff(dt1,dt2) == 1000);
    }

    TEST(date_test, 16) {
        s21::date dt1 = s21::get_date();
        s21::date dt2 = add_days(dt1,1);
        ASSERT_TRUE(s21::date_gt(dt2,dt1));
    }



} //namespace date_test

#endif //SMARTCALC2_DATE_TEST_H
