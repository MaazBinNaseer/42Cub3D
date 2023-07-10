#include "../../inc/Cube3D.h"

static void check_unit_wall(t_rays *ray, t_map *map, float ray_offset[2])
{
    int x;
    int y;

    while (true)
    {
        x = ray->end[0] / 32;
        y = ray->end[1] / 32;
        if(x < 0 || y < 0 || x >= map->coloumns || y >= map->rows || map->map[y][x] == '1')
            break;
        ray->end[0] += ray_offset[0];
        ray->end[1] += ray_offset[1];
    }
}

static float rays_horizontal(t_rays *ray, t_map *map, int x, int y) 
{
    float tan_inv;
    float ray_offset[2];
    float ray_length;

    ray->ra = map->player_position.player_direction - 30 * (PI / 180);
    if (ray->ra < 0)
        ray->ra += (float)PI * 2;
    tan_inv = -1 / tan(ray->ra);
    if(ray->ra < PI && ray->ra > 0)
    {
        ray->end[1] = y / 32 * 32 + 32;
        ray->end[0] = (y - ray->end[1]) * tan_inv + x;
        ray_offset[1] = 32;
    }
    else if (ray->ra > PI && ray->ra != PI * 2)
    {
        ray->end[1] = y / 32 * 32 - 0.0001f;
        ray->end[0] = (y - ray->end[1]) * tan_inv + x;
        ray_offset[1] = -32;
    }
    if (ray->ra == 0 || ray->ra == PI)
    {
        ray->end[0] = x;
        ray->end[1] = y;
        return (MAXFLOAT);
    }
    ray_offset[0] = -ray_offset[1] * tan_inv;
    check_unit_wall(ray, map, ray_offset);
    ray_length = (sqrtf(powf((ray->end[0] - x), 2) + powf((ray->end[1] - y), 2)));
    printf("Ray legth %0.2f\n", ray_length);
    return (ray_length);
}

static float rays_vertical(t_rays *rays, t_map *map, int x, int y)
{
    float tan_inv;
    float ray_offset[2];
    float ray_length;

    rays->ra = map->player_position.player_direction - 30 * (PI / 180);
    tan_inv = -tan(rays->ra);
    if(rays->ra > PI_2  && rays->ra < (3 * PI_2))
    {
        rays->end[0] = x / 32 * 32 - 0.5f;
        ray_offset[0] = -32;
    }
    else if (rays->ra < PI_2 || rays->ra > (3 * PI_2))
    {
        rays->end[0] = x / 32 * 32 + 32;
        ray_offset[0] = 32;
    }
    rays->end[1] = (rays->end[0] - x) * tan_inv + y;
    if(rays->ra == PI_2 || rays->ra == (3 * PI_2))
    {
        rays->end[0] = x;
        rays->end[1] = y;
        return (MAXFLOAT);
    }
    ray_offset[1] = -ray_offset[0] * tan_inv;
    check_unit_wall(rays, map, ray_offset);
    ray_length = sqrtf(powf((rays->end[0] - x), 2) + powf((rays->end[1] - y), 2));
    return (ray_length);
}


void draw_rays(t_rays *ray, t_mlx *mlx, t_map *map, int x, int y)
{
    // printf("Calling rays_horizontal()...\n");
    fflush(stdout);
    int color = 0x00FF00; // Green for horizontal rays

    // Draw horizontal rays
    rays_horizontal(ray, map, x, y);
    mlx_line(mlx, mlx->offscreen_buffer , x, y, ray->end[0], ray->end[1], color);

    // Change color for vertical rays
    color = 0xFF0000; // Red for vertical rays
    rays_vertical(ray, map, x, y);
    mlx_line(mlx, mlx->offscreen_buffer , x, y, ray->end[0], ray->end[1], color);
}
