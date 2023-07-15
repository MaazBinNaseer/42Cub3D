#include "../../inc/Cube3D.h"

void mlx_line(t_mlx *mlx, void *offscreen_buffer, int x1, int y1, int x2, int y2, int color)
{
    (void)offscreen_buffer;
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

void draw_direction(t_mlx *mlx, t_map *map, float player_x, float player_y, int size)
{
    float player_angle = map->player_position.player_direction;

    // Calculate end point of the direction line
    // The line length could be adjusted as needed
    float end_x = player_x + cos(player_angle) * size;
    float end_y = player_y + sin(player_angle) * size;

    // Draw the line
    int color = 0x800000; // Choose the color as you like
    mlx_line(mlx, mlx->offscreen_buffer, player_x, player_y, end_x, end_y, color);
}



void draw_box(t_all *all, int start_x, int start_y, int color, int size)
{
    int x, y;

    for (y = start_y; y < start_y + size; y++) {
        for (x = start_x; x < start_x + size; x++) {
            my_mlx_pixel_put(all->mlx_list, x, y, color);
        }
    }
}

void draw_player(t_all *all, float player_x, float player_y, int size)
{
    t_rays *rays = malloc(sizeof(t_rays));
    initialize_rays(rays);
    int color = 0xFFFF0000;
    int player_size = 64;
    player_x = player_x * size ; 
    player_y = player_y * size;
    for (float px = player_x - player_size / 2.0; px < player_x + player_size / 2.0; px++)
    {
        for (float py = player_y - player_size / 2.0; py < player_y + player_size / 2.0; py++)
        {
            mlx_pixel_put(all->mlx_list->mlx, all->mlx_list->window, px, py, color);
            // my_mlx_pixel_put(mlx, px, py, color);
        }
    }
    draw_direction(all->mlx_list, all->map_list, player_x, player_y, size);
    draw_rays(rays, all->mlx_list, all->map_list, player_x, player_y);
}

void draw_grid(t_all *all, t_map *map, void *offscreen_buffer, int size)
{
    int i, j;
    int color = 0x0000FF;

    for (i = 0; i <= map->rows; i++) {
        mlx_line(all->mlx_list, offscreen_buffer, 0, i * size, map->coloumns * size, i * size, color); // Horizontal lines
    }
    for (j = 0; j <= map->coloumns; j++) {
        mlx_line(all->mlx_list, offscreen_buffer, j * size, 0, j * size, map->rows * size, color); // Vertical lines
    }
}

void draw_map(void *offscreen_buffer, t_map *map, t_all *all)
{
    int i, j;
    int size = 64; // This is the unit of the map
    int color;

    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->coloumns; j++) {
            if (map->map[i][j] == '0') {
                color = 0x000000;
                draw_box(all, j * size, i * size, color, size);
            } else if (map->map[i][j] == '1') { // '1' represents walls
                color = 0xFFFFFF;
                draw_box(all, j * size, i * size, color, size);
            } else if (map->map[i][j] == 'S') {
                color = 0x000000;
                printf("The value of the player is at (i: %d, j: %d)\n", i, j);
                draw_box(all, j * size, i * size, color, size);
                draw_player(all, i, j, size);
            }
        }
    }
    draw_grid(all, map, offscreen_buffer, size);
}



   // float center_x = player_x + player_size / 2;
    // float center_y = player_y + player_size / 2;
    // int line_length = 125;
    // int line_end_x = center_x + line_length * cos(map->player_position.player_direction);
    // int line_end_y = center_y + line_length * sin(map->player_position.player_direction);
    // mlx_line(mlx, center_x, center_y, line_end_x, line_end_y, 0x00FF00);