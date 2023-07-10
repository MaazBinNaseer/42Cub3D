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

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int create_window(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return -1;
    mlx->window = mlx_new_window(mlx->mlx, 1500, 1200 ,"DOOM");
    if (!mlx->window)
        return -1;
    mlx_hook(mlx->window, 17, 0, close_windows, mlx);
    return (0);
}

