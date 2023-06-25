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

/* ------------------------------------------------
* Checks  the rows of the wall to be validated first. 
---------------------------------------------------*/
int check_map_is_surrounded_rows(t_map *map_read)
{
    int i = -1;
 
    size_t first_row = ft_strlen(map_read->map[0]) - 1;
    size_t last_row = ft_strlen(map_read->map[map_read->rows - 1]);
    while((size_t )i++ < first_row)
    {
        if(map_read->map[0][i] != '1')
            {
                printf(RED "INVALID MAP\n" RESET);
                return (EXIT_FAILURE);
            }
    }
    i = -1;
    while((size_t)i++ < last_row)
    {
         if(map_read->map[map_read->rows - 1][i] != '1')
            {
                printf(RED "INVALID MAP\n" RESET);
                return (EXIT_FAILURE);
            }
    }
    return (0);
}

int check_map_is_surrounded_columns(t_map *map_read)
{
    size_t rows = map_read->rows;
    size_t i = 0;
    while(i < rows) //*Accessing the first row [subjected to change]
    {
        if(map_read->map[i][0] != '1')
        {
            printf(RED "INVALID MAP\n" RESET);
            return (EXIT_FAILURE);
        }      
        i++;
    }
    i= 0;
    while(i < rows) //* Accessing the last column
    {
        size_t row_length = ft_strlen(map_read->map[i]);
        // printf("The row length is %ld\n", row_length);
        // printf("Printing the last value of the last columns %c\n", map_read->map[i][row_length - 2]);
        if(map_read->map[i][row_length - 2] != '1')
        {
            printf(RED "INVALID MAP\n" RESET);
            return (EXIT_FAILURE);
        }
        else
            printf("The last coloumn variables are [%c]\n", map_read->map[i][row_length - 2]);
        i++;
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
        int row_length = ft_strlen(map_read->map[i]);

        while(j < row_length)   // iterate over the current row only
        {
            if (map_read->map[i][j] == 'N' || map_read->map[i][j] == 'S' ||
                map_read->map[i][j] == 'E' || map_read->map[i][j] == 'W')
            {
                map_read->player_position.x = i;
                map_read->player_position.y = j;
                map_read->player++;
                printf("The player position is x: %d | y: %d -- \n", map_read->player_position.x, map_read->player_position.y);
                break;
            }
            j++;
        }
        i++;
    }  
    check_for_error_map(map_read);
    return (0);
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

