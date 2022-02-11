#ifndef COLOR
#define COLOR

#include "cliquest_error.h"

#define BLACK(...)           printf("\033[30m" __VA_ARGS__), printf("\033[0m")
#define RED(...)             printf("\033[31m" __VA_ARGS__), printf("\033[0m")
#define GREEN(...)           printf("\033[32m" __VA_ARGS__), printf("\033[0m")
#define YELLOW(...)          printf("\033[33m" __VA_ARGS__), printf("\033[0m")
#define BLUE(...)            printf("\033[34m" __VA_ARGS__), printf("\033[0m")
#define MAZENTA(...)         printf("\033[35m" __VA_ARGS__), printf("\033[0m")
#define CYAN(...)            printf("\033[36m" __VA_ARGS__), printf("\033[0m")
#define WHITE(...)           printf("\033[37m" __VA_ARGS__), printf("\033[0m")
#define BOLD_BLACK(...)      printf("\033[1m\033[30m" __VA_ARGS__), printf("\033[0m")
#define BOLD_RED(...)        printf("\033[1m\033[31m" __VA_ARGS__), printf("\033[0m")
#define BOLD_GREEN(...)      printf("\033[1m\033[32m" __VA_ARGS__), printf("\033[0m")
#define BOLD_YELLOW(...)     printf("\033[1m\033[33m" __VA_ARGS__), printf("\033[0m")
#define BOLD_BLUE(...)       printf("\033[1m\033[34m" __VA_ARGS__), printf("\033[0m")
#define BOLD_MAZENTA(...)    printf("\033[1m\033[35m" __VA_ARGS__), printf("\033[0m")
#define BOLD_CYAN(...)       printf("\033[1m\033[36m" __VA_ARGS__), printf("\033[0m")
#define BOLD_WHITE(...)      printf("\033[1m\033[36m" __VA_ARGS__), printf("\033[0m")

error_code_e cli_color_print(const char *color, const char *str);

#endif