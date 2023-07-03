#include "../../inc/Cube3D.h"

bool is_map_line(const char *line)
{
    bool non_space_found = false;
    while (*line)
    {
        if (*line != '0' && *line != '1' && *line != 'S' && *line != ' ')
            return false;
        if (*line != ' ')
            non_space_found = true;
        line++;
    }
    return non_space_found;
}


void read_config_file(const char *filename, t_config_properties *file, t_map *map)
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
            file->floor_texture = ft_strdup(line + 2);
        else if(ft_strncmp(line, "C", 1) == 0)
            file->ceiling_texture = ft_strdup(line + 2);
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
    // cleanup(file, map);
    return ;
}

//todo: Implementation for Invalid path to the xpm file
// bool check_valid_path_for_path(t_config_properties *file)
// {
//     read_config_file()
    
// }

bool set_order_of_file(const char* filename)
{
    int fd;
    char *line;
    int set_value = 0;
    bool map_started = false;

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
                {
                    set_value = 7;
                    map_started = true;
                }
            else if (map_started && (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 || 
                 ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0 || 
                 ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0))
                {
                    printf("Offending line: '%s'\n", line);
                    printf(RED "Error: Configuration line found after map lines.\nReturning back \n" RESET);
                    free(line);
                    close(fd);
                    return (EXIT_FAILURE);
                }
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
* --------------  FOR READ FILE -------------------
printf("THE LINE ARE BEING READ ARE: [%s]\n", line);
printf("The string is %s\n", file->south_texture);
printf("The string is %s\n", file->east_texture);
printf("THe string is %s\n", file->north_texture);
printf("The string is %s\n", file->west_texture);
*/