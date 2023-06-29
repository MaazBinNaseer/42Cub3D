#include "../../inc/Cube3D.h"

/*
My keyboard for ESC is 79822912 for some damn reason
*/


int close_windows(t_mlx *mlx, int keycode)
{
    printf("Keycode: %d\n", keycode); // Print the keycode

    mlx_destroy_window(mlx->mlx, mlx->window);
    return (0);
}


int create_window(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return -1; 
    mlx->window = mlx_new_window(mlx->mlx, 450, 360, "HELLO WORLD");
    
    if (!mlx->window)
        return -1; 

    // mlx_hook(mlx->window, 2, 1L<<0, close_windows, mlx);
    mlx_hook(mlx->window, 17, 0, close_windows, NULL);
    return (0);
}
