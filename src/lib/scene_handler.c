#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

static error_code_e cli_create_tabldes(data_table_t *dt){
  map_t *m_table = dt->m_table;
  item_t *i_table = dt->i_table;
  player_t *p_data = &(dt->p_data);
  cli_create_item_table(i_table);
  cli_create_map_table(m_table);
  cli_init_player_data(p_data);
  return RC_SUCESS;
}

error_code_e cli_scene_handler(void) {
  data_table_t data_table;
  data_table_t *dt = &data_table;
  cli_create_tabldes(dt);
  dt->next_s = START_SCENE;
  switch (dt->next_s) {
    case START_SCENE:
      cli_scene_game_start(dt);
      break;
    case MAIN_MENU:
      cli_scene_main_menu(dt);
      break;
    case MAOU_CASTLE_SCENE:
      cli_scene_maou_castle(dt);
      break;
    default:
      template_log("Scene selection error.");
      return RC_INTERNAL_ERROR;
      break;
  }
  return RC_SUCESS;
}