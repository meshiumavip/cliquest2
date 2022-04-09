#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"

#define CLI_LOG(...) cli_logger(__FILE__, __LINE__, __func__, __VA_ARGS__);
#define CLI_PRINT(...) \
  printf(__VA_ARGS__); \
  printf("\n");
#define CLI_ERROR(...)        \
  if (__VA_ARGS__) {          \
    CLI_LOG(NULL)             \
    return RC_INTERNAL_ERROR; \
  }

typedef error_code_e (*SCENE)(data_table_t *);

typedef struct{
  scene_e next_s;
  SCENE scene;
}scene_handler_t;

error_code_e cli_create_tabldes(data_table_t *dt);

error_code_e cli_system_clear();
error_code_e cli_logger(const char *filename, const int32_t line, const char *funcname, const char *str);

error_code_e cli_equip_item(player_equipment_t *pe, const item_list_e il, const item_type_e it);
error_code_e cli_view_player_status(data_table_t *dt);
error_code_e cli_view_local_map(data_table_t *dt);
error_code_e cli_view_global_map(data_table_t *dt);

error_code_e cli_init_player_data(player_t *p_data);

error_code_e cli_create_item_table(item_t *ii_table);
error_code_e cli_create_global_map_table(global_map_t *gm_table);
error_code_e cli_create_local_map_table(local_map_t *lm_table);

error_code_e cli_get_input_num(const char *msg, int32_t *num);
error_code_e cli_get_input_str(const char *msg, const size_t data_size, char *buf);
error_code_e cli_get_input_action(const uint8_t options, uint8_t *num);
#endif  // SYSTEM_H