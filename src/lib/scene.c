#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

/*
error_code_e cli_scene_xx(data_table_t *data_table){
  return RC_SUCESS;
}
*/

static void cli_display_actions(action_t *action, int32_t size) {
  CLI_PRINT("----------------------------------------");
  for (int32_t i = 0; i < size; i++) {
    CLI_PRINT("%d: %s", i + 1, action[i].str);
  }
}

/*
advenger
*/
error_code_e cli_scene_game_start(data_table_t *dt) {
  char str[NAME_MAX];
  int32_t num;
  error_code_e rc = RC_SUCESS;
  CLI_PRINT(" ")
  CLI_PRINT(" ")
  CLI_PRINT("  ####   ####      ######             ###    ##   ##  #######   #####    # #####")
  CLI_PRINT(" ##  ##   ##         ##              ## ##   ##   ##   ##   #  ##   ##  ## ## ##")
  CLI_PRINT("##        ##         ##             ##   ##  ##   ##   ##      ##          ##")
  CLI_PRINT("##        ##         ##             ##   ##  ##   ##   ####     #####      ##")
  CLI_PRINT("##        ##         ##             ##   ##  ##   ##   ##           ##     ##")
  CLI_PRINT(" ##  ##   ##  ##     ##              ## ##   ##   ##   ##   #  ##   ##     ##")
  CLI_PRINT("  ####   #######   ######             ####    #####   #######   #####     ####")
  CLI_PRINT("                                         ##")
  CLI_PRINT(" ")
  CLI_PRINT("                                   PRESS ENTER")

  rc = cli_get_input_data(str, NULL, sizeof(char) * NAME_MAX, DATA_TYPE_CHAR);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  CLI_PRINT(" ")
  action_t action[2] = {
      {1, "さいしょから", SCENE_PROLOGUE},
      {2, "つづきから", ACTION_MENU_MAIN},
  };
  cli_display_actions(action, 2);
  rc = cli_get_input_data(str, &num, sizeof(char) * NAME_MAX, DATA_TYPE_INT);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  CLI_ERROR(num <= 0)
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

error_code_e cli_scene_main_menu(data_table_t *dt) {
  char str[NAME_MAX];
  int32_t num;
  error_code_e rc = RC_SUCESS;
  uint8_t size = 6;
  action_t action[] = {
      {1, "世界地図", ACTION_MENU_GLOBAL_MAP},  //
      {2, "ダンジョン地図", ACTION_MENU_LOACL_MAP},
      {3, "ステータス", ACTION_MENU_STATUS},
      {4, "アイテム", ACTION_MENU_ITEM},
      {5, "探索", ACTION_MENU_EXPLORER},
      {6, "移動", ACTION_MENU_MOVE},
  };
  cli_display_actions(action, size);
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  rc = cli_get_input_data(str, &num, sizeof(char) * NAME_MAX, DATA_TYPE_CHAR);
  CLI_ERROR(num < size)
  CLI_ERROR(rc == RC_INTERNAL_ERROR)
  return RC_SUCESS;
}

error_code_e cli_scene_maou_castle(data_table_t *dt) {
  return RC_SUCESS;
}