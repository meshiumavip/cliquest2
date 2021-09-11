#ifndef SCENE
#define SCENE

#include <stdint.h>
#include <stdio.h>

#include "data_table.h"
#include "cliquest_error.h"

typedef enum {
  START_SCENE,
  MAOU_CASTLE_SCENE,
} scene_e;

error_code_e cli_scene_handler(void);
void cli_scene_game_start(data_table_t *data_table);
error_code_e cli_scene_maou_castle(data_table_t *data_table);

#endif  // SCENE