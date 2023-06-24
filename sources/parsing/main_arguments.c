#include "../../inc/Cube3D.h"
// #include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t num)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if (num == 0)
		return (0);
	while ((i < num - 1) && (ptr1[i] != '\0' && ptr2[i] != '\0')
		&& (ptr1[i] == ptr2[i]))
		i++;
	return (ptr1[i] - ptr2[i]);
}


/* ---------------------------------------------------------------
* @brief: To allow the user to handle incorrect inputs
* @return: Should throw an error when the argument fails more than 2 
------------------------------------------------------------------*/
void read_arguments_valid(char *arg)
{
    int length = 0;
    t_map map;
    map.rows = 0;
    map.map = NULL;
    // count the length of the string
    while(arg[length] != '\0')
        length++;

    // check if the last four characters match ".cub"
    if(length >= 4 && ft_strncmp(arg + length - 4, ".cub", 4) == 0)
        {
            printf("Valid Argument\n");
            read_map(arg, &map);
            check_map_is_surronded(&map);
            get_player_position(&map);
             for(int i = 0; i < map.rows; i++)
            {
                free(map.map[i]);
            }
            free(map.map);
            // free(read);
        }
    else
        printf("Error\n");
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