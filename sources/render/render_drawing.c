#include "../../inc/Cube3D.h"

void mlx_line(t_info *mlx, void *offscreen_buffer, int x1, int y1, int x2, int y2, int color)
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

void		put_pixel(t_img *img, unsigned int colour, int p_x, int p_y)
{
	if (p_y >= img->height || p_x >= img->width || p_x < 0 || p_y < 0)
		return ;
	img->img_data[p_y * img->width + p_x] = colour;
}

static int	display_col(t_info *info, int x)
{
	int	y;

	y = 0;
	while (y < info->rc.wstart)
		put_pixel(info->img, info->colour_ceiling.all, x, y++);
	while (y >= info->rc.wstart && y <= info->rc.wend)
	{
		info->rc.textur.y = (int)info->rc.textur_pos & (64 - 1);
		info->rc.textur_pos += info->rc.step_textur;
		pixel_colour(info);
		put_pixel(info->img, info->colour, x, y);
		y++;
	}
	while (y < info->height)
		put_pixel(info->img, info->colour_floor.all, x, y++);
	return (SUCCESS);
}

int			fn_display_screen(t_info *info)
{
	int	x;

	x = 0;
	while (x < info->width - 1)
	{
		init_raycast(info, x);
		direction_ray(info);
		hit_ray(info);
		size_ray(info);
		wall_textur(info);
		if ((info->error = display_col(info, x++)))
			return (info->error);
		info->rc.zbuffer[x] = info->rc.dist;
	}
	if ((info->error = init_sprite(info)))
		return (info->error);
	return (SUCCESS);
}

