#include "../../inc/Cube3D.h"

/* --------------------------------------------------------
* This function need to open the file and read the 
* contents of the map that is rows and coloumns to be used 
* later for validating map
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

int check_map_is_surronded(t_map *map_read)
{
    int i;
    int j; 

    i = 0;
    while(i < map_read->coloumns)
    {
        if(map_read->map[0][i] != '1'|| map_read->map[map_read->rows- 1][i] != '1')
        {
            printf("Invalid Map [ Map is supposed to be surrounded by Walls !]");
            return (1);
        }
        i++;
    }
    
    j= 1;
    while(j < (map_read->rows - 1))
    {
        if(map_read->map[j][0] != '1' || map_read->map[j][map_read->coloumns - 1] != '1')
        {
            printf("Invalid Map [ Map is supposed to be surrounded by Walls !]");
            return (1);
        }
        j++;
    }
    return (0);
}

