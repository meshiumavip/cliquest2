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
  strcpy(dt->p_data.name, "kana");
  cli_scene_game_start(dt);
  EXPECT_EQ(SCENE_PROLOGUE, dt->next_s);
}

TEST_F(cli_scene, Test2) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  error_code_e rc = cli_scene_prologue(dt);
  EXPECT_EQ(ACTION_MENU_MAIN, dt->next_s);
  EXPECT_EQ(RC_SUCESS, rc);
}

/*
TEST_F(cli_scene, Test2) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  error_code_e rc = cli_scene_maou_castle(dt);
//  EXPECT_EQ(, dt->next_s);
  EXPECT_EQ(RC_SUCESS, rc);
}
*/