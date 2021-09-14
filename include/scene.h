#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"

typedef enum {
  START_SCENE,
  MAIN_MENU,
  MAOU_CASTLE_SCENE,
} scene_e;

error_code_e cli_scene_handler(void);
void cli_scene_game_start(data_table_t *data_table);
void cli_scene_maou_castle(data_table_t *data_table);
#endif  // SCENE_H