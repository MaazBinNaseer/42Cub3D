#include "cub3d.h"

static int		init_pos(t_info *info)
{
	if (info->map.player == 'N')
	{
		info->raycast.dir.y = -1;
		info->raycast.plane.x = -0.80;
	}
	if (info->map.player == 'S')
	{
		info->raycast.dir.y = 1;
		info->raycast.plane.x = 0.80;
	}
	if (info->map.player == 'E')
	{
		info->raycast.dir.x = 1;
		info->raycast.plane.y = -0.80;
	}
	if (info->map.player == 'W')
	{
		info->raycast.dir.x = -1;
		info->raycast.plane.y = 0.80;
	}
	return (SUCCESS);
}

int				init_info_pos(t_info *info)
{
	if (!(info->mlx_ptr = mlx_init()))
		return (MLX_FAIL);
	if ((info->img = fn_new_image(info, info->width, info->height)) == NULL)
		return (IMG_FAIL);
	if ((info->error = init_pos(info)) != SUCCESS)
		return (info->error);
	return (SUCCESS);
}
