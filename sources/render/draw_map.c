#include "../../inc/Cube3D.h"


/*
! Segmentation fault ---------- 
*/
void draw_map(t_mlx *mlx, t_map *map)
{
    int x, y;
    y = 0;
    // mlx->path_to_tiles = "../Xpm/1.xpm";
    int width = 10;
    // mlx->height = 10;
    mlx->img = mlx_xpm_file_to_image(mlx, "xpm/1.xpm", &width, &width);
    if(mlx->img == NULL)
        {
            printf(RED "No file\n" RESET);
            exit(1);
        }

    while (y < map->rows)
    {
        x = 0;
        while (x < map->coloumns)
        {

            // if (map->map[y][x] == '1')
            // {

            //     mlx->img = mlx_xpm_file_to_image(mlx, "1.xpm", &width, &width);
            //     mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, x, y);
            // } 
            // else if (map->map[y][x] == '0')
            //     mlx_string_put(mlx->mlx, mlx->window, x * TILE_SIZE, y * TILE_SIZE, 0x000000FF, "0"); // Draw blue square for empty spaces
            // else if (map->map[y][x] == 'S')
            //     mlx_string_put(mlx->mlx, mlx->window, x * TILE_SIZE, y * TILE_SIZE, 0x0000FF00, "S"); // Draw green square for player's position
            x++;
        }
        y++;
    }
}