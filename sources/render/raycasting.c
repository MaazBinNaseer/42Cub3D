#include "../../inc/Cube3D.h"

int is_valid_tile(t_map *map, int x, int y) {
    int tileX = x / 64;
    int tileY = y / 64;

    if (tileX < 0 || tileY < 0 || tileX >= map->coloumns || tileY >= map->rows)
        return 0;

    if (map->map[tileY][tileX] == '1')
        return 0; 

    return 1;  
}

static float rays_horizontal(t_mlx *mlx, t_rays *ray, t_map *map, float x, float y) {
    int ay;
    int ax; 
    ray->ra = map->player_position.player_direction;

    if(ray->ra > 0 && ray->ra < PI)
        ay = roundf(y / 64.0 ) * 64 - 1;
    else
        ay = roundf(y / 64.0) * 64 + 64;

    if(ray->ra == 0 || roundf(ray->ra) == roundf(PI))
        ray->ra = ray->ra + 0.35;
    else if(roundf(ray->ra) == roundf(6.28))
        ray->ra = 0.35;

    ax = x + roundf((y - ay) /tan(ray->ra));

    int Cx;
    int Cy;
    while(1) {   
        if(ray->ra >= 0 && ray->ra < PI) 
            ray->offset[0] = -64;
        else
            ray->offset[0] = 64;
        ray->offset[1] = roundf(64 / tan(ray->ra));
        Cx = ax + ray->offset[1]; 
        Cy = ay + ray->offset[0];
        if (!is_valid_tile(map, Cx, Cy))
            break;
        ax = Cx;
        ay = Cy;
    }
    float ray_length = sqrtf(powf((Cx - x), 2) + powf((Cy - y), 2));
    int color = 0x00FF00;
    mlx_line(mlx, mlx->offscreen_buffer , x, y, Cx, Cy, color);
    return(ray_length);
}

static float rays_vertical(t_mlx *mlx, t_rays *ray, t_map *map, float x, float y) {
    int ay;
    int ax; 
    ray->ra = map->player_position.player_direction;
    if(ray->ra > PI_2 && ray->ra < 3 * PI_2)
        ax = roundf(x / 64.0 ) * 64 - 1;
    else
        ax = roundf(x / 64.0) * 64 + 64;
    if(ray->ra == 0 || roundf(ray->ra) == roundf(PI))
        ray->ra = ray->ra + 0.5;
    else if(roundf(ray->ra) == roundf(6.28))
        ray->ra = 0.5;
    ay = y + roundf((x - ax) /tan(ray->ra));
    int Cx;
    int Cy;
    while(1)
    {   
        if(ray->ra > PI_2 && ray->ra < 3 * PI_2)
            ray->offset[1] = -64;
        else
            ray->offset[1] = 64;
        ray->offset[0] = roundf(64 / tan(ray->ra));
        Cx = ax + ray->offset[1]; 
        Cy = ay + ray->offset[0];
        if (!is_valid_tile(map, Cx, Cy))
            break;   
        ax = Cx;
        ay = Cy;
    }
    float ray_length = sqrtf(powf((Cx - x), 2) + powf((Cy - y), 2));
    int color = 0xFFA500;
    mlx_line(mlx, mlx->offscreen_buffer , x, y, Cx, Cy, color);
    return(ray_length);
}


#define TWO_PI 6.28318530718 // 2*PI
#define NUM_RAYS 10 // number of rays to cast


void draw_rays(t_rays *ray, t_mlx *mlx, t_map *map, int x, int y)
{
  // calculate the angle increment for each ray
    float angle_increment = TWO_PI / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++) {
        // calculate the direction of this ray
        float ray_angle = i * angle_increment;

        // set the player's direction to the ray angle
        map->player_position.player_direction = ray_angle;

        // cast the ray horizontally and vertically
        rays_horizontal(mlx, ray, map, x, y);
        rays_vertical(mlx, ray, map, x, y);
    }
}


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
