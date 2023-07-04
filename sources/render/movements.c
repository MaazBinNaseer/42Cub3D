#include "../../inc/Cube3D.h"


/*
todo: Issues with the movement of the player (need to make it smooth)
*/
int key_hook(int keycode, t_all *all)
{
    printf("The value of the keycode is %d\n", keycode);
    float new_x = all->map_list->player_position.x;
    float new_y = all->map_list->player_position.y;
    float new_angle = all->map_list->player_position.player_direction;

    if (keycode == 119 || keycode == 25) // 'w'
    {
        printf("W key pressed (keycode: %d)\n", keycode);
        new_x -= cos(new_angle) * 0.5;
        new_y -= sin(new_angle) * 0.5;
    }
    else if (keycode == 115 || keycode == 39) // 's'
    {
        printf("S key pressed (keycode: %d)\n", keycode);
        new_x += cos(new_angle) * 0.5;
        new_y += sin(new_angle) * 0.5;
    }
    else if (keycode == 97 || keycode == 38) // 'a'
    {
        printf("A key pressed (keycode: %d)\n", keycode);
        new_x += sin(new_angle) * 0.5;
        new_y -= cos(new_angle) * 0.5;
    }
    else if (keycode == 100 || keycode == 40) // 'd'
    {
        printf("D key pressed (keycode: %d)\n", keycode);
        new_x -= sin(new_angle) * 0.5;
        new_y += cos(new_angle) * 0.5;
    }
    else if (keycode == 65361) // '<-'
    {
        printf("<- key pressed (keycode: %d)\n", keycode);
        new_angle -= 0.1;
        if(new_angle < 0)
            new_angle += 2*PI;
    }
    else if (keycode == 65363) // '->'
    {
        printf("-> key pressed (keycode: %d)\n", keycode);
        new_angle += 0.1;
        if(new_angle > 2*PI)
            new_angle -= 2*PI;
    }
    // Check if the new position is within the map and not inside a wall
    if (new_x >= 0 && new_x < all->map_list->rows && new_y >= 0 && new_y < all->map_list->coloumns && all->map_list->map[(int)new_x][(int)new_y] != '1')
    {
        all->map_list->player_position.x = new_x;
        all->map_list->player_position.y = new_y;
        all->map_list->player_position.player_direction = new_angle;
    }
    printf("The player's position after updating it: x = %f, y = %f, angle = %f\n", all->map_list->player_position.x, all->map_list->player_position.y, all->map_list->player_position.player_direction);
    mlx_clear_window(all->mlx_list->mlx, all->mlx_list->window); // Clear the window
    draw_map(all->mlx_list, all->map_list);
    draw_player(all->mlx_list, all->map_list, all->map_list->player_position.y * 100, all->map_list->player_position.x * 100);
    return (0);
}



