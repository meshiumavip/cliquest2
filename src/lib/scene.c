#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

static void cli_display_actions(const uint8_t options, action_t *action) {
  CLI_PRINT("----------------------------------------");
  for (int32_t i = 0; i < options; i++) {
    CLI_PRINT("%d: %s", i + 1, action[i].str);
  }
}

error_code_e cli_print_text(char file[PRINT_MAX]){
  char str[PRINT_MAX];
  FILE *fp = fopen(file, "r");
  while ( fgets(str, sizeof(str), fp) != NULL) {
    printf("%s", str);
  }
  fclose(fp);
}

error_code_e cli_scene_game_start(data_table_t *dt) {
  uint8_t num = 0;
  char file[PRINT_MAX] = "/home/wsl/cliquest2/text/title.txt";
  error_code_e rc = RC_SUCESS;
  action_t action[] = {
      {1, "さいしょから", SCENE_PROLOGUE},
      {2, "つづきから", ACTION_MENU_MAIN},
  };
  uint8_t options = sizeof(action) / sizeof(action_t);
  cli_print_text(file);
  cli_display_actions(options, action);
  rc = cli_get_input_action(options, &num);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  dt->next_s = action[num - 1].next_s;
  return RC_SUCESS;
}

error_code_e cli_scene_prologue(data_table_t *dt) {
  uint8_t rc = RC_SUCESS;
  rc = cli_init_player_data(&(dt->p_data));
  CLI_PRINT("%sの冒険が始まる...", dt->p_data.name)
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
  CLI_PRINT("TBD")
  return RC_INTERNAL_ERROR;
}

error_code_e cli_action_menu_local_map(data_table_t *dt) {
  CLI_PRINT("TBD")
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