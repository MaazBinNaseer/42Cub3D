#include "../../inc/Cube3D.h"

/*
! Segmentation fault and No Image load Images ---------- 
*/
void draw_big_pixel(t_mlx *mlx, int x, int y, int color)
{
    int big_pixel_size = 10;  // The size of the big pixel
    int i, j;

    for (i = 0; i < big_pixel_size; ++i) {
        for (j = 0; j < big_pixel_size; ++j) {
            mlx_pixel_put(mlx->mlx, mlx->window, x + i, y + j, color);
        }
    }
}

void draw_map(t_mlx *mlx, t_map *map)
{
    int i, j;
    int width = 2000;
    int offset_x = 20; 
    int offset_y = 20;

    int big_pixel_size = (width) / (2 * map->coloumns);
    (void)mlx;
    printf(GRN "The map column is %d\n" RESET, map->coloumns);
    printf(GRN "The map column is %d\n" RESET, map->rows);

    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->coloumns; j++) {
            if (map->map[i][j] == '0') {
                // Draw a big pixel in red at the adjusted coordinates (j, i).
                draw_big_pixel(mlx, (j * big_pixel_size) + offset_x, (i * big_pixel_size) + offset_y, 0xFF0000);
            } else if (map->map[i][j] == '1') {
                // Draw a big pixel in white at the adjusted coordinates (j, i).
                draw_big_pixel(mlx, (j * big_pixel_size) + offset_x, (i * big_pixel_size) + offset_y, 0xFFFFFF);
                
                // Load and display an image at the adjusted coordinates (j, i)
                // void *image = mlx_xpm_file_to_image(mlx->mlx, "image.xpm", NULL, NULL);
                // mlx_put_image_to_window(mlx->mlx, mlx->window, image, (j * big_pixel_size) + offset_x, (i * big_pixel_size) + offset_y);
            } else if (map->map[i][j] == 'S') {
                // Draw a big pixel in blue at the adjusted coordinates (j, i).
                draw_big_pixel(mlx, (j * big_pixel_size) + offset_x, (i * big_pixel_size) + offset_y, 0x0000FF);
            }
        }
    }
}

