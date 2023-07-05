#include "../../inc/Cube3D.h"

void drawRays3D(t_all *access)
{
    float rays = access->map_list->player_position.player_direction;
    int dof, read, mx, my, mp;
    float rx = 0, ry = 0, xo = 0, yo = 0;
    for(read = 0; read < 1; read++)
    {
        // *  Checking the horizontal line
        dof = 0;
        float ainverse_Tan = -1/tan(rays); 
        if(rays > PI) //* If the rays are looking up
        {
            printf("Ry: %f, Rx: %f\n", rx, ry);
            ry = (((int)(access->map_list->player_position.y)>>6)<<6) - 0.0001;
            rx = (access->map_list->player_position.y) * ainverse_Tan + access->map_list->player_position.x;
            yo = -64;
            xo = -yo * ainverse_Tan;
        }
        if(rays < PI) //* If the rays are looking down
        {
            printf("Ry: %f, Rx: %f\n", rx, ry);
            ry = (((int)(access->map_list->player_position.y)>>6)<<6) + 64;
            rx = (access->map_list->player_position.y) * ainverse_Tan + access->map_list->player_position.x;
            yo = 64;
            xo = -yo*ainverse_Tan;
        }

        if(rays == 0 || rays == PI) //* If the rays are looking left or right
        {
             printf("Ry: %0.2f, Rx: %0.2f\n", rx, ry);
            ry = access->map_list->player_position.y;
            rx = access->map_list->player_position.x;
            dof = 8;
        }
        while(dof < 8)
        {
            mx = (int)rx>>6;
            my = (int)ry>>6;
            mp = my * access->map_list->rows + mx;
            if(mp < (access->map_list->rows * access->map_list->coloumns) && (access->map_list->map[my][mx] == '1'))
                dof = 8;
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        printf("Rays are Rx: %0.2f and Ry: %0.2f\n", rx, ry);

        float player_center_x = access->map_list->player_position.x * 32 + 16;
        float player_center_y = access->map_list->player_position.y * 32 + 16;
        float ray_end_x = player_center_x + rx * 64 * cos(access->map_list->player_position.player_direction);
        float ray_end_y = player_center_y + ry * 64 * sin(access->map_list->player_position.player_direction);
        mlx_line(access->mlx_list, player_center_x, player_center_y, ray_end_x, ray_end_y, 0xFFC0CB); 
    }
}