#ifndef SYSTEM
#define SYSTEM

#include <stdint.h>
#include <stdio.h>
#include "cliquest_error.h"

#define template_log(...) template_logger(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define CLI_PRINT(...) printf(__VA_ARGS__), printf("\n")

#define PLAYER_NAME_MAX 32

typedef enum {
  DATA_TYPE_CHAR = 0,
  DATA_TYPE_INT,
} input_data_type_e;

error_code_e game_main();
int32_t template_logger(char *filename, int32_t line, const char *funcname, char *str);
void get_input_data(char *input_data, size_t size, input_data_type_e data_type);

#endif  // SYSTEM