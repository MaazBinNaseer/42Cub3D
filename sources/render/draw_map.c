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
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            mlx_pixel_put(mlx->mlx, mlx->window, x + i, y + j, color);
        }
    }
}


void draw_player(t_mlx *mlx, t_map *map, float player_x, float player_y, t_all *list)
{
    int color = 0xFFFF0000;
    int player_size = 32;
    // calculate_distance(list);
    player_x = map->player_position.x * player_size;
    player_y = map->player_position.y * player_size;

    for (float px = player_x; px < player_x + player_size; px++)
    {
        for (float py = player_y; py < player_y + player_size; py++)
        {
            mlx_pixel_put(mlx->mlx, mlx->window, px, py, color);
        }
    }
    drawRays_horizontal3D(list);
    // drawRays_vertical3D(list);
    // printf("Distance from the wall %0.2f\n", distance);
}

void draw_map(t_mlx *mlx, t_map *map, t_all *list)
{
    int i, j;
    int size = 64; // This is the unit of the map
    int color;

    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->coloumns; j++) {
            if (map->map[i][j] == '0') {
                color = 0x000000;
                draw_box(mlx, j * size, i * size, color, size);
            } else if (map->map[i][j] == '1') { // '1' represents walls
                color = 0xFFFFFF;
                draw_box(mlx, j * size, i * size, color, size);
            } else if (map->map[i][j] == 'S') {
                color = 0x000000; 
                draw_box(mlx, j * size, i * size, color, size);
                draw_player(mlx, map, i * size, j * size, list);
            }
        }
    }
    color = 0x0000FF;
    for (i = 0; i <= map->rows; i++) {
        mlx_line(mlx, 0, i * size, map->coloumns * size, i * size, color); // Horizontal lines
    }
    for (j = 0; j <= map->coloumns; j++) {
        mlx_line(mlx, j * size, 0, j * size, map->rows * size, color); // Vertical lines
    }
}

   // float center_x = player_x + player_size / 2;
    // float center_y = player_y + player_size / 2;
    // int line_length = 125;
    // int line_end_x = center_x + line_length * cos(map->player_position.player_direction);
    // int line_end_y = center_y + line_length * sin(map->player_position.player_direction);
    // mlx_line(mlx, center_x, center_y, line_end_x, line_end_y, 0x00FF00);