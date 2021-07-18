#ifndef DATA_TABLE
#define DATA_TABLE

#include <stdint.h>
#include <stdio.h>

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
  uint8_t weapon;
  uint8_t armor;
} player_equipment_t;

typedef struct player_info {
  char name[32];
  uint8_t global_location;
  uint8_t local_location;
  player_status_t player_status;
  player_status_buf_t player_status_buf;
  player_equipment_t player_equipment;
  uint8_t item[20];
} player_info_t;

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

typedef struct enemy_table {
  uint8_t enemy_tire;
  uint8_t enemy_tag;
  char name[32];
  enemy_status_t enemy_status;
  enemy_status_buf_t enemy_status_buf;
} enemy_table_t;

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

// ITEM
typedef enum {
  HP_PORTION = 0,
  MP_PORTION,
  IRON_SWORD,
  MITHRIL_SWORD,
  CRYSTAL_SWORD,
  LEATHRE_ARMOR,
  MITHRIL_ARMOR,
  CRYSTAL_ARMOR,
} item_list_e;

typedef enum {
  TIRE1,
  TIRE2,
  TIRE3,
  TIRE4,
  TIRE5,
} tire_e;

typedef enum {
  NORMAL_ITEM,
  KEY_ITEM,
  WEAPON,
  ARMOR,
} item_type_e;

typedef struct {
  uint8_t item_tire;
  uint8_t item_tag;
  uint8_t item_type;
  char item_name[32];
  char item_describe[128];
  uint16_t HP;
  uint16_t MP;
  uint8_t ATT;
  uint8_t DEF;
  uint8_t WIS;
  uint8_t SPD;
} item_info_t;

// MAP
typedef struct local_map {
  char map_name[32];
  uint8_t map_tag;
  uint8_t map_type;
  uint8_t* field;
} local_map_t;

typedef enum{
  CENTRAL = 0,
  NORTH_CITY,
  SOUTH_PORT,
  EAST_MOUNTAIN,
  WEST_DESERT,
  NORTH_MEADOW,
  CRISTAL_CAVE,
}map_id_e;

typedef enum{
  CITY = 0,
  DUNGEON = 1,
}map_type_e;

typedef struct data_table {
  player_info_t player_info;
  enemy_table_t enemy_table;
  local_map_t local_map;
} data_table_t;

#endif  // DATA_TABLE