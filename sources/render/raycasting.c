#include "../../inc/Cube3D.h"

static void check_unit_wall(t_rays *ray, t_map *map, float ray_offset[2])
{
    int x;
    int y;
    ray_offset[0] = 0;
    ray_offset[1] = 0;

    while (true)
    {
        x = ray->end[0] / 32;
        y = ray->end[1] / 32;
        if(x < 0 || y < 0 || x >=map->rows || y >= map->coloumns || map->map[x][y] == '1')
            break;
        ray->end[0] += ray_offset[0];
        ray->end[1] += ray_offset[1];
    }
}

static float rays_horizontal(t_rays *ray, t_map *map, int x, int y) 
{
    // printf("Inside rays_horizontal()...\n");
    fflush(stdout);
    float tan_inv;
    float ray_offset[2];
    float ray_length;
    ray->ra = map->player_position.player_direction - 30 * (PI / 180);
    if (ray->ra < 0)
    {
        ray->ra += (float)PI * 2;
    }
    tan_inv = -1 / tan(ray->ra);
    if(ray->ra < PI && ray->ra > 0)
    {
        printf("Entered here\n");
        ray->end[1] = y / 32 * 32 + 32;
        ray->end[0] = (y - ray->end[1]) * tan_inv + x;
        ray_offset[1] = 32;
    }
    else if (ray->ra > PI && ray->ra != PI * 2)
    {
        printf("Entered here 2\n");
        ray->end[1] = y / 32 * 32 - 0.0001f;
        ray->end[0] = (y - ray->end[1]) * tan_inv + x;
        ray_offset[1] = -32;
    }
    if (ray->ra == 0 || ray->ra == PI)
    {
        printf("Entered here 3\n");
        ray->end[0] = x;
        ray->end[1] = y;
        printf("The value of ray->end[0]: %0.2f and ray->end[1]: %0.2f \n" , ray->end[0], ray->end[1]);
        return (MAXFLOAT);
    }
    ray_offset[0] = -ray_offset[1] * tan_inv;
    check_unit_wall(ray, map, ray_offset);
    ray_length = (sqrtf(powf((ray->end[0] - x), 2) + powf((ray->end[1] - y), 2)));
    printf("Ray legth %0.2f\n", ray_length);
    return (ray_length);
}



void draw_rays(t_rays *ray, t_mlx *mlx, t_map *map, int x, int y)
 {
    // printf("Calling rays_horizontal()...\n");
    fflush(stdout);
    int color = 0x00FF00;
    rays_horizontal(ray, map, x, y);

    // draw a line from the player position (x, y) to the end of the ray
    mlx_line(mlx, mlx->offscreen_buffer , x, y, ray->end[0], ray->end[1], color);
}
