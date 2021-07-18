#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliquest_error.h"
#include "data_table.h"
#include "system.h"
#include "scene.h"

int32_t template_logger(char *filename, int32_t line, const char *funcname, char *str) {
  FILE *file;
  if ((file = fopen("cliquest.log", "a")) == NULL) {
    printf("ファイルが開けませんでした");
    return INTERNAL_ERROR;
  }
  fprintf(file, "%s:%d %s() :%s\n", filename, line, funcname, str);
  fclose(file);
  return RC_SUCESS;
}

void get_input_data(char *input_data, size_t size, input_data_type_e data_type) {

  fgets(input_data, size, stdin);
  if (data_type == DATA_TYPE_INT) {
    int32_t input_data_int = atoi(input_data);
    printf("int :%d\n", input_data_int);
    return;
  }
  printf("char :%s", input_data);
}

static void equip_item(player_equipment_t *player_equipment, item_list_e equipment) {
  //アイテムリストとタグを照合して装備種別で判定
}

static void init_player_data(data_table_t *data_table) {
  player_info_t *player_info = &(data_table->player_info);
  player_equipment_t *player_equipment = &(player_info->player_equipment);
  player_info->global_location = SOUTH_PORT;
  player_info->local_location = 0;
  player_info->item[0] = HP_PORTION;
  player_info->item[1] = MP_PORTION;
  player_info->item[2] = IRON_SWORD;
  player_info->item[3] = LEATHRE_ARMOR;
  equip_item(player_equipment, IRON_SWORD);
  equip_item(player_equipment, LEATHRE_ARMOR);
  printf("名前を教えてください。：");
  get_input_data(player_info->name, sizeof(char) * PLAYER_NAME_MAX, DATA_TYPE_CHAR);
  player_info->player_status.MAX_HP = 100;
  player_info->player_status.MAX_MP = 100;
  player_info->player_status.HP = 100;
  player_info->player_status.MP = 100;
  player_info->player_status.ATT = 10;
  player_info->player_status.DEF = 10;
  player_info->player_status.WIS = 10;
  player_info->player_status.SPD = 10;
}

error_code_e game_main(void) {
  data_table_t data_table;
  scene_game_start();
  init_player_data(&data_table);
  return RC_SUCESS;
}