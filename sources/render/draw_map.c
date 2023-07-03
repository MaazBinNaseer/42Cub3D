#include "../../inc/Cube3D.h"

void draw_box(t_mlx *mlx, int x, int y, int color, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        mlx_pixel_put(mlx->mlx, mlx->window, x + i, y, color); // Top edge
        mlx_pixel_put(mlx->mlx, mlx->window, x + i, y + size - 1, color); // Bottom edge
        mlx_pixel_put(mlx->mlx, mlx->window, x, y + i, color); // Left edge
        mlx_pixel_put(mlx->mlx, mlx->window, x + size - 1, y + i, color); // Right edge
    }
}

void draw_box_wall(t_mlx *mlx, int x, int y, int size)
{
    int i, j;

    int black = 0x000000; // Black color for outline
    int white = 0xFFFFFF; // White color for filling

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            // Check if we are at the edge of the box
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1)
                mlx_pixel_put(mlx->mlx, mlx->window, x + i, y + j, black);
            else
                mlx_pixel_put(mlx->mlx, mlx->window, x + i, y + j, white);
        }
    }
}


void draw_map(t_mlx *mlx, t_map *map)
{
    int i, j;
    int size = 100;  // size of each box
    int color;
    // int offset_x = 0;
    // int offset_y = 0;

    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->coloumns; j++) {
            if (map->map[i][j] == '0') {
                color = 0x000000;  // free space color: yellow
                draw_box(mlx, j * size, i * size, color, size);
            } else if (map->map[i][j] == '1') {
                color = 0xFFFFFF;
                draw_box(mlx, j * size, i * size, color, size); // wall color: white
            } else if (map->map[i][j] == 'S') {
                color = 0x0000FF;  // start point color: blue
                draw_box(mlx, j * size, i * size, color, size);
            }
        }
    }
}

/*
todo: Find a way to print an image on the screen 
*/
void intialize_images(t_map *map, t_im *img, t_mlx *mlx)
{
    int width = 64;
    img->wall = mlx_xpm_file_to_image(mlx->mlx, "./xpms/wall_2.xpm", &width, &width);
    img->path = mlx_xpm_file_to_image(mlx->mlx, "./xpms/path.xpm",&width, &width);
    map->img = img;
    if(img->wall == NULL)
        {
            printf(RED "Intialize fail\n" RESET);
            exit(1);
        }
    
}