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
  cli_create_item_table(dt->i_table);
  EXPECT_STREQ("HPポーション", dt->i_table[HP_PORTION].item_name);
  EXPECT_STREQ("輪廻転生のローブ", dt->i_table[REINCARNATION_ROBE].item_name);
}


TEST_F(cli_system, Test3) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  map_t *mt = dt->m_table;
  EXPECT_EQ(RC_SUCESS, cli_create_map_table(mt));
  EXPECT_STREQ("世界地図", mt[0].name);
  EXPECT_STREQ("クリスタルの洞窟", mt[7].name);
  EXPECT_EQ(0, mt[0].map_field[0][0]);
  EXPECT_EQ(9, mt[0].map_field[9][10]);
}

TEST_F(cli_system, Test4) {
  char str[32];
  int32_t num;
  EXPECT_EQ(RC_SUCESS, cli_get_input_data(str, NULL, sizeof(char) * 32, DATA_TYPE_CHAR));
  EXPECT_STREQ("name", str);
  EXPECT_EQ(RC_SUCESS, cli_get_input_data(str, &num, sizeof(char) * 32, DATA_TYPE_INT));
  EXPECT_EQ(100, num);
}

TEST_F(cli_system, Test5) {
  player_equipment_t pe;
  EXPECT_EQ(RC_SUCESS, cli_equip_item(&pe, IRON_SWORD, WEAPON));
  EXPECT_EQ(IRON_SWORD, pe.weapon);
  EXPECT_EQ(RC_SUCESS, cli_equip_item(&pe, LEATHRE_ARMOR, ARMOR));
  EXPECT_EQ(LEATHRE_ARMOR, pe.armor);
}

TEST_F(cli_system, Test6) {
  player_t p_data;
  EXPECT_EQ(RC_SUCESS, cli_init_player_data(&p_data));
  EXPECT_STREQ("name", p_data.name);
}
