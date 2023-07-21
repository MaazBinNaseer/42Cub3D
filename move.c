#include "cub3d.h"

static void	fn_rotate(t_info *info, int advance)
{
	double	dir;
	double	plane;

	dir = info->raycast.dir.x;
	plane = info->raycast.plane.x;
	info->raycast.dir.x = info->raycast.dir.x * cos(advance * 0.05)
		- info->raycast.dir.y * sin(advance * 0.05);
	info->raycast.dir.y = dir * sin(advance * 0.05)
		+ info->raycast.dir.y * cos(advance * 0.05);
	info->raycast.plane.x = info->raycast.plane.x * cos(advance * 0.05)
		- info->raycast.plane.y * sin(advance * 0.05);
	info->raycast.plane.y = plane * sin(advance * 0.05)
		+ info->raycast.plane.y * cos(advance * 0.05);
}

static void	up_down(t_info *info)
{
	if (info->move.up == 1)
	{
		if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x +
		info->raycast.dir.x * info->raycast.speed)] == '0')
			info->pos.x += info->raycast.dir.x * info->raycast.speed;
		if (info->map.tab_map[(int)(info->pos.y + info->raycast.dir.y *
			info->raycast.speed)][(int)(info->pos.x)] == '0')
			info->pos.y += info->raycast.dir.y * info->raycast.speed;
	}
	if (info->move.down == 1)
	{
		if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x -
		info->raycast.dir.x * info->raycast.speed)] == '0')
			info->pos.x -= info->raycast.dir.x * info->raycast.speed;
		if (info->map.tab_map[(int)(info->pos.y - info->raycast.dir.y *
			info->raycast.speed)][(int)(info->pos.x)] == '0')
			info->pos.y -= info->raycast.dir.y * info->raycast.speed;
	}
}

static void	straf(t_info *info)
{
	if (info->move.strafr == 1)
	{
		if (info->map.tab_map[(int)(info->pos.y - info->raycast.dir.x *
			info->raycast.speed)][(int)(info->pos.x)] == '0')
			info->pos.y -= info->raycast.dir.x * info->raycast.speed;
		if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x
			+ info->raycast.dir.y * info->raycast.speed)] == '0')
			info->pos.x += info->raycast.dir.y * info->raycast.speed;
	}
	if (info->move.strafl == 1)
	{
		if (info->map.tab_map[(int)(info->pos.y + info->raycast.dir.x *
			info->raycast.speed)][(int)(info->pos.x)] == '0')
			info->pos.y -= -info->raycast.dir.x * info->raycast.speed;
		if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x -
			info->raycast.dir.y * info->raycast.speed)] == '0')
			info->pos.x -= info->raycast.dir.y * info->raycast.speed;
	}
}

void		fn_move(t_info *info)
{
	if (info->move.up == 1 || info->move.down == 1)
		up_down(info);
	if (info->move.strafr == 1 || info->move.strafl == 1)
		straf(info);
	if (info->move.left == 1)
		fn_rotate(info, 1);
	if (info->move.right == 1)
		fn_rotate(info, -1);
}
