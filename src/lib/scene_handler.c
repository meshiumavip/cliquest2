#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

static error_code_e cli_create_tabldes(data_table_t *dt) {
  error_code_e rc = RC_SUCESS;
  map_t *m_table = dt->m_table;
  item_t *i_table = dt->i_table;
  player_t *p_data = &(dt->p_data);
  rc = cli_create_item_table(i_table);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  rc = cli_create_map_table(m_table);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  return RC_SUCESS;
}

error_code_e cli_scene_handler(void) {
  data_table_t data_table;
  data_table_t *dt = &data_table;
  cli_create_tabldes(dt);
  dt->next_s = SCENE_GAME_START;
  uint8_t loop = 1;
  uint8_t rc = RC_SUCESS;
  scene_handler_t handler[] = {
  };
  while (loop) {
    switch (dt->next_s) {
      case SCENE_GAME_START:
        rc = cli_scene_game_start(dt);
        CLI_ERROR(rc = RC_INTERNAL_ERROR)
        break;
      case SCENE_PROLOGUE:
        rc = cli_scene_prologue(dt);
        CLI_ERROR(rc = RC_INTERNAL_ERROR)
        loop = 0;
        break;
      case ACTION_MENU_MAIN:
        cli_scene_main_menu(dt);
        break;
      case SCENE_MAOU_CASTLE:
        cli_scene_maou_castle(dt);
        break;
      default:
        CLI_LOG("Scene selection error.");
        loop = 0;
        return RC_INTERNAL_ERROR;
        break;
    }
  }
  return RC_SUCESS;
}