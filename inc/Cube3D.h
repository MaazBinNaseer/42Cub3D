#ifndef CUBE_3D_H
#define CUBE_3D_H

#include <stdio.h>
#include <stdbool.h>
#include "../sources/utils/Libft/libft.h"
#include "../sources/utils/Libft/get_next_line.h"

/* --------------------------------------------------------
# ------------------------- COLORS ------------------
---------------------------------------------------------- */
#define RED "\033[1;31m"
#define RESET "\033[0m"

/* --------------------------------------------------------
# ------------------------- STRUCTS ------------------
---------------------------------------------------------- */

typedef struct s_config_properties
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    char *floor_texture;
    char *ceiling_texture;
    int map_set;
} t_config_properties;


typedef struct s_pos
{
    int x;
    int y;
} t_pos;

typedef struct s_map
{
    char **map;
    int rows;
    int coloumns;
    int player;
    t_pos player_position;
} t_map;



/* --------------------------------------------------------
*------------------------- CONFIG FILE ------------------
---------------------------------------------------------- */
int read_config_file(const char *filename, t_config_properties *file, t_map *map);
// int read_config_file(const char *filename, t_config_properties *file);
bool set_order_of_file(const char* filename);



/* --------------------------------------------------------
*------------------------- MAP READING ------------------
---------------------------------------------------------- */
// char *read_map(const char *filename, t_map *map);
// void read_map(int fd, const char *filename, t_map *map);
void read_map(int fd, t_map *map, char *first_map_line);
int check_map_is_surrounded_rows(t_map *map_read);
bool check_for_zeros_surrounded_map(t_map *map_read);
int check_map_is_surrounded_columns(t_map *map_read);
int get_player_position(t_map *map_read);
bool check_for_error_map(t_map *map_read);
int check_map(t_map *map_check);

/* --------------------------------------------------------
*-------------------------UTILS --------------------------
---------------------------------------------------------- */
void free_map(t_map *map_read);
void print_map(t_map *map);


#endif