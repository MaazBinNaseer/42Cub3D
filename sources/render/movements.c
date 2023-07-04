#include "../../inc/Cube3D.h"

int key_hook(int keycode, t_all *all)
{
    int new_x = all->map_list->player_position.x;
    int new_y = all->map_list->player_position.y;

    if (keycode == 119 || keycode == 25) // 'w'
    {
        printf("W key pressed (keycode: %d)\n", keycode);
        new_x -= 1;
    }
    else if (keycode == 115 || keycode == 39) // 's'
    {
        printf("S key pressed (keycode: %d)\n", keycode);
        new_x += 1;
    }
    else if (keycode == 97 || keycode == 38) // 'a'
    {
        printf("A key pressed (keycode: %d)\n", keycode);
        new_y -= 1;
    }
    else if (keycode == 100 || keycode == 40) // 'd'
    {
        printf("D key pressed (keycode: %d)\n", keycode);
        new_y += 1;
    }

    // Check if the new position is within the map and not inside a wall
    if (new_x >= 0 && new_x < all->map_list->rows && new_y >= 0 && new_y < all->map_list->coloumns && all->map_list->map[new_x][new_y] != '1')
    {
        all->map_list->player_position.x = new_x;
        all->map_list->player_position.y = new_y;
    }

    printf("The player's position after updating it: x = %d, y = %d\n", all->map_list->player_position.x, all->map_list->player_position.y);

    mlx_clear_window(all->mlx_list->mlx, all->mlx_list->window); // Clear the window
    draw_map(all->mlx_list, all->map_list);
    draw_player(all->mlx_list, all->map_list, all->map_list->player_position.y * 100, all->map_list->player_position.x * 100);

    return (0);
}


