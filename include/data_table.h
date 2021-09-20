#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include <stdint.h>
#include <stdio.h>

#define ANY_INPUT_MAX 32
#define PLAYER_NAME_MAX 32
#define ITEM_ID_MAX 255
#define IITEM_NAME_MAX 32
#define PLAYER_ITEM_MAX 20
#define ITEM_DISCRIBE_MAX 128
#define MAP_NAME_MAX 32
#define LOCAL_MAP_MAX 255
// MAP
typedef enum {
  GLOBAL_MAP = 0,
  CENTRAL = 10,
  NORTH_CITY,
  SOUTH_PORT,
  EAST_MOUNTAIN,
  WEST_DESERT,
  NORTH_MEADOW,
  CRISTAL_CAVE,
} global_location_e;

typedef enum {
  GLOBAL,
  CITY,
  ROAD,
  DUNGEON,
} map_type_e;

typedef struct {
  char name[255];
  global_location_e gl;
  map_type_e mt;
  uint8_t map_field[10][11];
} map_t;

// ITEM
typedef enum {
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
  char item_name[IITEM_NAME_MAX];
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
  START_SCENE,
  MAIN_MENU,
  MAOU_CASTLE_SCENE,
} scene_e;

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
  char name[PLAYER_NAME_MAX];
  global_location_e gl;
  uint8_t local_location;
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
  char name[PLAYER_NAME_MAX];
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
  item_t i_table[ITEM_ID_MAX];
  map_t m_table[8];
  global_location_e gl;
  uint8_t local_map[LOCAL_MAP_MAX];
  scene_e next_s;
} data_table_t;

#endif  // DATA_TABLE