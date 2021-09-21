#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"

typedef struct menu_select {
  map_type_e mt;
  uint8_t s1;
  uint8_t s2;
  uint8_t s3;
  uint8_t s4;
  uint8_t s5;
  uint8_t s6;
  uint8_t s7;
} menu_select_t;

error_code_e cli_scene_handler(void);
error_code_e cli_scene_game_start(data_table_t *dt);
error_code_e cli_scene_prologue(data_table_t *dt);
error_code_e cli_scene_maou_castle(data_table_t *dt);

error_code_e cli_action_menu_main(data_table_t *dt);
error_code_e cli_action_menu_global_map(data_table_t *dt);
error_code_e cli_action_menu_status(data_table_t *dt);
error_code_e cli_action_menu_item(data_table_t *dt);
error_code_e cli_action_menu_explorer(data_table_t *dt);
error_code_e cli_action_menu_move(data_table_t *dt);
#endif //SCENE_H