#include "../../inc/Cube3D.h"

void mlx_line(t_mlx *mlx, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (x1 != x2 || y1 != y2)
    {
        mlx_pixel_put(mlx->mlx, mlx->window, x1, y1, color);
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
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
    int line_length = 200; // Adjust this value as needed
    int line_end_x = player_x + line_length * cos(map->player_position.player_direction);
    int line_end_y = player_y + line_length * sin(map->player_position.player_direction);
    mlx_line(mlx, player_x, player_y, line_end_x, line_end_y, 0x00FF00); // Line color is green
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