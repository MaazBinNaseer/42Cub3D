#include "../../inc/Cube3D.h"

static void	add_until_wall(t_rays *ray, t_map *map, float ray_offset[2])
{
	int	x;
	int	y;

	while (true)
	{
		x = ray->end[0] / 32;
		y = ray->end[1] / 32;
		if (x < 0 || y < 0 || x >= map->rows
			|| y >= map->coloumns|| map->map[y][x] == '1')
			break ;
		ray->end[0] += ray_offset[0];
		ray->end[1] += ray_offset[1];
	}
}

static float	rays_horizontal(t_rays *ray, t_map *map, int x, int y)
{
	float	tan_v;
    float ray_offset[2] = {0.0f, 0.0f};

	tan_v = -1 / tan(ray->ra);
	if (ray->ra < M_PI && ray->ra > 0)
	{
		ray->end[1] = y / 32 * 32 + 32;
		ray->end[0] = (y - ray->end[1]) * tan_v + x;
		ray_offset[1] = 32;
	}
	else if (ray->ra > M_PI && ray->ra != M_PI * 2)
	{
		ray->end[1] = y / 32 * 32 - 0.0001f;
		ray->end[0] = (y - ray->end[1]) * tan_v + x;
		ray_offset[1] = -32;
	}
	if (ray->ra == 0 || ray->ra == M_PI)
	{
		ray->end[0] = x;
		ray->end[1] = y;
		return (MAXFLOAT);
	}
	ray_offset[0] = -ray_offset[1] * tan_v;
	add_until_wall(ray, map, ray_offset);
	return (sqrtf(powf((ray->end[0] - x), 2) + powf((ray->end[1] - y), 2)));
}

static float	rays_vertical(t_rays *ray, t_map *map, int x, int y)
{
	float	tan_v;
	 float ray_offset[2] = {0.0f, 0.0f};

	tan_v = -tan(ray->ra);
	if (ray->ra > M_PI_2 && ray->ra < (3 * M_PI_2))
	{
		ray->end[0] = x / 32 * 32 - 0.0001f;
		ray_offset[0] = -32;
	}
	else if (ray->ra < M_PI_2 || ray->ra > (3 * M_PI_2))
	{
		ray->end[0] = x / 32 * 32 + 32;
		ray_offset[0] = 32;
	}
	ray->end[1] = (x - ray->end[0]) * tan_v + y;
	if (ray->ra == M_PI_2 || ray->ra == (3 * M_PI_2))
	{
		ray->end[0] = x;
		ray->end[1] = y;
		return (MAXFLOAT);
	}
	ray_offset[1] = -ray_offset[0] * tan_v;
	add_until_wall(ray, map, ray_offset);
	return (sqrtf(powf((ray->end[0] - x), 2) + powf((ray->end[1] - y), 2)));
}

float	calc_rays(t_rays *ray, t_map *map, int x, int y)
{
	float	dist_h;
	float	dist_v;
	int		end_h[2];

	ray->start[0] = x;
	ray->start[1] = y;
	dist_h = rays_horizontal(ray, map, x, y);
	end_h[0] = ray->end[0];
	end_h[1] = ray->end[1];
	ray->dir = 'S';
	dist_v = rays_vertical(ray, map, x, y);
	if (dist_h < dist_v)
	{
		ray->end[0] = end_h[0];
		ray->end[1] = end_h[1];
		ray->dir = 'S';
		return (dist_h);
	}
	return (dist_v);
}

#define TWO_PI 6.28318530718 // 2*PI
#define NUM_RAYS 9 // number of rays to cast


#define SCREEN_HEIGHT 1200
#define SCREEN_WIDTH 1400
#define WALL_COLOR 0xFFF000  // white color
#define WALL_HEIGHT_CONSTANT SCREEN_HEIGHT * 8 // adjust this as necessary

void draw_walls(t_mlx *mlx, t_rays *ray, t_map *map, int x, int y, int ray_index)
{
    // calculate distances and find shortest one
    float shortest_distance = calc_rays(ray, map, x, y);
    
    // correct the fishbowl effect
    shortest_distance = shortest_distance * cos(map->player_position.player_direction - ray->ra);  // changed order

    // calculate wall height and top/bottom positions
    int wallHeight = WALL_HEIGHT_CONSTANT / (shortest_distance);
    int wallTop = (SCREEN_HEIGHT - wallHeight) / 2;
    int wallBottom = wallTop + wallHeight;
    // draw the wall slice
    mlx_line(mlx, mlx->offscreen_buffer, ray_index, wallTop, ray_index, wallBottom, WALL_COLOR);
}

void draw_rays(t_mlx *mlx, t_rays *ray, t_map *map, int x, int y, float player_angle)
{
    // calculate the angle increment for each ray
    float angle_increment = (60.0 * PI / 180.0) / SCREEN_WIDTH;

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        // calculate the direction of this ray, starting from player_angle - 30 degrees and going up to player_angle + 30 degrees
        ray->ra = player_angle - (30.0 * PI / 180.0) + i * angle_increment;

        // make sure ray_angle is between 0 and TWO_PI
        if (ray->ra < 0) ray->ra += TWO_PI;
        if (ray->ra > TWO_PI) ray->ra -= TWO_PI;

        // draw walls for this ray
        draw_walls(mlx, ray, map, x, y, i);
    }
}





   // printf("Shortest distance to wall : %0.2f  and the position of the player x: %0.2f and y: %0.2f \n", lol, map->player_position.x, map->player_position.y);


