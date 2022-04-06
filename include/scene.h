#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"

typedef struct menu_select {
  uint8_t s1;
  uint8_t s2;
  uint8_t s3;
  uint8_t s4;
  uint8_t s5;
  uint8_t s6;
  uint8_t s7;
} menu_select_t;

//start scene
error_code_e cli_scene_handler(void);
error_code_e cli_scene_game_start(data_table_t *dt);
error_code_e cli_scene_prologue(data_table_t *dt);

//menu
error_code_e cli_scene_menu(data_table_t *dt, const action_t *action, const uint8_t options);
error_code_e cli_scene_menu_incity(data_table_t *dt);
error_code_e cli_scene_menu_onroad(data_table_t *dt);
error_code_e cli_scene_menu_indungeon(data_table_t *dt);
error_code_e cli_scene_menu_global_map(data_table_t *dt);
error_code_e cli_scene_menu_local_map(data_table_t *dt);
error_code_e cli_scene_menu_status(data_table_t *dt);
error_code_e cli_scene_menu_item(data_table_t *dt);
error_code_e cli_scene_menu_explorer(data_table_t *dt);
error_code_e cli_scene_menu_explorer_itemshop(data_table_t *dt);
error_code_e cli_scene_menu_explorer_blacksmith(data_table_t *dt);
error_code_e cli_scene_menu_explorer_guild(data_table_t *dt);
error_code_e cli_scene_menu_explorer_southport_dungeon(data_table_t *dt);
error_code_e cli_scene_menu_move(data_table_t *dt);

//dungeon
error_code_e cli_scene_dungeon_maoucastle(data_table_t *dt);


#endif //SCENE_H