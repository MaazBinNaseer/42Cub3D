#include "../../inc/Cube3D.h"

/*
My keyboard for ESC is 79822912 for some damn reason
*/

int close_windows(t_mlx *mlx, t_map *map, int keycode)
{
    printf("Keycode: %d\n", keycode);

    // Access the t_map data
    printf("Map rows: %d\n", map->rows);
    printf("Map columns: %d\n", map->coloumns);

    mlx_destroy_window(mlx->mlx, mlx->window);
    return (0);
}

int create_window(t_mlx *mlx, t_map *map)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return -1;
    (void )map;
    mlx->window = mlx_new_window(mlx->mlx, 1080, 1000 ,"HELLO WORLD");
    if (!mlx->window)
        return -1;
    // draw_line(mlx, 30, 40, 50, 60);
    draw_map(mlx, map);
    mlx_hook(mlx->window, 17, 0, close_windows, mlx);
    return (0);
}

