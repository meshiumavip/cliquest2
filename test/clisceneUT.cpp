#include <gtest/gtest.h>
extern "C" {
#include <stdint.h>
#include <stdio.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"
}

#undef CLI_PRINT
#define CLI_PRINT(...) strlen(__VA_ARGS__)
extern "C" {
#include "scene.c"
}

class cli_system : public ::testing::Test {};
TEST_F(cli_system, Test1) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  cli_scene_game_start(dt);
  EXPECT_EQ(MAIN_MENU, dt->next_s);
}