#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

static void cli_display_actions(const uint8_t options, action_t *action) {
  CLI_PRINT("----------------------------------------");
  for (int32_t i = 0; i < options; i++) {
    CLI_PRINT("%d: %s", i + 1, action[i].str);
  }
  CLI_PRINT("----------------------------------------");
  printf(">");
}

static error_code_e cli_replace_text(char *buf, const char *old, const char *rep) {
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

static error_code_e cli_text_separator(const char *str, bool *is_separate) {
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

static error_code_e cli_print_text(const char file[], const char *name) {
  char str[PRINT_MAX];
  bool is_separate = false;
  FILE *fp = fopen(file, "r");
  CLI_ERROR(fp == NULL)
  while (fgets(str, sizeof(str), fp) != NULL) {
    is_separate = false;
    cli_text_separator(str, &is_separate);
    if (is_separate) {
      continue;
    }
    cli_replace_text(str, "ユーザ名", name);
    printf("%s", str);
  }
  fclose(fp);
  return RC_SUCESS;
}

error_code_e cli_scene_game_start(data_table_t *dt) {
  uint8_t num = 0;
  char file[] = "/home/wsl/cliquest2/text/title.txt";
  error_code_e rc = RC_SUCESS;
  action_t action[] = {
      {1, "さいしょから", SCENE_PROLOGUE},
      {2, "つづきから", ACTION_MENU_MAIN},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);

  rc = cli_print_text(file, dt->p_data.name);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  cli_display_actions(options, action);
  rc = cli_get_input_action(options, &num);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  dt->next_s = action[num - 1].next_s;
  return RC_SUCESS;
}

error_code_e cli_scene_prologue(data_table_t *dt) {
  uint8_t rc = RC_SUCESS;
  rc = cli_init_player_data(&(dt->p_data));
  char file[] = "/home/wsl/cliquest2/text/prologue.txt";
  rc = cli_print_text(file, dt->p_data.name);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  dt->next_s = ACTION_MENU_MAIN;
  return RC_SUCESS;
}

error_code_e cli_scene_maou_castle(data_table_t *dt) {
  return RC_SUCESS;
}

error_code_e cli_action_menu_main(data_table_t *dt) {
  error_code_e rc = RC_SUCESS;
  char str[NAME_MAX];
  uint8_t num;
  action_t action[] = {
      {1, "世界地図", ACTION_MENU_GLOBAL_MAP},  //
      {2, "ダンジョン地図", ACTION_MENU_LOACL_MAP},
      {3, "ステータス", ACTION_MENU_STATUS},
      {4, "アイテム", ACTION_MENU_ITEM},
      {5, "探索", ACTION_MENU_EXPLORER},
      {6, "移動", ACTION_MENU_MOVE},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);
  cli_display_actions(options, action);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  rc = cli_get_input_action(options, &num);
  CLI_ERROR(num > options)
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  dt->next_s = action[num - 1].next_s;
  return RC_SUCESS;
}

error_code_e cli_action_menu_global_map(data_table_t *dt) {
  cli_draw_global_map(dt);
  return RC_INTERNAL_ERROR;
}

error_code_e cli_action_menu_local_map(data_table_t *dt) {
  cli_draw_local_map(dt);
  return RC_INTERNAL_ERROR;
}

error_code_e cli_action_menu_status(data_table_t *dt) {
  CLI_PRINT("TBD")
  return RC_INTERNAL_ERROR;
}

error_code_e cli_action_menu_item(data_table_t *dt) {
  CLI_PRINT("TBD")
  return RC_INTERNAL_ERROR;
}

error_code_e cli_action_menu_explorer(data_table_t *dt) {
  CLI_PRINT("TBD")
  return RC_INTERNAL_ERROR;
}

error_code_e cli_action_menu_move(data_table_t *dt) {
  CLI_PRINT("TBD")
  return RC_INTERNAL_ERROR;
}