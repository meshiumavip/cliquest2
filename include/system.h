#ifndef SYSTEM
#define SYSTEM

#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"

#define template_log(...) cli_template_logger(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define CLI_PRINT(...) printf(__VA_ARGS__), printf("\n")

#define PLAYER_NAME_MAX 32

typedef enum {
  DATA_TYPE_CHAR = 0,
  DATA_TYPE_INT,
} input_data_type_e;

error_code_e cli_template_logger(char *filename, int32_t line, const char *funcname, char *str);
error_code_e cli_get_input_data(char *input_data, size_t size, input_data_type_e data_type);
error_code_e cli_equip_item(player_equipment_t *player_equipment, item_list_e equipment);
error_code_e cli_init_player_data(data_table_t *data_table);

#endif  // SYSTEM