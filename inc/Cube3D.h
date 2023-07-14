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
#define PI 3.14159265358979323846
#define PI_2 1.57079632679489661923
#define MAXFLOAT 3.40282347e+38F
#define TILE_SIZE 64
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
    double dx;
    double dy;
    float player_direction;
} t_pos;

typedef struct s_images
{
    void *wall;
    void *path;
} t_images;

typedef struct s_rays
{
    char		dir;
	int			color;
	int			start[2];
	float		end[2];
	float		ra;
	float		dist;
    float       offset[2];
	// mlx_image_t	*img;

} t_rays;
typedef struct s_map
{
    char **map;
    int rows;
    int coloumns;
    int player;
    t_images *img;
    t_pos player_position;
} t_map;


typedef struct s_mlx
{
    void    *mlx;
    void	*img;
    void    *window;
	char	*addr;
    int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
    char    *path_to_tiles;
	int		endian;
    void    *offscreen_buffer; 
}   t_mlx;

typedef struct s_all
{
    t_mlx *mlx_list;
    t_map *map_list;
    t_rays *rays;
} t_all;

/* --------------------------------------------------------
*------------------------- CONFIG FILE ------------------
---------------------------------------------------------- */
void read_config_file(const char *filename, t_config_properties *file, t_map *map);
bool set_order_of_file(const char* filename);


/* --------------------------------------------------------
*------------------------- MAP READING ------------------
---------------------------------------------------------- */
void    read_map(int fd, t_map *map, char *first_map_line);
int     check_map_is_surrounded_rows(t_map *map_read);
bool    check_for_zeros_surrounded_map(t_map *map_read);
int     check_map_is_surrounded_columns(t_map *map_read);
float   get_player_position(t_map *map_read);
bool    check_for_error_map(t_map *map_read);
int     check_map(t_map *map_check);


/* --------------------------------------------------------
*------------------------- RENDERING ------------------
---------------------------------------------------------- */
int     create_window(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void    updatePlayerDirection(t_all *access, float rotation_angle);
void    draw_map(void *offscreen_buffer, t_map *map, t_all *all);
void    mlx_line(t_mlx *mlx, void *offscreen_buffer, int x1, int y1, int x2, int y2, int color);
void    draw_rays(t_rays *ray, t_mlx *mlx, t_map *map, int x, int y);
void    draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2);
void    draw_player(t_all *all, float player_x, float player_y, int size);
int     key_hook(int keycode, t_all *all);
void    draw_grid(t_all *all, t_map *map, void *offscreen_buffer, int size);

/* --------------------------------------------------------
*------------------------- RAYCASTING ------------------
---------------------------------------------------------- */
void cast_rays(t_mlx *mlx, t_rays *ray, t_map *map, int x, int y);




/* --------------------------------------------------------
*-------------------------UTILS --------------------------
---------------------------------------------------------- */
void    intialize_list_map(t_map *map_file);
void    initialize_list_file(t_config_properties *file);
void    intialize_all(t_all *all);
void    intialize_list_mlx(t_mlx *mlx);
void    intialize_images(t_map *map, t_images *img, t_mlx *mlx);
void    initialize_rays(t_rays *rays);
void    free_map(t_map *map_read);
void    print_map(t_map *map);
void    cleanup(t_config_properties *file, t_map *map);

#endif