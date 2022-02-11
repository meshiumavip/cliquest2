#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"
#include "color.h"

error_code_e cli_logger(const char *filename, const int32_t line, const char *funcname, const char *str) {
  FILE *file;
  if ((file = fopen("cliquest.log", "a")) == NULL) {
    printf("ファイルが開けませんでした");
    return RC_INTERNAL_ERROR;
  }
  fprintf(file, "%s:%d %s() :%s\n", filename, line, funcname, str);
  fclose(file);
  return RC_SUCESS;
}

static error_code_e cli_convert_local_map_elements(data_table_t *dt, const int32_t x, const int32_t y){
  local_map_t *m_table = &(dt->lm_table[dt->p_data.ll_tag]);
    bool is_player_here = false;
  char color[32] = "WHITE";
  if(dt->p_data.local_location[0] == x && dt->p_data.local_location[1] == y){
    is_player_here = true;
    sprintf(color, "YELLOW");
  }
  switch (m_table->map_field[x][y]){
    case WALL:
      printf("  ");
      break;
    case PATH:
      cli_color_print(color, " +");
      break;
    case SECRET_PATH:
      cli_color_print(color, " *");
      break;
    case BOSS:
      cli_color_print(color, " B");
      break;
    default:
      break;
  }
  return RC_SUCESS;
}

error_code_e cli_draw_local_map(data_table_t *dt){
  for(int32_t x=0 ; x<10; x++){
    for(int32_t y=0 ; y<10; y++){
      cli_convert_local_map_elements(dt, x, y);
    }
    printf("\n");
  }
  return RC_SUCESS;
}

static error_code_e cli_convert_global_map_elements(data_table_t *dt, const int32_t x, const int32_t y){
  global_map_t *gm_table = &(dt->gm_table[dt->p_data.gl_tag]);
  bool is_player_here = false;
  char color[32] = "WHITE";
  if(dt->p_data.global_location[0] == x && dt->p_data.global_location[1] == y){
    is_player_here = true;
    sprintf(color, "YELLOW");
  }
  switch (gm_table->map_field[x][y]){
    case OPEN_SPACE:
      printf("  ");
      break;
    case ROAD:
      cli_color_print(color, " +");
      break;
    case CITY:
      cli_color_print(color, " C");
      break;
    case DUNGEON:
      cli_color_print(color, " D");
      break;
    default:
      break;
  }
}

error_code_e cli_draw_global_map(data_table_t *dt){
  for(int32_t x=0 ; x<10; x++){
    for(int32_t y=0 ; y<10; y++){
      cli_convert_global_map_elements(dt, x, y);
    }
    printf("\n");
  }
  return RC_SUCESS;
}

error_code_e cli_create_item_table(item_t *i_table) {
  item_t item_table[] = {
      {HP_PORTION, TIRE0, NORMAL_ITEM, "HPポーション", "HPを50回復する", 50, 0, 0, 0, 0, 0},
      {MP_PORTION, TIRE0, NORMAL_ITEM, "MPポーション", "MPを50回復する", 0, 50, 0, 0, 0, 0},
      {IRON_SWORD, TIRE1, WEAPON, "鉄の剣", "", 0, 0, 10, 0, 0, 10},
      {MITHRIL_SWORD, TIRE2, WEAPON, "ミスリルの剣", "", 0, 0, 20, 0, 5, 5},
      {CRYSTAL_SWORD, TIRE3, WEAPON, "クリスタルの剣", "", 0, 0, 30, 0, 10, 0},
      {DESTINY_SWORD, TIRE4, WEAPON, "宿命の剣", "", 50, -50, 50, 20, 0, -30},
      {WOOD_WAND, TIRE1, WEAPON, "木の杖", "", 0, 0, 10, 0, 10, 0},
      {SPRITE_WAND, TIRE2, WEAPON, "妖精の杖", "", 0, 0, 0, 0, 20, 5},
      {CRYSTAL_WAND, TIRE3, WEAPON, "クリスタルの杖", "", 0, 0, 0, 0, 30, 10},
      {TWILIGHT_WAND, TIRE4, WEAPON, "黄昏の杖", "", -50, 50, 0, -30, 50, 20},
      {LEATHRE_ARMOR, TIRE1, ARMOR, "皮の鎧", "", 50, 0, 0, 10, 0, 10},
      {MITHRIL_ARMOR, TIRE2, ARMOR, "ミスリルの鎧", "", 75, 0, 0, 20, 5, 5},
      {CRYSTAL_ARMOR, TIRE3, ARMOR, "クリスタルの鎧", "", 100, 0, 0, 30, 10, 0},
      {IMMORTAL_ARMOR, TIRE4, ARMOR, "不滅の鎧", "", 200, -100, -10, 80, -10, -20},
      {WIZARD_ROBE, TIRE1, ARMOR, "魔法使いのローブ", "", 20, 30, 0, 10, 0, 10},
      {SPRITE_ROBE, TIRE2, ARMOR, "妖精のローブ", "", 30, 45, 0, 15, 0, 15},
      {HOLY_ROBE, TIRE3, ARMOR, "聖なるローブ", "", 40, 60, 0, 20, 0, 20},
      {REINCARNATION_ROBE, TIRE4, ARMOR, "輪廻転生のローブ", "", 0, 100, -10, -10, 30, 30},
  };
  memcpy(i_table, item_table, sizeof(item_table));
  return RC_SUCESS;
}

