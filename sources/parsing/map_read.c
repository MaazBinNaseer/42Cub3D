#include "../../inc/Cube3D.h"

/* --------------------------------------------------------
* This function need to open the file and read the 
* contents of the map that is rows and coloumns to be used 
* later for validating map
//! Error for more than 100 lines (implementation)
---------------------------------------------------------- */
int read_map(const char *filename, t_map *map_read)
{
    char *line;
    int fd_map;
    int current_columns;

    fd_map= open(filename, O_RDONLY);
    if (fd_map == -1) {
        perror("Failed to open the map file.\n");
        return (1);
    }   
    map_read->map = ft_calloc(100, sizeof(char *));
    map_read->rows = 0;
    map_read->coloumns = 0;
    while((line = get_next_line(fd_map) )!= NULL)
    {
      
        map_read->map[map_read->rows] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
        ft_strcpy(map_read->map[map_read->rows], line);
        current_columns = ft_strlen(line);
        if(current_columns > map_read->coloumns)
            map_read->coloumns = current_columns - 1;
        map_read->rows++;
        free(line);
    }
    printf("The columns are as follows: [%d]\n", map_read->coloumns);
    printf("The rows are as follows: [%d]\n", map_read->rows);
    close(fd_map);
    return (0);
}

/* --------------------------------------------
* Checks the coloums and the rows of the wall to be 
* validated first. 
-----------------------------------------------*/
int check_map_is_surronded(t_map *map_read)
{
    int i;
    int j; 

    i = 0;
    while(i < map_read->coloumns)
    {
        if(map_read->map[0][i] != '1'|| map_read->map[map_read->rows- 1][i] != '1')
        {
            printf(RED "Invalid Map [ Map is supposed to be surrounded by Walls !]\n" RESET);
            return (1);
        }
        i++;
    }
    j= 1;
    while(j < (map_read->rows - 1))
    {
        if(map_read->map[j][0] != '1' || map_read->map[j][map_read->coloumns - 1] != '1')
        {
            printf(RED "Invalid Map [ Map is supposed to be surrounded by Walls !]" RESET);
            return (1);
        }
        j++;
    }
    return (0);
}
/* -------------------------------------------------------
* Finds the coordinates of the player in any position of 
* the map, no duplications of the player is allowed. 
--------------------------------------------------------*/
int get_player_position(t_map *map_read)
{
    int i = 0;

    while(i < map_read->rows)
    {
        int j = 0;
        while(j < map_read->coloumns)
        {
            if (map_read->map[i][j] == 'N' || map_read->map[i][j] == 'S' ||
                map_read->map[i][j] == 'E' || map_read->map[i][j] == 'W')
            {
                // printf("I have found the player at position [%d][%d].\n", i, j);
                map_read->player_position = i * map_read->coloumns + j;
                map_read->player++;
                // printf("The total number of players are %d\n", map_read->player);
                break;
            }
            j++;
        }
        i++;
    }  
    check_for_error_map(map_read);
    return (map_read->player_position);
}
bool check_for_error_map(t_map *map_read)
{
    if(map_read->player > 1)
    {
        printf( RED "The player should be only 1. [No Duplications are allowed]\n");
        printf("[-- We have found [%d] players in the map --]\n" RESET, map_read->player);
        return (EXIT_FAILURE);
    }
    else if (map_read->player == 0)
    {
        printf(RED "Player is Nowhere to be found in the map !\n" RESET);
        return (EXIT_FAILURE);
    }
    else if(map_read->rows > 100)
    {
        printf(RED "Too many lines of rows are there! Reduction required\n" RESET);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

