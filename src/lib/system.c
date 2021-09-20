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

error_code_e cli_template_logger(const char *filename, const int32_t line, const char *funcname, const char *str) {
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
  item_t item_table[ITEM_ID_MAX] = {
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
  map_t map_table[8] = {
    {"世界地図", GLOBAL_MAP, GLOBAL,{
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
  
  memcpy(m_table, map_table, sizeof(map_t)*8);
  return RC_SUCESS;
}


static error_code_e lntrim(char *str, const size_t data_size){
  for(int32_t i = 0; i < data_size ; i++){
    if (str[i] == '\n'){
      str[i] = '\0';
      return RC_SUCESS;
    }
  }
  return RC_INTERNAL_ERROR;
};

error_code_e cli_get_input_data(char *str, int32_t *num, const size_t data_size, const input_data_type_e data_type) {
  fgets(str, data_size, stdin);
  lntrim(str, data_size);
  if (data_type == DATA_TYPE_INT) {
    *num = atoi(str);
    return RC_SUCESS;
  }
  return RC_SUCESS;
}

error_code_e cli_equip_item(player_equipment_t *pe, const item_list_e il, const item_type_e it) {
  if (it == ARMOR){
    pe->armor = il;
  }
  if (it == WEAPON){
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
  CLI_PRINT("名前を教えてください。：");
  ret = cli_get_input_data(p_data->name, NULL, sizeof(char) * PLAYER_NAME_MAX, DATA_TYPE_CHAR);
  if (ret != RC_SUCESS) {
    return RC_INTERNAL_ERROR;
  }
  return RC_SUCESS;
  }

/*
error_code_e cli_scene_view(list_t *list){
    LOG("");
    for(int32_t i =0; i<20 ;i++){
        if(list[i].value == -1){
            break;
        }
        PRINT("%d: %s", list[i].value, list[i].key);
    }
}

error_code_e cli_scene_selector(list_t *list, int32_t list_max, player_t *player){
    LOG("");
    int32_t ret = ERROR_SUCCESS;
    int32_t num;
    char *str;
    scene_input(&num, list_max, list);
    ret = list[num-1].next_scene(player);
    DEBUG("");PRINT(" ret %d");
    return ret;
}

error_code_e cli_scene_input(int32_t *num, int32_t list_max, list_t *list){
    LOG("");
    char str[4];//正常値は２桁＋入力時の改行＋終端文字＝４byte、5byte以上は不正
        while(1){
            PRINT("---------------------------");
            printf("入力：");
            fgets(str, sizeof(str), stdin);
            PRINT("\n");
            if(str[strlen(str)-1] != '\n' ){while( getchar() != '\n');} //stdinに残った5byte以降の文字を回収
            if(strlen(str) == 1){scene_view(list); continue;}; //未入力チェック
            *num=atoi(str);
            if(*num == 0){scene_view(list); continue;} //文字列を除外
            if(0 <= *num && *num <= list_max){
                break;
            }
            scene_view(list);
        }
}
*/