/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuhamma <smuhamma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:21:48 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/02 14:21:50 by smuhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				init_save(t_info *info, int argc, char *s)
{
	if (argc == 3 && (ft_strncmp(s, "--save", ft_strlen(s)) == 0))
		info->flag_save = 1;
	else if (argc == 3)
		return (INVALID_ARG);
	return (SUCCESS);
}

static int		init_texture(t_info *info)
{
	if ((info->textur1 = fn_new_textur(info, info->data.no)) == NULL)
		return (WRONG_TEXTURE);
	if ((info->textur2 = fn_new_textur(info, info->data.so)) == NULL)
		return (WRONG_TEXTURE);
	if ((info->textur3 = fn_new_textur(info, info->data.we)) == NULL)
		return (WRONG_TEXTURE);
	if ((info->textur4 = fn_new_textur(info, info->data.ea)) == NULL)
		return (WRONG_TEXTURE);
	if ((info->sprite = fn_new_textur(info, info->data.spr)) == NULL)
		return (WRONG_TEXTURE);
	return (SUCCESS);
}

static int		check_tab2(char *tab)
{
	int i;
	int size;

	i = 0;
	size = ft_strlen(tab);
	while (i < size)
	{
		if (!ft_isdigit(tab[i]) && tab[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int		get_resolution(t_info *info)
{
	char	**tab;
	int		l;

	l = -1;
	if ((info->error = check_resolut(info, &tab)) != SUCCESS)
		return (info->error);
	if (tab_size(tab) == 2)
	{
		while (++l < 2)
			if (!check_tab2(tab[l]))
				return (WRONG_INPUT);
		if (tab[0])
			{
				info->width = ft_atoi(tab[0]);
				printf("info->width: %f\n", info->width);
			}
		if (tab[1])
			info->height = ft_atoi(tab[1]);
	}
	else
		return (WRONG_INPUT);
	ft_tabdel((void **)tab);
	if (!info->width || !info->height || info->width < 0 || info->height < 0)
		return (WRONG_INPUT);
	check_resolut2(info);
	return (SUCCESS);
}

int				init_var(t_info *info, char *s)
{
	info->raycast.speed = 0.05;
	if ((info->error = get_map(info, s)) != SUCCESS)
		return (info->error);
	if ((info->error = parse_map(info)) != SUCCESS)
		return (info->error);
	if ((info->error = get_colour(&info->colour_floor,
		info->data.f)) != SUCCESS)
		return (info->error);
	if ((info->error = get_colour(&info->colour_ceiling,
		info->data.c)) != SUCCESS)
		return (info->error);
	if ((info->error = get_resolution(info)) != SUCCESS)
		return (info->error);
	if ((info->error = init_info_pos(info)) != SUCCESS)
		return (info->error);
	if (!(info->raycast.zbuffer = malloc(sizeof(double) * info->width)))
		return (MALLOC_FAIL);
	if ((info->error = init_texture(info)) != SUCCESS)
		return (info->error);
	return (SUCCESS);
}
