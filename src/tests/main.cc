#include <gtest/gtest.h>

#include <iostream>

#include "model/credit_calc_test.h"
#include "model/date_test.h"
#include "model/deposit_calc_test.h"
#include "model/polish_test/polish_test.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
