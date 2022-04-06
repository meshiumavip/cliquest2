#include <gtest/gtest.h>
extern "C" {
#include <stdint.h>
#include <stdio.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "system.h"
}

#define cli_system_clear cli_stub_system_clear
error_code_e cli_stub_system_clear(){return RC_SUCESS;}

extern "C" {
#include "system.c"
}

class cli_system : public ::testing::Test {};
TEST_F(cli_system, Test1) {
  error_code_e rc = CLI_LOG("test") EXPECT_EQ(RC_SUCESS, rc);
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
  global_map_t* gm_table = dt->gm_table;
  EXPECT_EQ(RC_SUCESS, cli_create_global_map_table(gm_table));
  EXPECT_STREQ("1の島", gm_table[0].name);
  EXPECT_STREQ("2の島", gm_table[1].name);
  EXPECT_EQ(0, gm_table[0].map_field[0][0]);
  EXPECT_EQ(3, gm_table[0].map_field[0][9]);
  EXPECT_EQ(2, gm_table[0].map_field[9][4]);
}

TEST_F(cli_system, Test3_2) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  local_map_t* lm_table = dt->lm_table;
  EXPECT_EQ(RC_SUCESS, cli_create_local_map_table(lm_table));
  EXPECT_STREQ("セントラル", lm_table[0].name);
  EXPECT_STREQ("クリスタルの洞窟", lm_table[6].name);
  EXPECT_EQ(0, lm_table[2].map_field[0][0]);
  EXPECT_EQ(3, lm_table[2].map_field[5][9]);
  EXPECT_EQ(1, lm_table[2].map_field[9][4]);
}

TEST_F(cli_system, Test4) {
  char buf[NAME_MAX];
  EXPECT_EQ(RC_SUCESS, cli_get_input_str("Test4", sizeof(buf), buf));
  EXPECT_STREQ("name", buf);
}

TEST_F(cli_system, Test4_2) {
  int32_t num=0;
  EXPECT_EQ(RC_SUCESS, cli_get_input_num("Test4_2", &num));
  EXPECT_EQ(100, num);
}

TEST_F(cli_system, Test4_3) {
  uint8_t num = 0;
  action_t action[] = {
      {1, SCENE_MENU_GLOBAL_MAP, "世界地図"},  //
      {2, SCENE_MENU_STATUS, "ステータス"},
      {3, SCENE_MENU_ITEM, "アイテム"},
      {5, SCENE_MENU_EXPLORER, "探索"},
      {5, SCENE_MENU_MOVE, "移動"},
  };
  uint8_t options = sizeof(action)/sizeof(action_t);
  EXPECT_EQ(RC_SUCESS, cli_get_input_action(options, &num));
  EXPECT_EQ(6, num);
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
