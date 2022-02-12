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
  local_map_t *lm_table = dt->lm_table;
  global_map_t *gm_table = dt->gm_table;
  item_t *i_table = dt->i_table;
  player_t *p_data = &(dt->p_data);
  rc = cli_create_item_table(i_table);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  rc = cli_create_local_map_table(lm_table);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  rc = cli_create_global_map_table(gm_table);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  return RC_SUCESS;
}

error_code_e cli_scene_handler(void) {
  data_table_t data_table;
  data_table_t *dt = &data_table;
  cli_create_tabldes(dt);
  dt->next_s = SCENE_GAME_START;
  uint8_t rc = RC_SUCESS;
  // TODO secene_eと配列の順序が一致しないと適切な関数を呼び出せない
  scene_handler_t handler[] = {
      {SCENE_GAME_START, cli_scene_game_start},
      {SCENE_PROLOGUE, cli_scene_prologue},
      {SCENE_MAOU_CASTLE, cli_scene_maou_castle},
      {ACTION_MENU_MAIN_CITY, cli_action_menu_city},
      {ACTION_MENU_MAIN_ROAD,},
      {ACTION_MENU_MAIN_DUNGEON,},
      {ACTION_MENU_GLOBAL_MAP, cli_action_global_map},
      {ACTION_MENU_LOACL_MAP, cli_action_local_map},
      {ACTION_MENU_STATUS, cli_action_status},
      {ACTION_MENU_ITEM, cli_action_item},
      {ACTION_MENU_EXPLORER, cli_action_explorer},
      {ACTION_MENU_MOVE, cli_action_move},
  };

  while (rc == RC_SUCESS) {
    rc = cli_system_clear();
    CLI_ERROR(rc == RC_INTERNAL_ERROR)
    rc = handler[dt->next_s].scene(dt);
    CLI_ERROR(rc == RC_INTERNAL_ERROR)
  }
  return RC_SUCESS;
}