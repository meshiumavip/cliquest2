#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

error_code_e cli_scene_handler(void) {
  data_table_t data_table;
  data_table_t* dt = &data_table;
  cli_create_item_table(dt->item_table);
  dt->next_scene = START_SCENE;
  switch (dt->next_scene) {
    case START_SCENE:
      cli_scene_game_start(dt);
      cli_init_player_data(dt);
      break;
    case MAIN_MENU:
      cli_main_menu(dt);
      break;
    case MAOU_CASTLE_SCENE:
      cli_scene_maou_castle(dt);
      break;
    default:
      template_log("Scene selection error.");
      return INTERNAL_ERROR;
      break;
  }
  return RC_SUCESS;
}