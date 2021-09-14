#include <gtest/gtest.h>
extern "C" {
#include <stdint.h>
#include <stdio.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "system.h"
}

#undef CLI_PRINT
#define CLI_PRINT(...) strlen(__VA_ARGS__)
extern "C" {
#include "system.c"
}

class cli_system : public ::testing::Test {};
TEST_F(cli_system, Test1) {
  EXPECT_EQ(RC_SUCESS, cli_template_logger("filename", 123, "funcname", "test"));
}

TEST_F(cli_system, Test2) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  cli_create_item_table(dt->item_table);
  EXPECT_STREQ("HPポーション", dt->item_table[HP_PORTION].item_name);
  EXPECT_STREQ("輪廻転生のローブ", dt->item_table[REINCARNATION_ROBE].item_name);
}

TEST_F(cli_system, Test3) {
  char input[32];
  EXPECT_EQ(RC_SUCESS, cli_get_input_data(input, sizeof(char) * 32, DATA_TYPE_CHAR));
}

TEST_F(cli_system, Test4) {
  player_equipment_t pe;
  item_list_e e = MITHRIL_SWORD;
  EXPECT_EQ(RC_SUCESS, cli_equip_item(&pe, e));
}

TEST_F(cli_system, Test5) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  EXPECT_EQ(RC_SUCESS, cli_init_player_data(dt));
}