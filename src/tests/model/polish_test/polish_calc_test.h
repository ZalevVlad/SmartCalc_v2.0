#ifndef SMARTCALC2_POLISH_CALC_TEST_H
#define SMARTCALC2_POLISH_CALC_TEST_H

#include <gtest/gtest.h>

#include "../../../model/polish.h"

#define EPS 1e-7

namespace polish_test {

TEST(polish_calc, 0) {
  try {
    s21::polish polish("0");
    ASSERT_NEAR(polish.calc(0), 0, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 1) {
  try {
    s21::polish polish("1");
    ASSERT_NEAR(polish.calc(0), 1, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 2) {
  try {
    s21::polish polish("-1234");
    ASSERT_NEAR(polish.calc(0), -1234, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 3) {
  try {
    s21::polish polish("1e12");
    ASSERT_NEAR(polish.calc(0), 1e12, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 4) {
  try {
    s21::polish polish("-1.23453e-4");
    ASSERT_NEAR(polish.calc(0), -1.23453e-4, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 5) {
  try {
    s21::polish polish("7+8");
    ASSERT_NEAR(polish.calc(0), 15, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 6) {
  try {
    s21::polish polish("19-8");
    ASSERT_NEAR(polish.calc(0), 11, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 7) {
  try {
    s21::polish polish("11*2");
    ASSERT_NEAR(polish.calc(0), 22, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 8) {
  try {
    s21::polish polish("44/2");
    ASSERT_NEAR(polish.calc(0), 22, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 9) {
  try {
    s21::polish polish("15%6");
    ASSERT_NEAR(polish.calc(0), 3, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 10) {
  try {
    s21::polish polish("3^3");
    ASSERT_NEAR(polish.calc(0), 27, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 11) {
  try {
    s21::polish polish("sin(0.5)");
    ASSERT_NEAR(polish.calc(0), std::sin(0.5), EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 12) {
  try {
    s21::polish polish("cos(0.5)");
    ASSERT_NEAR(polish.calc(0), std::cos(0.5), EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 13) {
  try {
    s21::polish polish("tan(0.5)");
    ASSERT_NEAR(polish.calc(0), 5.46302489843790484e-01, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 14) {
  try {
    s21::polish polish("asin(0.5)");
    ASSERT_NEAR(polish.calc(0), 5.23598775598298927e-01, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 15) {
  try {
    s21::polish polish("acos(0.5)");
    ASSERT_NEAR(polish.calc(0), 1.04719755119659785e+00, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 16) {
  try {
    s21::polish polish("atan(0.5)");
    ASSERT_NEAR(polish.calc(0), 4.63647609000806094e-01, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 17) {
  try {
    s21::polish polish("sqrt(0.5)");
    ASSERT_NEAR(polish.calc(0), 7.07106781186547573e-01, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 18) {
  try {
    s21::polish polish("ln(0.5)");
    ASSERT_NEAR(polish.calc(0), -6.93147180559945286e-01, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 19) {
  try {
    s21::polish polish("log(0.5)");
    ASSERT_NEAR(polish.calc(0), -3.01029995663981198e-01, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 20) {
  try {
    s21::polish polish("sin(2)+cos(2)+tan(2)+asin(0.5)+acos(0.5)+atan(0.5)+sqrt(2)+ln(2)+log(2)");
    ASSERT_NEAR(polish.calc(0), 2.7509454014097446056, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 21) {
  try {
    s21::polish polish("sin(2)+cos(2)+tan(2)*(asin(0.5)/(acos(0.5)*atan(0.5)))^sqrt(2)-ln(2)/log(2)");
    ASSERT_NEAR(polish.calc(0), -4.240631132380359079728, EPS);
  } catch (const std::exception &e) {
    FAIL() << "Unexpected exception: " << e.what();
  }
}

TEST(polish_calc, 22) {
  try {
    s21::polish polish("2 2");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 23) {
  try {
    s21::polish polish("2+");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 24) {
  try {
    s21::polish polish("2-");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 25) {
  try {
    s21::polish polish("2*");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 26) {
  try {
    s21::polish polish("2/");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 27) {
  try {
    s21::polish polish("2^");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 28) {
  try {
    s21::polish polish("2%");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 29) {
  try {
    s21::polish polish("-");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 30) {
  try {
    s21::polish polish("+");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 31) {
  try {
    s21::polish polish("sin()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 32) {
  try {
    s21::polish polish("cos()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 33) {
  try {
    s21::polish polish("tan()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 34) {
  try {
    s21::polish polish("asin()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 35) {
  try {
    s21::polish polish("acos()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 36) {
  try {
    s21::polish polish("atan()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 37) {
  try {
    s21::polish polish("sqrt()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 38) {
  try {
    s21::polish polish("ln()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 39) {
  try {
    s21::polish polish("log()");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 40) {
  try {
    s21::polish polish("2+2+");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

TEST(polish_calc, 41) {
  try {
    s21::polish polish("(2 * 2) - ((0 + 1) - -)");
    polish.calc(0);
    FAIL() << "Expected runtime error";
  } catch (const std::runtime_error &e) {
    SUCCEED();
  } catch (const std::exception &e) {
    FAIL() << "Expected runtime error";
  }
}

}  // namespace polish_test

#endif  // SMARTCALC2_POLISH_CALC_TEST_H
