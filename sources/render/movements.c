#include "../../inc/Cube3D.h"


/*
todo: Issues with the movement of the player (need to make it smooth)
*/
float key_hook(int keycode, t_all *all)
{
    float new_x = all->map_list->player_position.x;
    float new_y = all->map_list->player_position.y;

    if (keycode == 119 || keycode == 25) // 'w'
    {
        printf("W key pressed (keycode: %d)\n", keycode);
        new_x -= 0.25;
    }
    else if (keycode == 115 || keycode == 39) // 's'
    {
        printf("S key pressed (keycode: %d)\n", keycode);
        new_x += 0.25;
    }
    else if (keycode == 97 || keycode == 38) // 'a'
    {
        printf("A key pressed (keycode: %d)\n", keycode);
        new_y -= 0.25;
    }
    else if (keycode == 100 || keycode == 40) // 'd'
    {
        printf("D key pressed (keycode: %d)\n", keycode);
        new_y += 0.25;
    }

    int new_x_int = (int)new_x;
    int new_y_int = (int)new_y;
    // Check if the new position is within the map and not inside a wall
    if (new_x >= 0 && new_x < all->map_list->rows && new_y >= 0 && new_y < all->map_list->coloumns && all->map_list->map[new_x_int][new_y_int] != '1')
    {
        all->map_list->player_position.x = new_x;
        all->map_list->player_position.y = new_y;
    }

    printf("The player's position after updating it: x = %0.3f, y = %0.3f\n", all->map_list->player_position.x, all->map_list->player_position.y);

    mlx_clear_window(all->mlx_list->mlx, all->mlx_list->window); // Clear the window
    draw_map(all->mlx_list, all->map_list);
    draw_player(all->mlx_list, all->map_list, all->map_list->player_position.y * 100, all->map_list->player_position.x * 100);

    return (0);
}


