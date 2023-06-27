#include "../../inc/Cube3D.h"
// #include <stdio.h>

/* ---------------------------------------------------------------
* @brief: To allow the user to handle incorrect inputs
* @return: Should throw an error when the argument fails more than 2 
------------------------------------------------------------------*/
void read_arguments_valid(char *arg)
{
    int length = 0;
    //* Intialized list --- needs to have a separate function
    t_map map;
    map.rows = 0;
    map.map = NULL;
    map.player_position.x = 0;
    map.player_position.y = 0;
    map.player = 0;
    t_config_properties file;
    file.north_texture = "";
    file.map_set = 0;
    // count the length of the string
    while(arg[length] != '\0')
        length++;
    if(length >= 4 && ft_strncmp(arg + length - 4, ".cub", 4) == 0)
        {
            printf("Valid Argument\n");
            if( set_order_of_file(arg) == EXIT_FAILURE)
                return ;
            
            read_config_file(arg, &file, &map);
            // read_map(arg, &map);
            // check_map(&map);
        }
    else
        printf("No such file exsist\n");
    // for(int i = 0; i < map.rows; i++)
    //      free(map.map[i]);
    //  free(map.map);
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