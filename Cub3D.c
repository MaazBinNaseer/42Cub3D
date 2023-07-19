#include "inc/Cube3D.h"

void intialize_lists(t_all *all, t_map *map, t_config_properties *file ,t_mlx *mlx)
{  
    initialize_list_file(file);
    intialize_list_map(map);
    intialize_list_mlx(mlx);
    all->map_list = map;
    all->mlx_list = mlx;
}

void game_loop(t_all *all, t_map *map, t_mlx *mlx) {

    (void)map;
    
    while (1) {
        // Handle input
        mlx_key_hook(mlx->window, key_hook, all);

        // Render everything on the screen
        mlx_put_image_to_window(mlx->mlx, mlx->window, all->mlx_list->offscreen_buffer, 0, 0);

        // Run the event loop
        mlx_loop(mlx->mlx);
    }
}

void read_arguments_valid(char *arg)
{
    int length = 0;
    t_all *all = malloc(sizeof(t_all)) ;
    t_config_properties *file = malloc(sizeof(t_config_properties));
    t_mlx *mlx = malloc(sizeof(t_mlx));
    t_map *map = malloc(sizeof(t_map));
    intialize_lists(all, map, file, mlx);
    
    while(arg[length] != '\0')
        length++;
    if(length >= 4 && ft_strncmp(arg + length - 4, ".cub", 4) == 0)
        {
            printf("Valid Argument\n");
            if( set_order_of_file(arg) == EXIT_FAILURE)
                exit(1) ;
            read_config_file(arg, file, map);
            create_window(mlx);
            all->mlx_list->offscreen_buffer = mlx_new_image(all->mlx_list->mlx, 1080, 1000);
            all->mlx_list->addr = mlx_get_data_addr(all->mlx_list->offscreen_buffer, &(mlx->bits_per_pixel), &(mlx->line_length), &(mlx->endian));
            game_loop(all, map, mlx);
        }
    else
        printf("No such file exsist\n");
    free(mlx);
    free_map(map);
}

int main(int argc, char **argv)
{
    if (argc > 2)
        printf("Too many arguments. Only the second argument will be accepted.\n");
    else if (argc > 1)
        read_arguments_valid(argv[1]);
    else
        printf("No arguments provided.\n");
    return 0;
}

/*
            printf("all: %p\n", (void*)all);
            printf("all->mlx_list: %p\n", (void*)all->mlx_list);
            printf("all->mlx_list->mlx: %p\n", (void*)all->mlx_list->mlx);
*/