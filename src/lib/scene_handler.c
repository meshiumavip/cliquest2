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
  uint8_t rc = RC_SUCESS;
  scene_handler_t handler[] = {
      {SCENE_GAME_START, cli_scene_game_start},
      {SCENE_PROLOGUE, cli_scene_prologue},
      {SCENE_MAOU_CASTLE, cli_scene_maou_castle},
      {ACTION_MENU_MAIN, cli_action_menu_main},
      {ACTION_MENU_GLOBAL_MAP, cli_action_menu_global_map},
      {ACTION_MENU_LOACL_MAP, cli_action_menu_local_map},
      {ACTION_MENU_STATUS, cli_action_menu_status},
      {ACTION_MENU_ITEM, cli_action_menu_item},
      {ACTION_MENU_EXPLORER, cli_action_menu_explorer},
      {ACTION_MENU_MOVE, cli_action_menu_move},
  };

  while (rc == RC_SUCESS) {
    rc = handler[dt->next_s].scene(dt);
    CLI_ERROR(rc == RC_INTERNAL_ERROR)
  }
  return RC_SUCESS;
}