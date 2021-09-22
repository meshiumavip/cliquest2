#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

/*
error_code_e cli_scene_xx(data_table_t *data_table){
  return RC_SUCESS;
}
*/

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

error_code_e cli_create_map_table(map_t *m_table) {
  uint8_t CE = CENTRAL;
  uint8_t NC = NORTH_CITY;
  uint8_t SP = SOUTH_PORT;
  uint8_t EM = EAST_MOUNTAIN;
  uint8_t WD = WEST_DESERT;
  uint8_t NM = NORTH_MEADOW;
  uint8_t CC = CRISTAL_CAVE;
  map_t map_table[] = {
    {"世界地図", GLOBAL_MAP, GLOBAL,
      {
        {0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , NM, 9},
        {0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 9},
        {0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , 9},
        {0 , 0 , 0 , 0 , 0 , NC, 0 , 0 , 0 , CC, 9},
        {0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 9},
        {0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 9},
        {0 , 0 , 1 , 1 , CE, 1 , 1 , 1 , 1 , EM, 9},
        {0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 9},
        {1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 9},
        {WD, 0 , 0 , 0 , SP, 0 , 0 , 0 , 0 , 0 , 9},
      }
    },
    {"セントラル", CENTRAL, CITY, },
    {"北の街", NORTH_CITY, CITY, },
    {"南の港", SOUTH_PORT, CITY, },
    {"東の山", EAST_MOUNTAIN, DUNGEON, },
    {"西の砂漠", WEST_DESERT, DUNGEON, },
    {"北の草原", NORTH_MEADOW, DUNGEON, },
    {"クリスタルの洞窟", CRISTAL_CAVE, DUNGEON, },
  };
    memcpy(m_table, map_table, sizeof(map_table));
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
    }
    if (fgets(buf, NAME_MAX, stdin) == NULL) {
      CLI_PRINT("入力値が不正です。1")
      continue;
    }
    if (buf[0] == '\n'){
      CLI_PRINT("入力値が不正です。2")
      continue;
    }
    lntrim(buf, NAME_MAX);
    *num = atoi(buf);
    if (*num == 0) {
      CLI_PRINT("数値を入力してください。")
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
    }
    if (fgets(buf, data_size, stdin) == NULL) {
      CLI_PRINT("入力値が不正です。3")
      continue;
    }
    if (buf[0] == '\n'){
      CLI_PRINT("入力値が不正です。4")
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
      continue;
    }
    if (buf[0] == '\n'){
      CLI_PRINT("入力値が不正です。6")
      continue;
    }
    lntrim(buf, NAME_MAX);
    *num = atoi(buf);
    if (*num == 0) {
      CLI_PRINT("数値を入力してください。")
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
  p_data->gl = SOUTH_PORT;
  p_data->local_location = 0;
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
  ret = cli_get_input_str("名前を教えてください。：",sizeof(char) * NAME_MAX,  p_data->name);
  if (ret != RC_SUCESS) {
    return RC_INTERNAL_ERROR;
  }
  return RC_SUCESS;
}