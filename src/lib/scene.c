#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"


  /*
  View functions
  */
static void cli_scene_display_actions(const data_table_t *dt, const action_t *action , const uint8_t options) {
  CLI_PRINT("----------------------------------------")
  for (int32_t i = 0; i < options; i++) {
    CLI_PRINT("%d: %s", i + 1, action[i].str);
  }
  CLI_PRINT("----------------------------------------")
  printf(">");
}

static error_code_e cli_scene_replace_text(char *buf, const char *old, const char *rep) {
  CLI_ERROR(buf == NULL)
  CLI_ERROR(old == NULL)
  CLI_ERROR(rep == NULL)
  char tmp[1024];
  char *p;

  /*
   buf old ...
   buf \0 old tmp
   buf new tmp
  */
  while ((p = strstr(buf, old)) != NULL) {
    *p = '\0';
    p += strlen(old);
    strcpy(tmp, p);
    strcat(buf, rep);
    strcat(buf, tmp);
  }
  return RC_SUCESS;
}

static error_code_e cli_scene_text_separator(const char *str, bool *is_separate) {
  error_code_e rc = RC_SUCESS;
  if (strcmp(str, "▼\n") == 0) {
    CLI_PRINT("\n")
    CLI_PRINT("-----------------")
    CLI_PRINT("next enter")
    *is_separate = true;
    while (getchar() != '\n') {
    }
    rc = cli_system_clear();
    CLI_ERROR(rc == RC_INTERNAL_ERROR)
  }
  return RC_SUCESS;
}

static error_code_e cli_scene_print_text(const char file[], const char *name) {
  char str[PRINT_MAX];
  bool is_separate = false;
  FILE *fp = fopen(file, "r");
  CLI_ERROR(fp == NULL)
  while (fgets(str, sizeof(str), fp) != NULL) {
    is_separate = false;
    cli_scene_text_separator(str, &is_separate);
    if (is_separate) {
      continue;
    }
    cli_scene_replace_text(str, "ユーザ名", name);
    printf("%s", str);
  }
  fclose(fp);
  return RC_SUCESS;
}

  /*
  Start scene
  */

error_code_e cli_scene_game_start(data_table_t *dt) {
  uint8_t num = 0;
  char file[] = "/home/wsl/cliquest2/text/title.txt";
  error_code_e rc = RC_SUCESS;
  action_t action[] = {
      {1, SCENE_PROLOGUE, "さいしょから"},
      {2, SCENE_MENU_MAIN_INCITY, "つづきから"},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);

  rc = cli_scene_print_text(file, dt->p_data.name);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  cli_scene_display_actions(dt, action, options);
  rc = cli_get_input_action(options, &num);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  dt->next_s = action[num - 1].next_s;
  return RC_SUCESS;
}

error_code_e cli_scene_prologue(data_table_t *dt) {
  uint8_t rc = RC_SUCESS;
  rc = cli_init_player_data(&(dt->p_data));
  char file[] = "/home/wsl/cliquest2/text/prologue.txt";
  rc = cli_scene_print_text(file, dt->p_data.name);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  dt->next_s = SCENE_MENU_MAIN_INCITY;
  return RC_SUCESS;
}

  /*
  Menu Scene
  */
error_code_e cli_scene_menu(data_table_t *dt, const action_t *action, const uint8_t options) {
  error_code_e rc = RC_SUCESS;
  uint8_t select_num;
  cli_scene_display_actions(dt, action, options);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  rc = cli_get_input_action(options, &select_num);
  CLI_ERROR(select_num > options)
  dt->next_s = action[select_num - 1].next_s;
  return RC_SUCESS;
}

error_code_e cli_scene_menu_indungeon(data_table_t *dt) {
  CLI_PRINT("%s %s", dt->gm_table[dt->p_data.gl_tag].name, dt->lm_table[dt->p_data.ll_tag].name)
  error_code_e rc = RC_SUCESS;
  action_t action[] = {
      {1, SCENE_MENU_GLOBAL_MAP, "世界地図"},  //
      {2, SCENE_MENU_LOACL_MAP, "ダンジョンマップ"},
      {3, SCENE_MENU_STATUS, "ステータス"},
      {4, SCENE_MENU_ITEM, "アイテム"},
      {5, SCENE_MENU_MOVE, "移動"},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);
  cli_scene_menu(dt, action, options);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  return RC_SUCESS;
}

