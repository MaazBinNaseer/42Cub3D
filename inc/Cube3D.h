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
    // int player_position; 
    int player;
    t_pos player_position;
} t_map;


/* --------------------------------------------------------
*------------------------- MAP READING ------------------
---------------------------------------------------------- */
// char *read_map(const char *filename, t_map *map);
int read_map(const char *filename, t_map *map);
int check_map_is_surrounded_rows(t_map *map_read);
int check_map_is_surrounded_columns(t_map *map_read);
int get_player_position(t_map *map_read);
bool check_for_error_map(t_map *map_read);
int check_map(t_map *map_check);

/* --------------------------------------------------------
*-------------------------UTILS --------------------------
---------------------------------------------------------- */




#endif