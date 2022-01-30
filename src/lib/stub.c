#include <stdio.h>
#include <stdlib.h>
#include "system.h"

error_code_e cli_system_clear(){
  system("clear");
  return RC_SUCESS;
}