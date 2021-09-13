#ifndef SYSTEM
#define SYSTEM

#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"

#define template_log(...) cli_template_logger(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define CLI_PRINT(...) printf(__VA_ARGS__), printf("\n")

typedef enum {
  DATA_TYPE_CHAR = 0,
  DATA_TYPE_INT,
} input_data_type_e;

error_code_e cli_template_logger(const char *filename, const int32_t line, const char *funcname, const char *str);
error_code_e cli_create_item_table(item_info_t *item_table);
error_code_e cli_get_input_data(char *input, const size_t data_size, const input_data_type_e data_type);
error_code_e cli_equip_item(player_equipment_t *player_equipment, item_list_e equipment);
error_code_e cli_init_player_data(data_table_t *data_table);

#endif  // SYSTEM