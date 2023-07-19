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
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */
/* --------------------------------------------------------
# ------------------------- STRUCTS ------------------
---------------------------------------------------------- */

typedef struct s_map
{
    char 		**map;
    int 		rows;
    int 		coloumns;
    int 		player;
    t_pos 		player_position;
} t_map;

typedef	enum				e_error
{
	SUCCESS,
	INVALID_ARG,
	WRONG_MAP,
	WRONG_INPUT,
	MALLOC_FAIL,
	IMG_FAIL,
	OPEN_ERR,
	MLX_FAIL,
	WRITE_FAIL,
	WRONG_TEXTURE
}							t_error;

typedef struct s_config_properties
{
    char 	*north_texture;
    char 	*south_texture;
    char 	*west_texture;
    char 	*east_texture;
    char 	*floor_texture;
    char 	*ceiling_texture;
    int 	map_set;
} t_config_properties;

typedef struct s_pos
{
    float 		x;
    float 		y;
    double 		dx;
    double 		dy;
    float 		player_direction;
} t_pos;

typedef struct				s_img
{
	void					*img_ptr;
	int						*img_data;
	int						bpp;
	int						size_line;
	int						endian;
	int						width;
	int						height;
}							t_img;

typedef union				u_colour
{
	unsigned int			all;
	char					tab[4];
	t_rgb					rgb;
}							t_colour;

typedef struct				s_rgb
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
	unsigned char			a;
}							t_rgb;


typedef struct				s_pos
{
	double					x;
	double					y;
}							t_pos;

typedef struct				s_pos_i
{
	int						x;
	int						y;
	int						id;
}							t_pos_i;

typedef struct				s_move
{
	int						up;
	int						down;
	int						left;
	int						right;
	int						strafl;
	int						strafr;
}							t_move;

typedef struct				s_rc
{
	t_pos					plane;
	t_pos					step;
	t_pos					dir;
	t_pos_i					textur;
	t_pos					rpos;
	t_pos					rdir;
	t_pos					rdisd;
	t_pos					rdist;
	t_pos_i					rmap;
	int						wall;
	int						wstart;
	int						wend;
	double					camera;
	int						hit;
	double					rh;
	double					step_textur;
	double					textur_pos;
	double					dist;
	double					speed;
	double					*zbuffer;
	int						*sp_order;
	double					*sp_distance;

}							t_rc;

typedef	struct				s_save
{
	int						height;
	int						width;
	unsigned char			*file_header;
	unsigned char			*img_header;
	int						fd;
	int						pad;
}							t_save;

typedef	struct				s_info
{
	void					*mlx;
	void					*window;
	double					width;
	double					height;
	int						flag_save;
	int						kol_sprite;
	t_map					map;
	t_img					*img;
	t_pos					pos;
	// t_data					data;
	t_move					move;
	t_colour				colour_floor;
	t_colour				colour_ceiling;
	// t_spdata				sp;
	// t_sprite				*tab_sprite;
	// t_textur				*textur1;
	// t_textur				*textur2;
	// t_textur				*textur3;
	// t_textur				*textur4;
	// t_textur				*sprite;
	unsigned int			colour;
	t_rc					rc;
	int						error;
}							t_info;


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
int     create_window(t_info *mlx);


/* --------------------------------------------------------
*------------------------- RAYCASTING ------------------
---------------------------------------------------------- */
void	init_raycast(t_info *info, int x);
void	direction_ray(t_info *info);
void	wall_textur(t_info *info);
void	size_ray(t_info *info);



/* --------------------------------------------------------
*-------------------------UTILS --------------------------
---------------------------------------------------------- */
void    intialize_list_map(t_map *map_file);
void    initialize_list_file(t_config_properties *file);
void    intialize_list_mlx(t_info *mlx);
void    free_map(t_map *map_read);
void    print_map(t_map *map);
void    cleanup(t_config_properties *file, t_map *map);

#endif