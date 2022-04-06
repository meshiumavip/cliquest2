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
      {SCENE_MENU_MAIN_INCITY, cli_scene_menu_incity},
      {SCENE_MENU_MAIN_ONROAD, cli_scene_menu_onroad},
      {SCENE_MENU_MAIN_DUNGEON, cli_scene_menu_indungeon},
      {SCENE_MENU_GLOBAL_MAP, cli_scene_menu_global_map},
      {SCENE_MENU_LOACL_MAP, cli_scene_menu_local_map},
      {SCENE_MENU_STATUS, cli_scene_menu_status},
      {SCENE_MENU_ITEM, cli_scene_menu_item},
      {SCENE_MENU_EXPLORER, cli_scene_menu_explorer},
      {SCENE_MENU_EXPLORER_ITEMSHOP, cli_scene_menu_explorer_itemshop},
      {SCENE_MENU_EXPLORER_BLACKSMITH, cli_scene_menu_explorer_blacksmith},
      {SCENE_MENU_EXPLORER_GUILD, cli_scene_menu_explorer_guild},
      {SCENE_MENU_EXPLORER_SOUTHPORT_DUNGEON, cli_scene_menu_explorer_southport_dungeon},
      {SCENE_MENU_MOVE, cli_scene_menu_move},
      {SCENE_DUNGEON_MAOU_CASTLE, cli_scene_dungeon_maoucastle},
  };

  while (rc == RC_SUCESS) {
    rc = cli_system_clear();
    CLI_ERROR(rc == RC_INTERNAL_ERROR)
    rc = handler[dt->next_s].scene(dt);
    CLI_ERROR(rc == RC_INTERNAL_ERROR)
  }
  return RC_SUCESS;
}