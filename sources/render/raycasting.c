#include "../../inc/Cube3D.h"


static float rays_horizontal(t_mlx *mlx, t_rays *ray, t_map *map, float x, float y) 
{
   //* Finding the first coordinate 
//    printf("What are the players coordinates: x: %0.2f", map->player_position.x);
    int ay;
    int ax; 
    // printf("The value of x: %0.2f and y %0.2f\n", x , y);
    ray->ra = map->player_position.player_direction;
    if(ray->ra > 0 && ray->ra < PI)
    {
        ay = roundf(y / 64.0 ) * 64 - 1;
    }
    else
    {
        ay = roundf(y / 64.0) * 64 + 64;
    }
    if(ray->ra == 0 || roundf(ray->ra) == roundf(PI))
        ray->ra = ray->ra + 0.35;
    else if(roundf(ray->ra) == roundf(6.28))
        ray->ra = 0.35;
    ax = x + roundf((y - ay) /tan(ray->ra));
    // printf("The value of ay is %d and ax is %d\n", (ay / 64), (ax / 64));
    int Cx;
    int Cy;
    while(1)
    {   
        if(ray->ra >= 0 && ray->ra < PI) // taking Ya as rayoffset[0]
            ray->offset[0] = -64;
        else
            ray->offset[0] = 64;
        ray->offset[1] = roundf(64 / tan(ray->ra));
        printf("The [Horizontal] rayoffset[1] is %0.2f\n", ray->offset[1]);
        //* Finding the Cy and Cx
        Cx = ax + ray->offset[1]; 
        Cy = ay + ray->offset[0];
        // printf("The value of Cy is %d and Cx is %d\n", (Cy / 64), (Cx / 64));
        if((Cx / 64) < 0 || (Cy / 64) < 0 || (Cx / 64) >= map->coloumns || (Cy / 64) >= map->rows || map->map[Cy / 64][Cx / 64] == '1')
        {  
            break;
        }
        ax = Cx;
        ay = Cy;
    }
    float ray_length = sqrtf(powf((Cx - x), 2) + powf((Cy - y), 2));
    int color = 0x00FF00;
    mlx_line(mlx, mlx->offscreen_buffer , x, y, Cx, Cy, color);
    return(ray_length);
}



static float rays_vertical(t_mlx *mlx, t_rays *ray, t_map *map, float x, float y)
{
    int ay;
    int ax; 
    ray->ra = map->player_position.player_direction;

    if(ray->ra > PI_2 && ray->ra < 3 * PI_2)
    {
        ax = roundf(x / 64.0 ) * 64 - 1;
    }
    else
    {
        ax = roundf(x / 64.0) * 64 + 64;
    }
    if(ray->ra == 0 || roundf(ray->ra) == roundf(PI))
        ray->ra = ray->ra + 0.5;
    else if(roundf(ray->ra) == roundf(6.28))
        ray->ra = 0.5;
    ay = y + roundf((x - ax) /tan(ray->ra));
    int Cx;
    int Cy;
    while(1)
    {   
        if(ray->ra > PI_2 && ray->ra < 3 * PI_2) // taking Ya as rayoffset[0]
            ray->offset[1] = -64;
        else
            ray->offset[1] = 64;
        ray->offset[0] = roundf(64 / tan(ray->ra));
        printf("The [Vertical] rayoffset[0] is %0.2f\n", ray->offset[0]);
        //* Finding the Cy and Cx
        Cx = ax + ray->offset[1]; 
        Cy = ay + ray->offset[0];
        if((Cx / 64) < 0 || (Cy / 64) < 0 || (Cx / 64) >= map->coloumns || (Cy / 64) >= map->rows || map->map[Cy / 64][Cx / 64] == '1')
        {  
            break;
        }
        ax = Cx;
        ay = Cy;
    }
    float ray_length = sqrtf(powf((Cx - x), 2) + powf((Cy - y), 2));
    int color = 0xFFA500;
    mlx_line(mlx, mlx->offscreen_buffer , x, y, Cx, Cy, color);
    return(ray_length);
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

void draw_rays(t_rays *ray, t_mlx *mlx, t_map *map, int x, int y)
{
    rays_horizontal(mlx, ray, map, x, y);
    rays_vertical(mlx, ray, map, x, y);

    
}
