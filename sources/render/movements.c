#include "../../inc/Cube3D.h"

void updatePlayerDirection(t_all *access, float rotation_angle) {
    
    access->map_list->player_position.player_direction += rotation_angle;
    if (access->map_list->player_position.player_direction < 0) {
        access->map_list->player_position.player_direction += 2*PI;
    } else if (access->map_list->player_position.player_direction >= 2*PI) {
        access->map_list->player_position.player_direction -= 2*PI;
    }
    return ;
}
/*
todo: Issues with the movement of the player (need to make it smooth)
*/
int key_hook(int keycode, t_all *all)
{
    float  deltaTime = 0.567;
    float new_x = all->map_list->player_position.x;
    float new_y = all->map_list->player_position.y;
    float new_angle = all->map_list->player_position.player_direction;
    float speed = 0.25;
    float moveStep = speed * deltaTime;


    if (keycode == 119 || keycode == 25) // 'w' - Move forward
    {
        new_x += cos(new_angle) * moveStep;
        new_y += sin(new_angle) * moveStep;
    }
    else if (keycode == 115 || keycode == 39) // 's' - Move backward
    {
        new_x -= cos(new_angle) * moveStep;
        new_y -= sin(new_angle) * moveStep;
    }
    else if (keycode == 97 || keycode == 38) // 'a' - Strafe left
    {
        new_x -= cos(new_angle + PI/2) * moveStep; // Add 90 degrees to the player angle
        new_y -= sin(new_angle + PI/2) * moveStep;
    }
    else if (keycode == 100 || keycode == 40) // 'd' - Strafe right
    {
        new_x += cos(new_angle + PI/2) * moveStep; // Add 90 degrees to the player angle
        new_y += sin(new_angle + PI/2) * moveStep;
    }
    else if (keycode == 65361) // '<-'
    {
        updatePlayerDirection(all, -0.785398);
        new_angle = all->map_list->player_position.player_direction;
    }
    else if (keycode == 65363) // '->'
    {
        updatePlayerDirection(all, 0.785398);
        new_angle = all->map_list->player_position.player_direction;
    }
    if (new_x >= 0 && new_x < all->map_list->rows && new_y >= 0 && new_y < all->map_list->coloumns && all->map_list->map[(int)new_x][(int)new_y] != '1')
    {
        all->map_list->player_position.x = new_x;
        all->map_list->player_position.y = new_y;
        all->map_list->player_position.player_direction = new_angle;
    }
    // printf("The player's position after updating it: x = %0.2f, y = %0.2f, angle = %0.2f\n", all->map_list->player_position.x, all->map_list->player_position.y, all->map_list->player_position.player_direction);
    mlx_clear_window(all->mlx_list->mlx, all->mlx_list->window); 
    draw_map(all->mlx_list, all->map_list, all);
    draw_player(all->mlx_list, all->map_list, all->map_list->player_position.x, all->map_list->player_position.y, all);
    return (0);
}


