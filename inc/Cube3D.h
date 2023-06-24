#ifndef CUBE_3D_H
#define CUBE_3D_H


#include <stdio.h>
#include <stdbool.h>
#include "../sources/utils/Libft/libft.h"
#include "../sources/utils/Libft/get_next_line.h"


typedef struct s_map
{
    char **map;
    int rows;
    int coloumns;

} t_map;


/* --------------------------------------------------------
*------------------------- MAP READING ------------------
---------------------------------------------------------- */
// char *read_map(const char *filename, t_map *map);
int read_map(const char *filename, t_map *map);
int check_map_is_surronded(t_map *map_read);



/* --------------------------------------------------------
*-------------------------UTILS --------------------------
---------------------------------------------------------- */
int	ft_strncmp(const char *s1, const char *s2, size_t num);



#endif