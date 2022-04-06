#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include <stdint.h>
#include <stdio.h>

#define NAME_MAX 32
#define ID_MAX 255
#define PRINT_MAX 255
#define PLAYER_ITEM_MAX 20
#define ITEM_DISCRIBE_MAX 128

// MAP
typedef enum {
  GLOBAL_MAP_STAGE1,
  GLOBAL_MAP_STAGE2,
}global_location_tag_e;

typedef enum {
  CENTRAL,
  NORTH_CITY,
  SOUTH_PORT,
  EAST_MOUNTAIN,
  WEST_DESERT,
  NORTH_MEADOW,
  CRISTAL_CAVE,
} local_location_tag_e;

typedef enum {
  OPEN_SPACE,
  ROAD,
  CITY,
  DUNGEON,
} global_map_element_e;

typedef enum {
  WALL,
  PATH,
  SECRET_PATH,
  BOSS,
} local_map_element_e;

typedef struct {
  global_location_tag_e gl_tag;
  char name[NAME_MAX];
  uint8_t map_field[10][10];
} global_map_t;

typedef struct {
  local_location_tag_e ll_tag;
  char name[NAME_MAX];
  uint8_t global_location[2];
  uint8_t map_field[10][10];
} local_map_t;

// ITEM
typedef enum {
  EMPTY = 0,
  HP_PORTION,
  MP_PORTION,
  IRON_SWORD,
  MITHRIL_SWORD,
  CRYSTAL_SWORD,
  DESTINY_SWORD,
  WOOD_WAND,
  SPRITE_WAND,
  CRYSTAL_WAND,
  TWILIGHT_WAND,
  LEATHRE_ARMOR,
  MITHRIL_ARMOR,
  CRYSTAL_ARMOR,
  IMMORTAL_ARMOR,
  WIZARD_ROBE,
  SPRITE_ROBE,
  HOLY_ROBE,
  REINCARNATION_ROBE,
} item_list_e;

typedef enum {
  TIRE0,
  TIRE1,
  TIRE2,
  TIRE3,
  TIRE4,
} tire_e;

typedef enum {
  NORMAL_ITEM,
  KEY_ITEM,
  WEAPON,
  ARMOR,
} item_type_e;

typedef struct {
  item_list_e il;
  tire_e tire;
  item_type_e it;
  char item_name[NAME_MAX];
  char item_describe[ITEM_DISCRIBE_MAX];
  int32_t HP;
  int32_t MP;
  int32_t ATT;
  int32_t DEF;
  int32_t WIS;
  int32_t SPD;
} item_t;

// SCENE
typedef enum {
  SCENE_GAME_START,
  SCENE_PROLOGUE,
  SCENE_MENU_MAIN_INCITY,
  SCENE_MENU_MAIN_ONROAD,
  SCENE_MENU_MAIN_DUNGEON,
  SCENE_MENU_GLOBAL_MAP,
  SCENE_MENU_LOACL_MAP,
  SCENE_MENU_STATUS,
  SCENE_MENU_ITEM,
  SCENE_MENU_EXPLORER,
  SCENE_MENU_EXPLORER_ITEMSHOP,
  SCENE_MENU_EXPLORER_BLACKSMITH,
  SCENE_MENU_EXPLORER_GUILD,
  SCENE_MENU_EXPLORER_SOUTHPORT_DUNGEON,
  SCENE_MENU_MOVE,
  SCENE_MENU_MOVE_EAST,
  SCENE_MENU_MOVE_WEST,
  SCENE_MENU_MOVE_SOUTH,
  SCENE_MENU_MOVE_NORTH,
  SCENE_DUNGEON_MAOU_CASTLE,
} scene_e;

typedef struct {
  uint8_t num;
  scene_e next_s;
  char str[NAME_MAX];
} action_t;

// PLAYER
typedef struct player_status {
  uint16_t MAX_HP;
  uint16_t HP;
  uint16_t MAX_MP;
  uint16_t MP;
  uint8_t ATT;
  uint8_t DEF;
  uint8_t WIS;
  uint8_t SPD;
} player_status_t;

typedef struct player_status_buf {
  uint8_t HP;
  uint8_t MP;
  uint8_t ATT;
  uint8_t DEF;
  uint8_t WIS;
  uint8_t SPD;
} player_status_buf_t;

typedef struct player_equipment {
  item_list_e weapon;
  item_list_e armor;
} player_equipment_t;

typedef struct player {
  char name[NAME_MAX];
  global_location_tag_e gl_tag;
  local_location_tag_e ll_tag;
  uint32_t global_location[2];
  uint32_t local_location[2];
  player_status_t ps;
  player_status_buf_t psb;
  player_equipment_t pe;
  item_list_e item[PLAYER_ITEM_MAX];
} player_t;

// ENEMY
typedef struct enemy_status {
  uint16_t MAX_HP;
  uint16_t HP;
  uint16_t MAX_MP;
  uint16_t MP;
  uint8_t ATT;
  uint8_t DEF;
  uint8_t WIS;
  uint8_t SPD;
  int16_t EXP;
} enemy_status_t;

typedef struct enemy_status_buf {
  uint8_t HP;
  uint8_t MP;
  uint8_t ATT;
  uint8_t DEF;
  uint8_t WIS;
  uint8_t SPD;
  int16_t EXP;
} enemy_status_buf_t;

typedef struct enemy {
  uint8_t enemy_tire;
  uint8_t enemy_tag;
  char name[NAME_MAX];
  enemy_status_t enemy_status;
  enemy_status_buf_t enemy_status_buf;
} enemy_t;

typedef struct encount_table {
  uint8_t global_location;
  uint8_t enemy1;
  uint8_t enemy2;
  uint8_t enemy3;
} encount_table_t;

typedef enum {
  SLIME,
  METAL_SLIME,
  GOLDEN_SLIME,
  BAT,
  VAMPIRE_GENUS,
  VAMPIRE,
  WYVERN,
  DRAGON,
  CRYSTAL_DRAGON,
} enemy_e;

// DataTable
typedef struct data_table {
  player_t p_data;
  enemy_t e_table;
  item_t i_table[ID_MAX];
  local_map_t lm_table[7];
  global_map_t gm_table[2];
  scene_e next_s;
} data_table_t;

#endif  // DATA_TABLE