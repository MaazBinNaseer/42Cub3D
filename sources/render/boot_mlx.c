#include "../../inc/Cube3D.h"

/*
My keyboard for ESC is 79822912 for some damn reason
*/

int close_windows(t_mlx *mlx)
{
    mlx_destroy_window(mlx->mlx, mlx->window);
    exit(1);
    return (0);
}

int create_window(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return -1;
    mlx->window = mlx_new_window(mlx->mlx, 1800, 1080 ,"HELLO WORLD");
    if (!mlx->window)
        return -1;
    mlx_hook(mlx->window, 17, 0, close_windows, mlx);
    return (0);
}

