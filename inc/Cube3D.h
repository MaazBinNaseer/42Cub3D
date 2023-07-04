#ifndef CUBE_3D_H
#define CUBE_3D_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../sources/utils/Libft/libft.h"
#include "../sources/utils/Libft/get_next_line.h"
#include "../mlx_linux/mlx.h"
#include "../mlx_linux/mlx_int.h"

/* --------------------------------------------------------
# ------------------------- COLORS ------------------
---------------------------------------------------------- */
#define RED "\033[1;31m"
#define YELL "\033[1;33m"
#define GRN  "\033[1;32m"
#define MAG "\033[1;38;5;13m"
#define RESET "\033[0m"

/* ------------------------------------------------------
# ----------------- MATH && MAP MACROS ------------------
--------------------------------------------------------*/
#define PI 3.14159
#define TILE_SIZE 10
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
    float x;
    float y;
    float dx;
    float dy;
} t_pos;

typedef struct s_im
{
    void *wall;
    void *path;
} t_im;

typedef struct s_map
{
    char **map;
    int rows;
    int coloumns;
    int player;
    t_im *img;
    t_pos player_position;
} t_map;


typedef struct s_mlx
{
    void    *mlx;
    void	*img;
    void    *window;
	char	*addr;
	int		width;
	int		height;
    char    *path_to_tiles;
	int		endian;
}   t_mlx;

typedef struct s_all
{
    t_mlx *mlx_list;
    t_map *map_list;
} t_all;

/* --------------------------------------------------------
*------------------------- CONFIG FILE ------------------
---------------------------------------------------------- */
void read_config_file(const char *filename, t_config_properties *file, t_map *map);
bool set_order_of_file(const char* filename);


/* --------------------------------------------------------
*------------------------- MAP READING ------------------
---------------------------------------------------------- */
void read_map(int fd, t_map *map, char *first_map_line);
int check_map_is_surrounded_rows(t_map *map_read);
bool check_for_zeros_surrounded_map(t_map *map_read);
int check_map_is_surrounded_columns(t_map *map_read);
float get_player_position(t_map *map_read);
bool check_for_error_map(t_map *map_read);
int check_map(t_map *map_check);


/* --------------------------------------------------------
*------------------------- RENDERING ------------------
---------------------------------------------------------- */
int create_window(t_mlx *mlx);
void intialize_images(t_map *map, t_im *img, t_mlx *mlx);
void draw_map(t_mlx *mlx, t_map *map);
void draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2);
float key_hook(int keycode, t_all *all);
void draw_player(t_mlx *mlx, t_map *map, float player_x, float player_y);
/* --------------------------------------------------------
*-------------------------UTILS --------------------------
---------------------------------------------------------- */
void intialize_list_map(t_map *map_file);
void initialize_list_file(t_config_properties *file);
void intialize_all(t_all *all);
void free_map(t_map *map_read);
void print_map(t_map *map);
void cleanup(t_config_properties *file, t_map *map);

#endif