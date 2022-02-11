#include <stdio.h>
#include <string.h>
#include "color.h"
#include "system.h"
#include "cliquest_error.h"

error_code_e cli_color_print(const char *color, const char *str) {
  if (strcmp(color, "WHITE") == 0) {
    WHITE("%s", str);
  }
  if (strcmp(color, "YELLOW") == 0) {
    YELLOW("%s", str);
  }
  return RC_SUCESS;
}