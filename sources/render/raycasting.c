#include "../../inc/Cube3D.h"


#define FOV (PI / 2)
#define NUMBER_OF_RAYS 180

float* drawRays_horizontal3D(t_all *access)
{
    float rays;
    int dof, mx, my;
    float rx, ry, xo, yo;
    float* ray_lengths = malloc(NUMBER_OF_RAYS * sizeof(float));
    float angle_increment = FOV / NUMBER_OF_RAYS;
    float fov_start = access->map_list->player_position.player_direction - (FOV / 2);

    for(int ray_num = 0; ray_num < NUMBER_OF_RAYS; ray_num++)
    {
        rays = fov_start + ray_num * angle_increment;

        dof = 0;
        float epsilon = 0.55;
        float ainverse_Tan = -1/tan(rays) + epsilon;

        rx = access->map_list->player_position.x * 64;
        ry = access->map_list->player_position.y * 64;
        xo = yo = 0;

        if(rays > PI) { // If the rays are looking down
            ry = (((int)(access->map_list->player_position.y)>>6)<<6) + 64;
            rx = (access->map_list->player_position.x * 64) + (ry - access->map_list->player_position.y * 64) / ainverse_Tan;
            yo = 64;
            xo = -yo / ainverse_Tan;
        }
        if(rays < PI) { // If the rays are looking up
            ry = (((int)(access->map_list->player_position.y + 0.0001)>>6)<<6) - 0.0001;
            rx = (access->map_list->player_position.x * 64) + (ry - access->map_list->player_position.y * 64) / ainverse_Tan;
            yo = -64;
            xo = -yo / ainverse_Tan;
        }

        while(dof < 8)
        {
            mx = ((int)0.001 + ((int)rx>>6));
            my = ((int)0.001 + ((int)ry>>6));
            if(mx < 0 || mx >= access->map_list->coloumns || my < 0 || my >= access->map_list->rows)
                dof = 8;
            else
            {
                if(access->map_list->map[my][mx] == '1')
                { 
                    dof = 8;
                    float player_center_x = access->map_list->player_position.x * 32 + 16 ;
                    float player_center_y = access->map_list->player_position.y * 32 + 16;
                    for(int i = -2; i <= 2; i++) {
                        for(int j = -2; j <= 2; j++) {
                            my_mlx_pixel_put(access->mlx_list->mlx,(int)player_center_x, (int)player_center_y, 0xFF0000); // Color is set to red for visibility
                        }
                    }
                    ray_lengths[ray_num] = sqrt(pow(rx - player_center_x, 2) + pow(ry - player_center_y, 2));
                    float ray_end_x = player_center_x + ray_lengths[ray_num]  * cos(access->map_list->player_position.player_direction);
                    float ray_end_y = player_center_y + ray_lengths[ray_num]  * sin(access->map_list->player_position.player_direction);
                    mlx_line(access->mlx_list, player_center_x, player_center_y, ray_end_x, ray_end_y, 0xFFC0CB); 
                    break;
                }
                else
                {
                    rx += xo; ry += yo; dof += 1;
                }
            }
        }
    }
    return ray_lengths;  
}































// float drawRays_horizontal3D(t_all *access)
// {
//     float rays = access->map_list->player_position.player_direction;
//     int dof, read, mx, my;
    
//     float rx = access->map_list->player_position.x * 64, ry = access->map_list->player_position.y * 64, xo = 0, yo = 0;
//     float ray_length = 0.0f;
//     for(read = 0; read < 1; read++)
//     {
//         // *  Checking the horizontal line
//         dof = 0;
//         float epsilon = 0.55;
//         float ainverse_Tan = -1/tan(rays) + epsilon; 
//         if(rays > PI) 
//         { // If the rays are looking down
//             ry = (((int)(access->map_list->player_position.y)>>6)<<6) + 64;
//             rx = (access->map_list->player_position.x * 64) + (ry - access->map_list->player_position.y * 64) / ainverse_Tan;
//             yo = 64;
//             xo = -yo / ainverse_Tan;
//         }
//         if(rays < PI) { // If the rays are looking up
//             ry = (((int)(access->map_list->player_position.y + 0.0001)>>6)<<6) - 0.0001;
//             rx = (access->map_list->player_position.x * 64) + (ry - access->map_list->player_position.y * 64) / ainverse_Tan;
//             yo = -64;
//             xo = -yo / ainverse_Tan;
//         }
//         while(dof < 8)
//         {
//             mx =( (int)0.001 + ((int)rx>>6));
//             my = ((int)0.001 + ((int)ry>>6));
//             if(mx < 0 || mx >= access->map_list->coloumns || my < 0 || my >= access->map_list->rows)
//                     dof = 8;
//             else
//             {
//                 if(access->map_list->map[my][mx] == '1')
//                    { 
//                         dof = 8;
//                         float player_center_x = access->map_list->player_position.x * 32 + 16 ;
//                         float player_center_y = access->map_list->player_position.y * 32 + 16;
//                         for(int i = -2; i <= 2; i++) {
//                             for(int j = -2; j <= 2; j++) {
//                             mlx_pixel_put(access->mlx_list->mlx,access->mlx_list->window, (int)player_center_x + i, player_center_y + j, 0xFF0000); // Color is set to red for visibility
//                             }
//                         }
//                         ray_length = sqrt(pow(rx - player_center_x, 2) + pow(ry - player_center_y, 2));
//                         printf("Ray length from the horizontal function %0.2f | ", ray_length);
//                         float ray_end_x = player_center_x + ray_length  * cos(access->map_list->player_position.player_direction);
//                         float ray_end_y = player_center_y + ray_length  * sin(access->map_list->player_position.player_direction);
//                         mlx_line(access->mlx_list, player_center_x, player_center_y, ray_end_x, ray_end_y, 0xFFC0CB); 
//                    }
//                 else
//                 {
//                     rx += xo; ry += yo; dof += 1;
//                 }
//             }
//         }
    
