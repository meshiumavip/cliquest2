#ifndef SCENE
#define SCENE

#include <stdint.h>
#include <stdio.h>

#include "data_table.h"
#include "cliquest_error.h"

typedef enum {
  INPUT_SCENE = 0,
  SELECT_SCENE,
  NAME_INPUT_SCENE,
} scene_e;

error_code_e cli_scene_handler(void);
void cli_scene_game_start(int32_t *next_scene);
error_code_e cli_scene_maou_castle(data_table_t *data_table);

#endif  // SCENE