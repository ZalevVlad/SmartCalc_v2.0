#ifndef SMARTCALC2_POLISH_CTR_TEST_H
#define SMARTCALC2_POLISH_CTR_TEST_H

#include <gtest/gtest.h>
#include "../../../model/polish.h"

#define EPS 1e-7

namespace polish_test {

    TEST(polish_ctr, 0) {
        try{
            s21::polish polish("");
            ASSERT_EQ(polish.getPolish(),"");
        }
        catch (std::exception& e){
            FAIL() << "Unexpected error" << e.what();
        }
    }

    TEST(polish_ctr, 1) {
        try {
            s21::polish polish("123");
            ASSERT_EQ(polish.getPolish(),"123 ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 2) {
        try {
            s21::polish polish("+2");
            ASSERT_EQ(polish.getPolish(),"2 p ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 3) {
        try {
            s21::polish polish("-2");
            ASSERT_EQ(polish.getPolish(),"2 ~ ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 4) {
        try {
            s21::polish polish("2+2");
            ASSERT_EQ(polish.getPolish(),"2 2 + ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 5) {
        try {
            s21::polish polish("2-2");
            ASSERT_EQ(polish.getPolish(),"2 2 - ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 6) {
        try {
            s21::polish polish("2*2");
            ASSERT_EQ(polish.getPolish(),"2 2 * ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 7) {
        try {
            s21::polish polish("2/2");
            ASSERT_EQ(polish.getPolish(),"2 2 / ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 8) {
        try {
            s21::polish polish("2%2");
            ASSERT_EQ(polish.getPolish(),"2 2 % ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 9) {
        try {
            s21::polish polish("2^2");
            ASSERT_EQ(polish.getPolish(),"2 2 ^ ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 10) {
        try {
            s21::polish polish("sin(2)");
            ASSERT_EQ(polish.getPolish(),"2 s ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 11) {
        try {
            s21::polish polish("cos(2)");
            ASSERT_EQ(polish.getPolish(),"2 c ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 12) {
        try {
            s21::polish polish("tan(2)");
            ASSERT_EQ(polish.getPolish(),"2 t ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 13) {
        try {
            s21::polish polish("acos(0.5)");
            ASSERT_EQ(polish.getPolish(),"0.5 C ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 14) {
        try {
            s21::polish polish("asin(0.5)");
            ASSERT_EQ(polish.getPolish(),"0.5 S ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 15) {
        try {
            s21::polish polish("atan(0.5)");
            ASSERT_EQ(polish.getPolish(),"0.5 T ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 16) {
        try {
            s21::polish polish("sqrt(0.5)");
            ASSERT_EQ(polish.getPolish(),"0.5 q ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 17) {
        try {
            s21::polish polish("ln(0.5)");
            ASSERT_EQ(polish.getPolish(),"0.5 l ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 18) {
        try {
            s21::polish polish("log(0.5)");
            ASSERT_EQ(polish.getPolish(),"0.5 L ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 19) {
        try {
            s21::polish polish("2+2+2*2*2");
            ASSERT_EQ(polish.getPolish(),"2 2 + 2 2 * 2 * + ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 20) {
        try {
            s21::polish polish("(121e+3)");
            ASSERT_EQ(polish.getPolish(),"121000 ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 21) {
        try {
            s21::polish polish("(((((((12)))))))");
            ASSERT_EQ(polish.getPolish(),"12 ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 22) {
        try {
            s21::polish polish("(((((11)))))+((((12))))");
            ASSERT_EQ(polish.getPolish(),"11 12 + ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 23) {
        try {
            s21::polish polish("(((11)+(12))+13)");
            ASSERT_EQ(polish.getPolish(),"11 12 + 13 + ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 24) {
        try {
            s21::polish polish("sin(2)+cos(2)+tan(2)+asin(2)+acos(2)+atan(2)+sqrt(2)+ln(2)+log(2)");
            ASSERT_EQ(polish.getPolish(),"2 s 2 c + 2 t + 2 S + 2 C + 2 T + 2 q + 2 l + 2 L + ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 25) {
        try {
            s21::polish polish("sin(2)+cos(2)-tan(2)/asin(0.5)*acos(0.5)*atan(0.5)^sqrt(2)+ln(2)/log(2)");
            ASSERT_EQ(polish.getPolish(),"2 s 2 c + 2 t 0.5 S / 0.5 C * 0.5 T 2 q ^ * - 2 l 2 L / + ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 26) {
        try {
            s21::polish polish("()()()");
            ASSERT_EQ(polish.getPolish(),"");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 27) {
        try {
            s21::polish polish("(()((()()(()()((((()(()((()())))(((()())))))))))))");
            ASSERT_EQ(polish.getPolish(),"");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 28) {
        try {
            s21::polish polish("(()((()()(()()((((()(()((()())))(((()(2))))))))))))");
            ASSERT_EQ(polish.getPolish(),"2 ");
        } catch (std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 29) {
        try{
            s21::polish polish(")");
            FAIL() << "Expected runtime_error";
        }
        catch (std::runtime_error& e){
            SUCCEED();
        }
        catch (std::exception& e){
            FAIL() << "Unexpected error" << e.what();
        }
    }

    TEST(polish_ctr, 30) {
        try{
            s21::polish polish("(");
            FAIL() << "Expected runtime_error";
        }
        catch (std::runtime_error& e){
            SUCCEED();
        }
        catch (std::exception& e){
            FAIL() << "Unexpected error" << e.what();
        }
    }

    TEST(polish_ctr, 31) {
        try{
            s21::polish polish("(()((()()(()()(((()(()((()())))(((()())))))))))))");
            FAIL() << "Expected runtime_error";
        }
        catch (std::runtime_error& e){
            SUCCEED();
        }
        catch (std::exception& e){
            FAIL() << "Unexpected error" << e.what();
        }
    }

    TEST(polish_ctr, 32) {
        try{
            s21::polish polish("sin");
            FAIL() << "Expected runtime_error";
        }
        catch (std::runtime_error& e){
            SUCCEED();
        }
        catch (std::exception& e){
            FAIL() << "Unexpected error" << e.what();
        }
    }

    TEST(polish_ctr, 33) {
        try {
            s21::polish polish("");
            ASSERT_EQ(polish.getPolish(),"");
        } catch (const std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 34) {
        try {
            s21::polish polish("");
            ASSERT_EQ(polish.getPolish(),"");
        } catch (const std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 35) {
        try {
            s21::polish polish("");
            ASSERT_EQ(polish.getPolish(),"");
        } catch (const std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }

    TEST(polish_ctr, 36) {
        try {
            s21::polish polish("(((1+2*3/4-5)%6)/12*cos(24*sin(13)))/(tan(15-13)+log(23))");
            ASSERT_EQ(polish.getPolish(),"1 2 3 * 4 / + 5 - 6 % 12 / 24 13 s * c * 15 13 - t 23 L + / ");
        } catch (const std::exception& e) {
            FAIL() << "Unexpected exception: " << e.what();
        }
    }



} //namespace polish_test




#endif //SMARTCALC2_POLISH_CTR_TEST_H
