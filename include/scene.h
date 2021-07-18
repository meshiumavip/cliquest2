#ifndef SCENE
#define SCENE

#include <stdint.h>
#include <stdio.h>

typedef enum {
  TITLE_SCENE = 0,
  INPUT_SCENE,
  SELECT_SCENE,
  NAME_INPUT_SCENE,
} scene_e;

void scene_game_start(void);

#endif  // SCENE