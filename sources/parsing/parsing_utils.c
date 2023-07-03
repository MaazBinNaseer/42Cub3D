#include "../../inc/Cube3D.h"

void free_map(t_map *map_read) 
{
    for(int i = 0; i < map_read->rows; i++) 
        free(map_read->map[i]);
    free(map_read->map);
}

void print_map(t_map *map) {
    printf("   ");
    for (int j = 0; j < map->coloumns; j++) {
        printf(YELL "%2d "RESET, j);
    }
    printf("\n");

    for (int i = 0; i < map->rows; i++) {
        printf(GRN "%2d " RESET, i);

        for (int j = 0; j < map->coloumns; j++) {
            printf(MAG "%2c " RESET, map->map[i][j]);
        }
        printf("\n");
    }
}

void cleanup(t_config_properties *file, t_map *map)
{
    int i;

    i = 0;
    free(file->north_texture);
    free(file->south_texture);
    free(file->west_texture);
    free(file->east_texture);
    free(file->floor_texture);
    free(file->ceiling_texture);

    while(i < map->rows)
    {
        free(map->map[i]);
        i++;
    }
    free(map->map);
}
