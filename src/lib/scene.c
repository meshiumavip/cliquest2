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

/*
advenger
aquaplan
future_1
soft
*/

void cli_scene_game_start(data_table_t *dt) {
  char str[ANY_INPUT_MAX];
  int32_t num;
  CLI_PRINT(" ");
  CLI_PRINT(" ");
  CLI_PRINT("  ####   ####      ######             ###    ##   ##  #######   #####    # #####");
  CLI_PRINT(" ##  ##   ##         ##              ## ##   ##   ##   ##   #  ##   ##  ## ## ##");
  CLI_PRINT("##        ##         ##             ##   ##  ##   ##   ##      ##          ##");
  CLI_PRINT("##        ##         ##             ##   ##  ##   ##   ####     #####      ##");
  CLI_PRINT("##        ##         ##             ##   ##  ##   ##   ##           ##     ##");
  CLI_PRINT(" ##  ##   ##  ##     ##              ## ##   ##   ##   ##   #  ##   ##     ##");
  CLI_PRINT("  ####   #######   ######             ####    #####   #######   #####     ####");
  CLI_PRINT("                                         ##");
  CLI_PRINT(" ");
  CLI_PRINT("                                   PRESS ENTER");

  cli_get_input_data(str, NULL, sizeof(char) * ANY_INPUT_MAX, DATA_TYPE_CHAR);
  CLI_PRINT(" ");
  CLI_PRINT("1:さいしょから");
  CLI_PRINT("2:つづきから");
  cli_get_input_data(str, &num, sizeof(char) * ANY_INPUT_MAX, DATA_TYPE_CHAR);
  switch (num)
  {
  case 1:
    dt->next_s = MAIN_MENU;
      break;
  default:
    dt->next_s = MAIN_MENU;
      break;
  }
}

void cli_scene_main_menu(data_table_t *dt) {

}

void cli_scene_maou_castle(data_table_t *dt) {
}