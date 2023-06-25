#include "../../inc/Cube3D.h"

int check_map(t_map *map_check)
{
    if(check_map_is_surrounded_rows(map_check) == 1)
        return (EXIT_FAILURE);
    else if (check_map_is_surrounded_columns(map_check) == 1)
        return (EXIT_FAILURE);
   else if( get_player_position(map_check) == 1)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}