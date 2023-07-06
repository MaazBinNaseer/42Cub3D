#include "../../inc/Cube3D.h"

void drawRays3D(t_all *access)
{
    float rays = access->map_list->player_position.player_direction;
    int dof, read, mx, my;
    
    float rx = access->map_list->player_position.x * 64, ry = access->map_list->player_position.y * 64, xo = 0, yo = 0;
    for(read = 0; read < 1; read++)
    {
        // *  Checking the horizontal line
        dof = 0;
        float epsilon = 0.55;
        float ainverse_Tan = -1/tan(rays) + epsilon; 
        if(rays > PI) 
        { // If the rays are looking down
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
        if(fabs(cos(rays)) < 0.0001) { // If the rays are looking left or right
            dof = 8;
            ry = access->map_list->player_position.y * 64;
            rx = access->map_list->player_position.x * 64;
        }

        while(dof < 8)
        {
            mx = (int)rx>>6;
            my = (int)ry>>6;
            if(mx < 0 || mx >= access->map_list->coloumns || my < 0 || my >= access->map_list->rows)
            {
                dof = 10;
            }
            else
            {
            //    int mp = my * access->map_list->rows + mx;
                if(access->map_list->map[my][mx] == '1')
                    dof = 8;
                else
                {
                    rx += xo;
                    ry += yo;
                    dof += 1;
                }
            }
        }
        // printf("---- Final Rays are Rx: %0.2f and Ry: %0.2f ------\n", rx, ry);
        float player_center_x = access->map_list->player_position.x * 64 + 32;
        float player_center_y = access->map_list->player_position.y * 64 + 32;
        for(int i = -2; i <= 2; i++) {
    for(int j = -2; j <= 2; j++) {
        mlx_pixel_put(access->mlx_list->mlx,access->mlx_list->window, (int)player_center_x + i, player_center_y + j, 0xFF0000); // Color is set to red for visibility
    }
}
        float ray_length = sqrt(pow(rx - player_center_x, 2) + pow(ry - player_center_y, 2));
        float ray_end_x = player_center_x + (ray_length * 3) * cos(access->map_list->player_position.player_direction);
        float ray_end_y = player_center_y + (ray_length * 3) * sin(access->map_list->player_position.player_direction);
        mlx_line(access->mlx_list, player_center_x, player_center_y, ray_end_x, ray_end_y, 0xFFC0CB); 

    }
    
}

//      printf("The values of are:\n player_center_x: %0.2f\n  player_center_y: %0.2f\n ray_end_x: %0.2f\n ray_end_y: %0.2f\n player_position(x: %0.2f, y: %0.2f)\n", player_center_x, player_center_y, ray_end_x, ray_end_y, access->map_list->player_position.x, access->map_list->player_position.y);
   //     printf("Comparing the player directions with ray position --- Rays direction: %0.2f, Rays_x: %0.2f, Rays_y: %0.2f\n", rays, rx, ry);
 //       printf("Comparing the player directions with Original position --- Player direction: %0.2f, Player_x: %0.2f, Player_y: %0.2f\n", access->map_list->player_position.player_direction, access->map_list->player_position.x, access->map_list->player_position.y);
//