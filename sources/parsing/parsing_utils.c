#include "../../inc/Cube3D.h"

void free_map(t_map *map_read) 
{
    for(int i = 0; i < map_read->rows; i++) 
        free(map_read->map[i]);
    free(map_read->map);
}

void print_map(t_map *map) {
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->coloumns; j++) {
            printf("%c ", map->map[i][j]);
        }
        printf("\n");
    }
}