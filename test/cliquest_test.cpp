#include <gtest/gtest.h>
extern "C" {
#include <stdio.h>
#include <stdint.h>
#include "cliquest_error.h"
#include "system.h"
}

class SystemTest : public ::testing::Test {};
TEST_F(SystemTest, Test1) {
  EXPECT_EQ(RC_SUCESS, cli_template_logger("filename", 123, "funcname", "test"));
}

TEST_F(SystemTest, Test2) {
  char input[32];
  EXPECT_EQ(RC_SUCESS, cli_get_input_data(input, sizeof(char) * 32, DATA_TYPE_CHAR));
}