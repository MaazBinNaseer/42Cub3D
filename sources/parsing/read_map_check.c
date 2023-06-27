#include "../../inc/Cube3D.h"

/* ------------------------------------
* Initial check for chars in the map
* If invalid throws the error 
! Should not skip the empty lines 
-------------------------------------*/
bool initial_check_for_chars_in_map(t_map *map_read)
{
    int i = 0;
    while(i < map_read->rows)
    {
        bool is_line_empty = true;
        int j = 0;
        if(map_read->map[i][j] != '\0')  // Check if the line is not empty
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
                is_line_empty = false;
                j++;
            }
        }
         if (is_line_empty) //# [SOME DOUBTS HERE]
             {
                 printf(RED "The line is empty \n" RESET);
                 return (EXIT_FAILURE);
             }
        i++;
    } 
    return (EXIT_SUCCESS);
}


bool check_for_rows_surrounded_map(t_map *map_read)
{
    size_t i = 0;

    size_t len = ft_strlen(map_read->map[1]) - 1;
    size_t first_len = ft_strlen(map_read->map[0]) - 1;

    printf("The length of first row: %ld and the second row is: %ld\n", first_len, len);
    while(i < len)
    {
       if(map_read->map[1][i] == '0' && map_read->map[0][i] != '1')
        {
            printf("0 is not surrounded by a wall");
            return (EXIT_FAILURE);
        }
        else if (map_read->map[1][i] == '1' && map_read->map[0][i] != '1')
        {
            printf("The map enclosure is incomplete\n");
            return (EXIT_FAILURE);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int check_map(t_map *map_check)
{
    if(initial_check_for_chars_in_map(map_check) == 1)
        return (EXIT_FAILURE);
    // else if (check_map_is_surrounded_rows(map_check) == 1)
    //     return (EXIT_FAILURE);
    else if(check_for_rows_surrounded_map(map_check) == 1)
            return (EXIT_FAILURE);
    else if (check_map_is_surrounded_columns(map_check) == 1)
        return (EXIT_FAILURE);
   else if( get_player_position(map_check) == 1)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}