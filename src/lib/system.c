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
    return INTERNAL_ERROR;
  }
  fprintf(file, "%s:%d %s() :%s\n", filename, line, funcname, str);
  fclose(file);
  return RC_SUCESS;
}

error_code_e cli_get_input_data(char *input, const size_t data_size, const input_data_type_e data_type) {
  fgets(input, data_size, stdin);
  if (data_type == DATA_TYPE_INT) {
    int32_t input_data_int = atoi(input);
    printf("int :%d\n", input_data_int);
    return RC_SUCESS;
  }
  printf("char :%s", input);
  return RC_SUCESS;
}

error_code_e cli_equip_item(player_equipment_t *player_equipment, item_list_e equipment) {
  // TODO アイテムリストとタグを照合して装備種別で判定
  return RC_SUCESS;
}

error_code_e cli_init_player_data(data_table_t *data_table) {
  int32_t ret;
  player_info_t *player_info = &(data_table->player_info);
  player_equipment_t *player_equipment = &(player_info->player_equipment);
  player_info->global_location = SOUTH_PORT;
  player_info->local_location = 0;
  player_info->item[0] = HP_PORTION;
  player_info->item[1] = MP_PORTION;
  player_info->item[2] = IRON_SWORD;
  player_info->item[3] = LEATHRE_ARMOR;
  player_info->player_status.MAX_HP = 100;
  player_info->player_status.MAX_MP = 100;
  player_info->player_status.HP = 100;
  player_info->player_status.MP = 100;
  player_info->player_status.ATT = 10;
  player_info->player_status.DEF = 10;
  player_info->player_status.WIS = 10;
  player_info->player_status.SPD = 10;
  ret = cli_equip_item(player_equipment, IRON_SWORD);
  if (ret != RC_SUCESS) {
    return INTERNAL_ERROR;
  }
  ret = cli_equip_item(player_equipment, LEATHRE_ARMOR);
  if (ret != RC_SUCESS) {
    return INTERNAL_ERROR;
  }
  printf("名前を教えてください。：");
  ret = cli_get_input_data(player_info->name, sizeof(char) * PLAYER_NAME_MAX, DATA_TYPE_CHAR);
  if (ret != RC_SUCESS) {
    return INTERNAL_ERROR;
  }
  return RC_SUCESS;
}