error_code_e cli_create_local_map_table(local_map_t *lm_table) {
  local_map_t map_table[] = {
    {CENTRAL, "セントラル", {6,4}, },
    {NORTH_CITY, "北の街", {3,5}, },
    {SOUTH_PORT, "南の港", {9,4},
      {
        {0 , 0 , 0 , 0 , 3 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 2 , 2 , 2 , 2 , 3 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
      }
    },
    {EAST_MOUNTAIN, "東の山", {6,9}, },
    {WEST_DESERT, "西の砂漠", {9,0}, },
    {NORTH_MEADOW, "北の草原", {0,9}, },
    { CRISTAL_CAVE, "クリスタルの洞窟", {3,9},},
  };
  memcpy(lm_table, map_table, sizeof(map_table));
  return RC_SUCESS;
}

error_code_e cli_create_global_map_table(global_map_t *gm_table) {
  global_map_t map_table[] = {
    {GLOBAL_MAP_STAGE1, "1の島",
      {
        {0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 3 },
        {0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 },
        {0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 },
        {0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 0 , 3 },
        {0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 1 , 1 , 2 , 1 , 1 , 1 , 1 , 3 },
        {0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        {3 , 0 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 },
      }
    },{GLOBAL_MAP_STAGE2, "2の島", }
  };
  memcpy(gm_table, map_table, sizeof(map_table));
  return RC_SUCESS;
}

static error_code_e lntrim(char *str, const size_t data_size) {
  for (int32_t i = 0; i < data_size; i++) {
    if (str[i] == '\n') {
      str[i] = '\0';
      return RC_SUCESS;
    }
  }
  return RC_INTERNAL_ERROR;
};

error_code_e cli_get_input_num(const char *msg, int32_t *num) {
  char buf[NAME_MAX];
  while (1) {
    if(msg != NULL){
      CLI_PRINT("%s", msg)
      printf(">");
    }
    if (fgets(buf, NAME_MAX, stdin) == NULL) {
      CLI_PRINT("入力値が不正です。1")
      printf(">");
      continue;
    }
    if (buf[0] == '\n'){
      CLI_PRINT("入力値が不正です。2")
      printf(">");
      continue;
    }
    lntrim(buf, NAME_MAX);
    *num = atoi(buf);
    if (*num == 0) {
      CLI_PRINT("数値を入力してください。")
      printf(">");
      continue;
    }
    break;
  }
  return RC_SUCESS;
}

error_code_e cli_get_input_str(const char *msg, const size_t data_size, char *buf) {
  while (1) {
    if(msg != NULL){
      CLI_PRINT("%s", msg)
      printf(">");
    }
    if (fgets(buf, data_size, stdin) == NULL) {
      CLI_PRINT("入力値が不正です。3")
      printf(">");
      continue;
    }
    if (buf[0] == '\n'){
      CLI_PRINT("入力値が不正です。4")
      printf(">");
      continue;
    }
    break;
  }
  lntrim(buf, data_size);
  return RC_SUCESS;
}

error_code_e cli_get_input_action(const uint8_t actions, uint8_t *num){
  char buf[NAME_MAX];
  while (1) {
    if (fgets(buf, NAME_MAX, stdin) == NULL) {
      CLI_PRINT("入力値が不正です。5")
      printf(">");
      continue;
    }
    if (buf[0] == '\n'){
      CLI_PRINT("入力値が不正です。6")
      printf(">");
      continue;
    }
    lntrim(buf, NAME_MAX);
    *num = atoi(buf);
    if (*num == 0) {
      CLI_PRINT("数値を入力してください。")
      printf(">");
      continue;
    }
    break;
  }
  return RC_SUCESS;
}


error_code_e cli_equip_item(player_equipment_t *pe, const item_list_e il, const item_type_e it) {
  if (it == ARMOR) {
    pe->armor = il;
  }
  if (it == WEAPON) {
    pe->weapon = il;
  }
  return RC_SUCESS;
}

error_code_e cli_init_player_data(player_t *p_data) {
  int32_t ret;
  player_equipment_t *pe = &(p_data->pe);
  p_data->gl_tag = GLOBAL_MAP_STAGE1;
  p_data->ll_tag = SOUTH_PORT;
  p_data->global_location[0] = 9;
  p_data->global_location[1] = 4;
  p_data->local_location[0] = 9;
  p_data->local_location[1] = 4;
  p_data->item[0] = HP_PORTION;
  p_data->item[1] = MP_PORTION;
  p_data->item[2] = IRON_SWORD;
  p_data->item[3] = LEATHRE_ARMOR;
  p_data->ps.MAX_HP = 100;
  p_data->ps.MAX_MP = 100;
  p_data->ps.HP = 100;
  p_data->ps.MP = 100;
  p_data->ps.ATT = 10;
  p_data->ps.DEF = 10;
  p_data->ps.WIS = 10;
  p_data->ps.SPD = 10;
  ret = cli_equip_item(pe, IRON_SWORD, WEAPON);
  if (ret != RC_SUCESS) {
    return RC_INTERNAL_ERROR;
  }
  ret = cli_equip_item(pe, LEATHRE_ARMOR, ARMOR);
  if (ret != RC_SUCESS) {
    return RC_INTERNAL_ERROR;
  }
  ret = cli_get_input_str("名前を教えてください。",sizeof(char) * NAME_MAX,  p_data->name);
  if (ret != RC_SUCESS) {
    return RC_INTERNAL_ERROR;
  }
  ret = cli_system_clear();
  if (ret != RC_SUCESS) {
    return RC_INTERNAL_ERROR;
  }
  return RC_SUCESS;
}