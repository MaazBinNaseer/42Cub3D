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