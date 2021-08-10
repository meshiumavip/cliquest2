#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

error_code_e cli_scene_handler(void) {
  data_table_t data_table;
  cli_scene_game_start(&(data_table.next_scene));
  cli_init_player_data(&data_table);
  cli_scene_maou_castle(&data_table);
  return RC_SUCESS;
}