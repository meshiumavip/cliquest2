#include <gtest/gtest.h>
extern "C" {
#include <stdint.h>
#include <stdio.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"
}

#define cli_system_clear cli_stub_system_clear
error_code_e cli_stub_system_clear(){return RC_SUCESS;}

extern "C" {
#include "scene.c"
#include "system.c"
}

class cli_scene : public ::testing::Test {};

TEST_F(cli_scene, Test1) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  strcpy(dt->p_data.name, "name");
  cli_scene_game_start(dt);
  EXPECT_EQ(SCENE_PROLOGUE, dt->next_s);
}

TEST_F(cli_scene, Test2) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  error_code_e rc = cli_scene_prologue(dt);
  EXPECT_EQ(SCENE_MENU_MAIN_INCITY, dt->next_s);
  EXPECT_EQ(RC_SUCESS, rc);
}


TEST_F(cli_scene, Test3) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  action_t action[] = {
      {1, SCENE_UT, "action1"},  //
  };
  uint8_t options = sizeof(action) / sizeof(action_t);
  error_code_e rc = cli_scene_menu(dt, action, options);
  EXPECT_EQ(SCENE_UT, dt->next_s);
  EXPECT_EQ(RC_SUCESS, rc);
}

TEST_F(cli_scene, Test3_2) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  sprintf(dt->gm_table[dt->p_data.gl_tag].name,"gl_tag");
  sprintf(dt->lm_table[dt->p_data.ll_tag].name,"ll_tag");
  error_code_e rc = cli_scene_menu_indungeon(dt);
  EXPECT_EQ(SCENE_MENU_GLOBAL_MAP, dt->next_s);
  EXPECT_EQ(RC_SUCESS, rc);
}

TEST_F(cli_scene, Test3_3) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  sprintf(dt->gm_table[dt->p_data.gl_tag].name,"gl_tag");
  error_code_e rc = cli_scene_menu_onroad(dt);
  EXPECT_EQ(SCENE_MENU_MOVE, dt->next_s);
  EXPECT_EQ(RC_SUCESS, rc);
}

TEST_F(cli_scene, Test3_4) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  sprintf(dt->gm_table[dt->p_data.gl_tag].name,"gl_tag");
  sprintf(dt->lm_table[dt->p_data.ll_tag].name,"ll_tag");
  error_code_e rc = cli_scene_menu_incity(dt);
  EXPECT_EQ(SCENE_MENU_MOVE, dt->next_s);
  EXPECT_EQ(RC_SUCESS, rc);
}

TEST_F(cli_scene, Test3_5) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  sprintf(dt->gm_table[dt->p_data.gl_tag].name,"gl_tag");
  cli_create_global_map_table(dt->gm_table);
  error_code_e rc = cli_scene_menu_global_map(dt);
  EXPECT_EQ(RC_INTERNAL_ERROR, rc);
}

TEST_F(cli_scene, Test3_6) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  sprintf(dt->lm_table[dt->p_data.ll_tag].name,"ll_tag");
  cli_create_local_map_table(dt->lm_table);
  error_code_e rc = cli_scene_menu_local_map(dt);
  EXPECT_EQ(RC_INTERNAL_ERROR, rc);
}

TEST_F(cli_scene, Test3_7) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  player_status_t *ps = &(dt->p_data.ps);
  sprintf(dt->p_data.name,"name");
  ps->MAX_HP = 100;
  ps->MAX_MP = 100;
  ps->HP = 100;
  ps->MP = 100;
  ps->ATT = 10;
  ps->DEF = 10;
  ps->WIS = 10;
  ps->SPD = 10;
  error_code_e rc = cli_scene_menu_status(dt);
  EXPECT_EQ(RC_INTERNAL_ERROR, rc);
}

TEST_F(cli_scene, Test3_8) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  cli_create_tabldes(dt);
  cli_init_player_data(&(dt->p_data));
  error_code_e rc = cli_scene_menu_item(dt);
  EXPECT_EQ(RC_INTERNAL_ERROR, rc);
}