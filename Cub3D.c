#include "inc/Cube3D.h"

// #include <stdio.h>

/* ---------------------------------------------------------------
* @brief: To allow the user to handle incorrect inputs
* @return: Should throw an error when the argument fails more than 2 
todo: Intialized list call should have a separate function call 
------------------------------------------------------------------*/
void read_arguments_valid(char *arg)
{
    int length = 0;
    
    t_mlx *mlx = malloc(sizeof(t_mlx));
    mlx->mlx = NULL;
    mlx->window = NULL;
    t_map *map = (malloc(sizeof(t_map)));
    intialize_list_map(map);
    t_config_properties *file = malloc(sizeof(t_config_properties));
    initialize_list_file(file);
    while(arg[length] != '\0')
        length++;
    if(length >= 4 && ft_strncmp(arg + length - 4, ".cub", 4) == 0)
        {
            printf("Valid Argument\n");
            if( set_order_of_file(arg) == EXIT_FAILURE)
                exit(1) ;
            read_config_file(arg, file, map);
            create_window(mlx, map);
            mlx_loop(mlx->mlx);
        }
    else
        printf("No such file exsist\n");
    free(mlx);
    free_map(map);
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("Too many arguments. Only the second argument will be accepted.\n");
    }
    else if (argc > 1)
    {
        read_arguments_valid(argv[1]);
    }
    else
    {
        printf("No arguments provided.\n");
    }

    return 0;
}