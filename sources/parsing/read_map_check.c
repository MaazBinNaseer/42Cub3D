#include "../../inc/Cube3D.h"

/* ------------------------------------
* Initial check for chars in the map
* If invalid throws the error 
! Should not skip the empty lines 
-------------------------------------*/
bool initial_check_for_chars_in_map(t_map *map_read)
{
    print_map(map_read);
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
                    printf(RED "We found something there [%c]\n at (i: %d, j: %d)\n" RESET, map_read->map[i][j], i, j);
                    return (EXIT_FAILURE);
                }
                is_line_empty = false;
                j++;
            }
        }
         if (is_line_empty)
             {
                 printf(RED "The line is empty \n" RESET);
                 return (EXIT_FAILURE);
             }
        i++;
    } 
    return (EXIT_SUCCESS);
}

//todo: Need to implement for the bottom row as well
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
            printf(RED "0 is not surrounded by a wall either at the top or bottom\n" RESET);
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
bool checking_for_diagonal_top_version(t_map *map)
{
    print_map(map);
    int i = 1, j;
    while(i < map->rows - 1)
    {
        j = 1;
        while (j < map->coloumns)
        {
            if(map->map[i][j] == 'S')
                j++;
            if(map->map[i][j] == '0')
            {
               if ((map->map[i - 1][j - 1] == 'S' && map->map[i - 1][j + 1] == '0')  || (map->map[i - 1][j - 1] == 'S' && map->map[i - 1][j + 1] == '0'))
                        j++;  
                if ((map->map[i - 1][j -1] != '1' && map->map[i - 1][j - 1] != '0') || (map->map[i - 1][j + 1] != '0' && map->map[i - 1][j + 1] != '1'))
                    {
                        printf(RED "Error [0] has a diagonal space at (i: %d, j: %d)\n", i, j);
                        return (EXIT_FAILURE);
                    }
            }
            j++;
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
    else if (checking_for_diagonal_top_version(map_check) == 1)
        return(EXIT_FAILURE);
    else if(check_for_rows_surrounded_map(map_check) == 1)
            return (EXIT_FAILURE);
    else if (check_map_is_surrounded_columns(map_check) == 1)
        return (EXIT_FAILURE);
   else if( get_player_position(map_check) == 1)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

/* ---- PRINTF's

* ----------- DIAGONAL MAP ----------------------
printf("[%c] at (row : %d, col: %d)\n", map->map[i][j], i, j); 
printf("Found a [%c] on the left diagonal\n", map->map[i - 1][j - 1]);
printf("Found a [%c] on the right diagonal\n", map->map[i - 1][j + 1]);
printf("[ -- Position is (i: %d, j: %d) -- ]\n", i, j); 1
*/