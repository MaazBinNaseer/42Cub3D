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

float rays_horizontal(t_mlx *mlx, t_rays *ray, t_map *map, float x, float y, float angle) {
    int ay;
    int ax;
    float ra = angle;  // Using the passed-in angle here

    if (ra > 0 && ra < PI)
        ay = roundf(y / 64.0) * 64 - 1;
    else
        ay = roundf(y / 64.0) * 64 + 64;

    if (ra == 0 || roundf(ra) == roundf(PI))
        ra = ra + 0.35;
    else if (roundf(ra) == roundf(6.28))
        ra = 0.35;

    ax = x + roundf((y - ay) / tan(ra));  // Using the local ra variable here

    int Cx;
    int Cy;
    while (1) {
        if (ra >= 0 && ra < PI)  // And here
            ray->offset[0] = -64;
        else
            ray->offset[0] = 64;
        ray->offset[1] = roundf(64 / tan(ra));  // And here
        Cx = ax + ray->offset[1];
        Cy = ay + ray->offset[0];
        if (!is_valid_tile(map, Cx, Cy))
            break;
        ax = Cx;
        ay = Cy;
    }

    // Calculate the exact intersection point with the wall (if needed)
    if (is_valid_tile(map, Cx, Cy)) {
        float dist_to_horizontal = fabs((Cy - y) / sin(ra));
        float dist_to_vertical = fabs((Cx - x) / cos(ra));

        if (dist_to_horizontal < dist_to_vertical) {
            Cx = roundf(x + dist_to_horizontal * cos(ra));
            Cy = roundf(y + dist_to_horizontal * sin(ra));
        } else {
            Cx = roundf(x + dist_to_vertical * cos(ra));
            Cy = roundf(y + dist_to_vertical * sin(ra));
        }
    }

    float ray_length = sqrtf(powf((Cx - x), 2) + powf((Cy - y), 2));
    int color = 0x00FF00;
    mlx_line(mlx, mlx->offscreen_buffer, x, y, Cx, Cy, color);
    return ray_length;
}


float rays_vertical(t_mlx *mlx, t_rays *ray, t_map *map, float x, float y, float angle) {
    int ax;
    int ay;
    float ra = angle;  // Using the passed-in angle here

    if (ra > PI_2 && ra < 3 * PI_2)
        ax = roundf(x / 64.0) * 64 - 1;
    else
        ax = roundf(x / 64.0) * 64 + 64;

    if (ra == 0 || roundf(ra) == roundf(PI))
        ra = ra + 0.35;
    else if (roundf(ra) == roundf(6.28))
        ra = 0.35;

    ay = y + roundf((x - ax) / tan(ra));  // Using the local ra variable here

    int Cx;
    int Cy;
    while (1) {
        if (ra > PI_2 && ra < 3 * PI_2)  // And here
            ray->offset[1] = -64;
        else
            ray->offset[1] = 64;
        ray->offset[0] = roundf(64 / tan(ra));  // And here
        Cx = ax + ray->offset[1];
        Cy = ay + ray->offset[0];
        if (!is_valid_tile(map, Cx, Cy))
            break;
        ax = Cx;
        ay = Cy;
    }

    // Calculate the exact intersection point with the wall (if needed)
    if (is_valid_tile(map, Cx, Cy)) {
        float dist_to_vertical = fabs((Cx - x) / cos(ra));
        float dist_to_horizontal = fabs((Cy - y) / sin(ra));

        if (dist_to_vertical < dist_to_horizontal) {
            Cx = roundf(x + dist_to_vertical * cos(ra));
            Cy = roundf(y + dist_to_vertical * sin(ra));
        } else {
            Cx = roundf(x + dist_to_horizontal * cos(ra));
            Cy = roundf(y + dist_to_horizontal * sin(ra));
        }
    }

    float ray_length = sqrtf(powf((Cx - x), 2) + powf((Cy - y), 2));
    int color = 0xFFA500;
    mlx_line(mlx, mlx->offscreen_buffer, x, y, Cx, Cy, color);
    return ray_length;
}


#define TWO_PI 6.28318530718 // 2*PI
#define NUM_RAYS 9 // number of rays to cast


void draw_rays(t_rays *ray, t_mlx *mlx, t_map *map, int x, int y)
{
 // calculate the angle increment for each ray
    float angle_increment = (30.0 * PI / 180.0);
    float lol = 0;
    for (int i = 0; i < NUM_RAYS; i++) {
        // calculate the direction of this ray
        float ray_angle = i * angle_increment;

        // cast the ray horizontally and vertically
        // printf("Line %s\n" , map->map[i]);

        rays_horizontal(mlx, ray, map, x, y, ray_angle);
        rays_vertical(mlx, ray, map, x, y, ray_angle);
        lol =  get_shortest_distance_to_wall(mlx, ray, map, x, y, ray_angle);
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


