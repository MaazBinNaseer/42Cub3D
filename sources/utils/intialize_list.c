#include "../../inc/Cube3D.h"

void initialize_list_file(t_config_properties *file)
{   
    file->ceiling_texture = "";
    file->east_texture = "";
    file->north_texture = "";
    file->south_texture = "";
    file->floor_texture = "";
    file->west_texture = "";
    file->map_set = 0;
}


void intialize_list_map(t_map *map_file)
{
    map_file->coloumns = 0;
    map_file->player = 0;
    map_file->rows = 0;
    map_file->player_position.x = 0;
    map_file->player_position.y = 0;
    map_file->player_position.player_direction = PI / 2;
    map_file->map = NULL;
    
}

void intialize_list_mlx(t_mlx *mlx)
{
    mlx->mlx = NULL;
    mlx->window = NULL;
    mlx->addr = NULL;
    mlx->line_length = 0;
    mlx->bits_per_pixel = 0;
    mlx->endian = 0;
}