// float shortest_distance(t_rays *ray, t_map *map, int x, int y)
// {
//     float   distance_H;
//     float   distance_V;
//     int     end_h[2];

//     ray->start[0] = x;
//     ray->start[1] = y;
//     distance_H = rays_horizontal(ray, map, x, y);
//     end_h[0] = ray->end[0];
//     end_h[1] = ray->end[1];
//     ray->dir = 'S';
//     // distance_V = rays_vertical(ray, map, x, y);
//     if(distance_H < distance_V)
//     {
//         ray->end[0] = end_h[0];
//         ray->end[1] = end_h[1];
//         ray->dir = 'E';
//         return (distance_H);
//     }
//     return (distance_V);
// }


// int is_valid_tile(t_map *map, int x, int y) {
//     int tileX = x / 64;
//     int tileY = y / 64;

//     if (tileX < 0 || tileY < 0 || tileX >= map->coloumns || tileY >= map->rows)
//         return 0;

//     if (map->map[tileY][tileX] == '1')
//         return 0; 
//     return 1;  
// }

// float rays_horizontal(t_mlx *mlx, t_rays *ray, t_map *map, float x, float y, float angle) {
//     int ay;
//     int ax;
//     float ra = angle;  // Using the passed-in angle here
//     (void)mlx;
//     if (ra > 0 && ra < PI)
//         ay = roundf(y / 64.0) * 64 - 1;
//     else
//         ay = roundf(y / 64.0) * 64 + 64;

//     if (ra == 0 || roundf(ra) == roundf(PI))
//         ra = ra + 0.35;
//     else if (roundf(ra) == roundf(6.28))
//         ra = 0.35;

//     ax = x + roundf((y - ay) / tan(ra));  // Using the local ra variable here

//     int Cx;
//     int Cy;
//     while (1) {
//         if (ra >= 0 && ra < PI)  // And here
//             ray->offset[0] = -64;
//         else
//             ray->offset[0] = 64;
//         ray->offset[1] = roundf(64 / tan(ra));  // And here
//         Cx = ax + ray->offset[1];
//         Cy = ay + ray->offset[0];
//         if (!is_valid_tile(map, Cx, Cy))
//             break;
//         ax = Cx;
//         ay = Cy;
//     }

//     // Calculate the exact intersection point with the wall (if needed)
//     if (is_valid_tile(map, Cx, Cy)) {
//         float dist_to_horizontal = fabs((Cy - y) / sin(ra));
//         float dist_to_vertical = fabs((Cx - x) / cos(ra));

//         if (dist_to_horizontal < dist_to_vertical) {
//             Cx = roundf(x + dist_to_horizontal * cos(ra));
//             Cy = roundf(y + dist_to_horizontal * sin(ra));
//         } else {
//             Cx = roundf(x + dist_to_vertical * cos(ra));
//             Cy = roundf(y + dist_to_vertical * sin(ra));
//         }
//     }

//     float ray_length = sqrtf(powf((Cx - x), 2) + powf((Cy - y), 2));
//     // int color = 0x00FF00;
//     // mlx_line(mlx, mlx->offscreen_buffer, x, y, Cx, Cy, color);
//     return ray_length;
// }


// float rays_vertical(t_mlx *mlx, t_rays *ray, t_map *map, float x, float y, float angle) {
//     int ax;
//     int ay;
//     float ra = angle;  // Using the passed-in angle here
//     (void)mlx;
//     if (ra > PI_2 && ra < 3 * PI_2)
//         ax = roundf(x / 64.0) * 64 - 1;
//     else
//         ax = roundf(x / 64.0) * 64 + 64;

//     if (ra == 0 || roundf(ra) == roundf(PI))
//         ra = ra + 0.35;
//     else if (roundf(ra) == roundf(6.28))
//         ra = 0.35;

//     ay = y + roundf((x - ax) / tan(ra));  // Using the local ra variable here

//     int Cx;
//     int Cy;
//     while (1) {
//         if (ra > PI_2 && ra < 3 * PI_2)  // And here
//             ray->offset[1] = -64;
//         else
//             ray->offset[1] = 64;
//         ray->offset[0] = roundf(64 / tan(ra));  // And here
//         Cx = ax + ray->offset[1];
//         Cy = ay + ray->offset[0];
//         if (!is_valid_tile(map, Cx, Cy))
//             break;
//         ax = Cx;
//         ay = Cy;
//     }

//     // Calculate the exact intersection point with the wall (if needed)
//     if (is_valid_tile(map, Cx, Cy)) {
//         float dist_to_vertical = fabs((Cx - x) / cos(ra));
//         float dist_to_horizontal = fabs((Cy - y) / sin(ra));

//         if (dist_to_vertical < dist_to_horizontal) {
//             Cx = roundf(x + dist_to_vertical * cos(ra));
//             Cy = roundf(y + dist_to_vertical * sin(ra));
//         } else {
//             Cx = roundf(x + dist_to_horizontal * cos(ra));
//             Cy = roundf(y + dist_to_horizontal * sin(ra));
//         }
//     }

//     float ray_length = sqrtf(powf((Cx - x), 2) + powf((Cy - y), 2));
//     // int color = 0xFFA500;
//     // mlx_line(mlx, mlx->offscreen_buffer, x, y, Cx, Cy, color);
//     return ray_length;
// }