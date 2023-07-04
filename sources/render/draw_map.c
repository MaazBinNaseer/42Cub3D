#include "../../inc/Cube3D.h"

void draw_box_wall(t_mlx *mlx, int x, int y, int size)
{
    int i, j;

    int black = 0x000000;
    int white = 0xFFFFFF; 

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1)
                mlx_pixel_put(mlx->mlx, mlx->window, x + i, y + j, black);
            else
                mlx_pixel_put(mlx->mlx, mlx->window, x + i, y + j, white);
        }
    }
}
void draw_box(t_mlx *mlx, int x, int y, int color, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        mlx_pixel_put(mlx->mlx, mlx->window, x + i, y, color); // Top edge
        mlx_pixel_put(mlx->mlx, mlx->window, x + i, y + size - 1, color); // Bottom edge
        mlx_pixel_put(mlx->mlx, mlx->window, x, y + i, color); // Left edge
        mlx_pixel_put(mlx->mlx, mlx->window, x + size - 1, y + i, color); // Right edge
    }
}

void draw_player(t_mlx *mlx, t_map *map, float player_x, float player_y)
{
    int color = 0xFFFF0000;
    int player_size = 100;

    player_x = map->player_position.y * player_size;
    player_y = map->player_position.x * player_size;

    for (float px = player_x; px < player_x + player_size; px++)
    {
        for (float py = player_y; py < player_y + player_size; py++)
        {
            mlx_pixel_put(mlx->mlx, mlx->window, px, py, color);
        }
    }
}



void draw_map(t_mlx *mlx, t_map *map)
{
    int i, j;
    int size = 100;
    int color;

    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->coloumns; j++) {
            if (map->map[i][j] == '0') {
                color = 0x000000;
                draw_box(mlx, j * size, i * size, color, size);
            } else if (map->map[i][j] == '1') {
                color = 0xFFFFFF;
                draw_box(mlx, j * size, i * size, color, size); 
            } else if (map->map[i][j] == 'S')
            {
                 color = 0x000000; 
                draw_box(mlx, j * size, i * size, color, size);
                draw_player(mlx, map, i * size, j * size);
            }
        }
    }
}


/*
todo: Find a way to print an image on the screen 
*/
void intialize_images(t_map *map, t_im *img, t_mlx *mlx)
{
    int width = 64;
    img->wall = mlx_xpm_file_to_image(mlx->mlx, "./xpms/wall_2.xpm", &width, &width);
    img->path = mlx_xpm_file_to_image(mlx->mlx, "./xpms/path.xpm",&width, &width);
    map->img = img;
    if(img->wall == NULL)
        {
            printf(RED "Intialize fail\n" RESET);
            exit(1);
        }
}