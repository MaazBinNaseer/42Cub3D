#include "../../inc/Cube3D.h"

void updatePlayerDirection(t_all *access, float rotation_angle) {
    access->map_list->player_position.player_direction += rotation_angle;
    if (access->map_list->player_position.player_direction < 0) {
        access->map_list->player_position.player_direction += 2*PI;
    } else if (access->map_list->player_position.player_direction >= 2*PI) {
        access->map_list->player_position.player_direction -= 2*PI;
    }
}

int key_hook(int keycode, t_all *all)
{
    float size = 64;
    float moveStep = 7.0 / size; // Adjusted move step
    float old_x = all->map_list->player_position.x;
    float old_y = all->map_list->player_position.y;
    float old_angle = all->map_list->player_position.player_direction;
    float new_x = old_x;
    float new_y = old_y;
    float new_angle = old_angle;

    if (keycode == 119 || keycode == 25) // 'w' - Move forward
    {
        new_x -= cos(new_angle) * moveStep;
        new_y -= sin(new_angle) * moveStep;
    }
    else if (keycode == 115 || keycode == 39) // 's' - Move backward
    {
         float temp_x = new_x + cos(new_angle) * moveStep;
        float temp_y = new_y +  sin(new_angle) * moveStep;
        if (temp_x >= 0 && temp_x < all->map_list->rows && temp_y >= 0 && temp_y < all->map_list->coloumns && all->map_list->map[(int)temp_x][(int)temp_y] != '1') {
            new_x = temp_x;
            new_y = temp_y;
        }
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

    // Continuous collision detection for all movement keys
    float t = 0.0;
    while (t < 1.0) {
        float intermediate_x = old_x + t * (new_x - old_x);
        float intermediate_y = old_y + t * (new_y - old_y);
        if (all->map_list->map[(int)intermediate_x][(int)intermediate_y] == '1') {
            // Collision detected
            new_x = old_x;
            new_y = old_y;
            break;
        }
        t += 0.1;
    }
    if (all->map_list->player_position.y >= 0 && all->map_list->player_position.y < all->map_list->rows &&
    all->map_list->player_position.x >= 0 && all->map_list->player_position.x < all->map_list->coloumns && 
    all->map_list->map[(int)floor(all->map_list->player_position.y)][(int)floor(all->map_list->player_position.x)] == '1')
    {
    // Collision with wall, revert to old position
        all->map_list->player_position.x = old_x;
        all->map_list->player_position.y = old_y;
        all->map_list->player_position.player_direction = old_angle;
    }

    all->map_list->player_position.x = new_x;
    all->map_list->player_position.y = new_y;
    all->map_list->player_position.player_direction = new_angle;
    mlx_put_image_to_window(all->mlx_list->mlx, all->mlx_list->window, all->mlx_list->offscreen_buffer, 0, 0);
    draw_player(all->mlx_list, all->map_list, all->map_list->player_position.x, all->map_list->player_position.y, size);
    return (0);
}

