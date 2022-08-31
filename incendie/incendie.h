#include <lapin.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



typedef struct s_bunny_pallet {
    t_bunny_color pallet;
    int nb;
} t_bunny_pallet;

typedef struct s_bunny_data {
    t_bunny_pixelarray *pixel;
    t_bunny_window *win;
    t_bunny_pallet *pallet;
    int **map;
} t_bunny_data;


t_bunny_pallet *std_init_pallet(t_bunny_pallet *pallet);

int **std_draw_map(int **map, t_bunny_pixelarray *picture);

void std_draw_fire(int **map,  t_bunny_pallet *pallet, t_bunny_pixelarray *picture);

int **std_init_map( t_bunny_pallet *pallet, t_bunny_pixelarray *picture);

t_bunny_response display_function(void *d);

t_bunny_response loop_function(void *d);

t_bunny_response eventHandler(t_bunny_event_state state, t_bunny_keysym key, void *data);

void std_clear_pixelarray(t_bunny_pixelarray *picture, unsigned int color);