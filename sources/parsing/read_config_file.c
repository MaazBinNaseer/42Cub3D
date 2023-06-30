#include "../../inc/Cube3D.h"

bool is_map_line(const char *line)
{
    while (*line)
    {
        if (*line != '0' && *line != '1' && *line != 'S' && *line != ' ')
            return false;
        line++;
    }
    return true;
}

int read_config_file(const char *filename, t_config_properties *file, t_map *map)
{
    char *line; 
    int fd; 

    fd = open(filename, O_RDONLY);

    while((line = get_next_line(fd) )!= NULL)
    {
        if(ft_strncmp(line, "NO", 2) == 0)
            file->north_texture = ft_strdup(line + 3);
        else if(ft_strncmp(line, "SO", 2) == 0)
            file->south_texture = ft_strdup(line + 3);
        else if(ft_strncmp(line, "WE", 2) == 0)
            file->west_texture = ft_strdup(line + 3);
        else if(ft_strncmp(line, "EA", 2) == 0)
            file->east_texture = ft_strdup(line + 3);
        else if(ft_strncmp(line, "F", 1) == 0)
            file->floor_texture = ft_strdup(line + 3);
        else if(ft_strncmp(line, "C", 1) == 0)
            file->ceiling_texture = ft_strdup(line + 3);
        else if (is_map_line(line))
            break;
        free(line);
    }
     if (line != NULL)
    {
        read_map(fd, map, line);
        check_map(map);
    }
    close(fd);
    cleanup(file, map);
    return (0);
}

bool set_order_of_file(const char* filename)
{
    int fd;
    char *line;
    int set_value = 0;

    fd = open(filename, O_RDONLY);
      while((line = get_next_line(fd) )!= NULL)
        {
            if(ft_strncmp(line, "NO", 2) == 0)
                set_value = 1;
            else if(ft_strncmp(line, "SO", 2) == 0)
                set_value = 2;
            else if(ft_strncmp(line, "WE", 2) == 0) 
                set_value = 3;
            else if(ft_strncmp(line, "EA", 2) == 0) 
                set_value = 4;
            else if(ft_strncmp(line, "F", 2) == 0) 
                set_value = 5;
            else if(ft_strncmp(line, "C", 2) == 0) 
                set_value = 6;
            else if (is_map_line(line))
                set_value = 7;
            free(line);
        }
    close (fd);
    if(set_value != 7)
    {
        printf(RED "Error: The map line is not at the end.\nReturning back \n" RESET);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}





/*
printf("THE LINE ARE BEING READ ARE: [%s]\n", line);
printf("The string is %s\n", file->south_texture);
printf("The string is %s\n", file->east_texture);
printf("THe string is %s\n", file->north_texture);
printf("The string is %s\n", file->west_texture);
*/