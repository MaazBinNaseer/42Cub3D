#include "../../inc/Cube3D.h"

/* ------------------------------------
* Initial check for chars
* skips through the empty lines 
-------------------------------------*/
bool initial_check_for_chars_in_map(t_map *map_read)
{
    int i = 0;
    while(i < map_read->rows)
    {
        int j = 0;
        if(map_read->map[i][0] != '\0')  // Check if the line is not empty
        {
            while(map_read->map[i][j] != '\0')
            {
                if (map_read->map[i][j] == '\n')
                    break;
                if(!ft_strchr("NSEW01", map_read->map[i][j]))
                {
                    printf(RED "We found something there [%c]\n" RESET, map_read->map[i][j]);
                    return (EXIT_FAILURE);
                }
                j++;
            }
        }
        i++;
    } 
    return (EXIT_SUCCESS);
}


int check_map(t_map *map_check)
{
    if(initial_check_for_chars_in_map(map_check) == 1)
        return (EXIT_FAILURE);
    else if (check_map_is_surrounded_rows(map_check) == 1)
        return (EXIT_FAILURE);
    else if (check_map_is_surrounded_columns(map_check) == 1)
        return (EXIT_FAILURE);
   else if( get_player_position(map_check) == 1)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}