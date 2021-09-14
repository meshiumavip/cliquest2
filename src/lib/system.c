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
    return RC_SUCESS;
  }
  return RC_SUCESS;
}

error_code_e cli_create_item_table(item_info_t *item_table) {
  item_info_t i_t[ITEM_ID_MAX] = {
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
  memcpy(item_table, i_t, sizeof(i_t));
  item_table = i_t;
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
  CLI_PRINT("名前を教えてください。：");
  ret = cli_get_input_data(player_info->name, sizeof(char) * PLAYER_NAME_MAX, DATA_TYPE_CHAR);
  if (ret != RC_SUCESS) {
    return INTERNAL_ERROR;
  }
  return RC_SUCESS;
}

error_code_e cli_main_menu(data_table_t *data_table) {
  return RC_SUCESS;
}