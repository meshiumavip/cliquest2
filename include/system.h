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

error_code_e cli_logger(const char *filename, const int32_t line, const char *funcname, const char *str);
error_code_e cli_create_item_table(item_t *ii_table);
error_code_e cli_create_map_table(map_t *mi);
error_code_e cli_get_input_data(char *str, int32_t *num, const size_t data_size, const input_data_type_e data_type);
error_code_e cli_equip_item(player_equipment_t *pe, const item_list_e il, const item_type_e it);
error_code_e cli_init_player_data(player_t *p_data);
#endif  // SYSTEM_H