error_code_e cli_scene_menu_onroad(data_table_t *dt) {
  CLI_PRINT("%s", dt->gm_table[dt->p_data.gl_tag].name)
  error_code_e rc = RC_SUCESS;
  action_t action[] = {
      {1, SCENE_MENU_GLOBAL_MAP, "世界地図"},  //
      {2, SCENE_MENU_STATUS, "ステータス"},
      {3, SCENE_MENU_ITEM, "アイテム"},
      {4, SCENE_MENU_MOVE, "移動"},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);
  cli_scene_menu(dt, action, options);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  return RC_SUCESS;
}

error_code_e cli_scene_menu_incity(data_table_t *dt) {
  CLI_PRINT("%s %s", dt->gm_table[dt->p_data.gl_tag].name, dt->lm_table[dt->p_data.ll_tag].name)
  error_code_e rc = RC_SUCESS;
  action_t action[] = {
      {1, SCENE_MENU_GLOBAL_MAP, "世界地図"},  //
      {2, SCENE_MENU_STATUS, "ステータス"},
      {3, SCENE_MENU_ITEM, "アイテム"},
      {4, SCENE_MENU_EXPLORER, "探索"},
      {5, SCENE_MENU_MOVE, "移動"},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);
  cli_scene_menu(dt, action, options);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  return RC_SUCESS;
}

error_code_e cli_scene_menu_global_map(data_table_t *dt) {
  cli_view_global_map(dt);
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_local_map(data_table_t *dt) {
  cli_view_local_map(dt);
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_status(data_table_t *dt) {
  cli_view_player_status(dt);
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_item(data_table_t *dt) {
  CLI_PRINT("%s %s", dt->gm_table[dt->p_data.gl_tag].name, dt->lm_table[dt->p_data.ll_tag].name)
  CLI_PRINT("所持品")
  CLI_PRINT("----------------------------------------")
  for(int32_t i=0; i<10; i++){
    CLI_PRINT("%-20s %-20s", dt->i_table[dt->p_data.item[i]].item_name, dt->i_table[dt->p_data.item[i+10]].item_name)
  }
  CLI_PRINT("----------------------------------------")
  return RC_INTERNAL_ERROR;
}

/*
  Explorer Scene
*/

error_code_e cli_scene_menu_explorer_southport_dungeon(data_table_t *dt){
  CLI_PRINT("港町の下水道")
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_explorer_guild(data_table_t *dt){
  CLI_PRINT("ギルド")
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_explorer_blacksmith(data_table_t *dt){
  CLI_PRINT("鍛冶屋")
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_explorer_itemshop(data_table_t *dt){
  CLI_PRINT("道具屋")
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_explorer_southport(data_table_t *dt) {
  error_code_e rc = RC_SUCESS;
  CLI_PRINT("探索")
  action_t action[] = {
      {1, SCENE_MENU_EXPLORER_ITEMSHOP, "道具屋"},
      {2, SCENE_MENU_EXPLORER_BLACKSMITH, "鍛冶屋"},
      {3, SCENE_MENU_EXPLORER_GUILD, "冒険者ギルド"},
      {4, SCENE_MENU_EXPLORER_SOUTHPORT_DUNGEON, "港町の下水道"},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);
  cli_scene_menu(dt, action, options);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_explorer(data_table_t *dt){
  switch (dt->p_data.ll_tag){
    case SOUTH_PORT:
      cli_scene_menu_explorer_southport(dt);
      break;
    default:
      break;
  }
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_move_east(data_table_t *dt) {
  return RC_INTERNAL_ERROR;
}
error_code_e cli_scene_menu_move_west(data_table_t *dt) {
  return RC_INTERNAL_ERROR;
}
error_code_e cli_scene_menu_move_south(data_table_t *dt) {
  return RC_INTERNAL_ERROR;
}
error_code_e cli_scene_menu_move_north(data_table_t *dt) {
  return RC_INTERNAL_ERROR;
}

error_code_e cli_scene_menu_move(data_table_t *dt) {
  error_code_e rc = RC_SUCESS;
  CLI_PRINT("%s %s", dt->gm_table[dt->p_data.gl_tag].name, dt->lm_table[dt->p_data.ll_tag].name)
  CLI_PRINT("移動")
  action_t action[] = {
      {1, SCENE_MENU_MOVE_EAST, "東"},
      {2, SCENE_MENU_MOVE_WEST, "西"},
      {3, SCENE_MENU_MOVE_SOUTH, "南"},
      {4, SCENE_MENU_MOVE_NORTH, "北"},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);
  cli_scene_menu(dt, action, options);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  return RC_INTERNAL_ERROR;
}

  /*
  Dungeon functions
  */
error_code_e cli_scene_dungeon_maoucastle(data_table_t *dt) {
  return RC_SUCESS;
}