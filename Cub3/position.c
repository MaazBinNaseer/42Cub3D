/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:51:53 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/07/19 18:51:54 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		init_pos(t_info *info)
{
	if (info->map.player == 'N')
	{
		info->rc.dir.y = -1;
		info->rc.plane.x = -0.80;
	}
	if (info->map.player == 'S')
	{
		info->rc.dir.y = 1;
		info->rc.plane.x = 0.80;
	}
	if (info->map.player == 'E')
	{
		info->rc.dir.x = 1;
		info->rc.plane.y = -0.80;
	}
	if (info->map.player == 'W')
	{
		info->rc.dir.x = -1;
		info->rc.plane.y = 0.80;
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
