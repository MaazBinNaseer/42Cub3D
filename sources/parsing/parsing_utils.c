#include "../../inc/Cube3D.h"

void free_map(t_map *map_read) 
{
    for(int i = 0; i < map_read->rows; i++) 
        free(map_read->map[i]);
    free(map_read->map);
}

void print_map(t_map *map) {
    // Print column indices
    printf("   ");
    for (int j = 0; j < map->coloumns; j++) {
        printf(YELL "%2d "RESET, j);
    }
    printf("\n");

    for (int i = 0; i < map->rows; i++) {
        // Print row index
        printf(GRN "%2d " RESET, i);

        for (int j = 0; j < map->coloumns; j++) {
            printf(MAG "%2c " RESET, map->map[i][j]);
        }
        printf("\n");
    }
}