//     }
//     return (ray_length);  
// }

// float drawRays_vertical3D(t_all *access)
// {
//     float rays = access->map_list->player_position.player_direction;
//     int dof, read, mx, my;
    
//     float rx = access->map_list->player_position.x * 64, ry = access->map_list->player_position.y * 64, xo = 0, yo = 0;
//     float ray_length = 0.0f;
//     for(read = 0; read < 1; read++)
//     {
//         // *  Checking the vertical line
//         dof = 0;
//            float ainverse_Tan;
//         if(fabs(tan(rays)) < 0.0001) {
//             ainverse_Tan = 0; 
//         }
//         else {
//             ainverse_Tan = 1/tan(rays); 
//         }
//             if(rays > PI/2 && rays < (3*PI/2))
//         { // If the rays are looking left
//             rx = (((int)(access->map_list->player_position.x)>>6)<<6) - 0.0001;
//             ry = (access->map_list->player_position.y * 64) + (access->map_list->player_position.x * 64 - rx) * ainverse_Tan;
//             xo = -64;
//             yo = -xo * ainverse_Tan;
//         }
//         if(rays < PI/2 || rays > (3*PI/2)) { // If the rays are looking right
//             rx = (((int)(access->map_list->player_position.x + 0.0001)>>6)<<6) + 64;
//             ry = (access->map_list->player_position.y * 64) + (rx - access->map_list->player_position.x * 64) * ainverse_Tan;
//             xo = 64;
//             yo = xo * ainverse_Tan;
//         }
//         if(fabs(sin(rays)) < 0.0001) { // If the rays are looking up or down
//             dof = 8;
//             rx = access->map_list->player_position.x * 64;
//             ry = access->map_list->player_position.y * 64;
//         }
//         while(dof < 8)
//         {
//             mx =( (int)0.001 + ((int)rx>>6));
//             my = ((int)0.001 + ((int)ry>>6));
//             if(mx < 0 || mx >= access->map_list->coloumns || my < 0 || my >= access->map_list->rows)
//                 dof = 8;
//             else
//             {
//                 if(access->map_list->map[my][mx] == '1')
//                     {
//                         dof = 8;

//                         float player_center_x = access->map_list->player_position.x * 32 + 16;
//                         float player_center_y = access->map_list->player_position.y * 32 + 16;
//                         for(int i = -2; i <= 2; i++) {
//                         for(int j = -2; j <= 2; j++) {
//                             mlx_pixel_put(access->mlx_list->mlx,access->mlx_list->window, (int)player_center_x + i, player_center_y + j, 0xFF0000);
//                             }
//                         }
//                         ray_length = sqrt(pow(rx - player_center_x, 2) + pow(ry - player_center_y, 2));
//                         printf("Ray length from the veritcal function %0.2f\n", ray_length);
//                         float ray_end_x = player_center_x + ray_length * cos(access->map_list->player_position.player_direction);
//                         float ray_end_y = player_center_y + ray_length * sin(access->map_list->player_position.player_direction);
//                         mlx_line(access->mlx_list, player_center_x, player_center_y, ray_end_x, ray_end_y, 0xFF0000);
//                     }
//                 else
//                 {
//                     rx += xo; ry += yo; dof += 1;
//                 }
//             }
//         }

//     }  
//     return (ray_length);
// }

// float calculate_distance (t_all *access)
// {
//     float hor_dist = drawRays_horizontal3D(access);
//     float vert_dist = drawRays_vertical3D(access);
    
//     float shortest_distance = fmin(hor_dist, vert_dist);
    
//     return (shortest_distance);
// }

  // if(fabs(cos(rays)) < 0.0001) { // If the rays are looking left or right
        //     dof = 8;
        //     ry = access->map_list->player_position.y * 64;
        //     rx = access->map_list->player_position.x * 64;
        // }  