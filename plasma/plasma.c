#include "plasma.h"


t_bunny_pallet *std_init_pallet(t_bunny_pallet *pallet) {
    pallet = calloc(129, sizeof(t_bunny_pallet));
    pallet[0].pallet.full = BLACK;
    for (int i = 1; i != 128; i++) {
        pallet[i].nb = i;
        pallet[i].pallet.argb[ALPHA_CMP] = 128;
        pallet[i].pallet.argb[RED_CMP] = 128.0 + 128 * sin(3.1415 * i / 32.0);
        pallet[i].pallet.argb[GREEN_CMP] = 128.0 + 128 * sin(3.1415 * i / 64.0);
        pallet[i].pallet.argb[BLUE_CMP] = 128.0 + 128 * sin(3.1415 * i / 128.0);
    }
    return pallet;
}


int **std_init_map(t_bunny_pallet *pallet, t_bunny_pixelarray *picture) {
    int **map = calloc( picture->clipable.clip_height + 1, sizeof(int*));

    for (int i = 0; i < (int)picture->clipable.clip_height; i++) {
        map[i] = calloc((picture->clipable.clip_width + 2), sizeof(int));
    }
    return (map);
}

int **std_draw_map(int **map, t_bunny_pixelarray *picture, double buffer ) {
    double f = 0;

    for (int x = 0; x < (int)(picture->clipable.clip_width  + 1); x++) {
        for (int y = 0; y < (int)picture->clipable.clip_height - 1; y++) {
			int res = (128.0 * sin(x / buffer))
                + (128.0 * sin(y / buffer))
                + (128.0 * cos(sqrt((double)((x - (double)(picture->clipable.clip_width  + 1) / 2.0)
                * (x - (double)(picture->clipable.clip_width  + 1) / 2.0) + (y - (double)picture->clipable.clip_height / 2.0) * (y - (double)picture->clipable.clip_height / 2.0))) / 8.0))
                 /  M_PI;
            map[y][x] = res;
            f++;
        }
    }
    return ( map);
}

void std_draw_plasma(int **map, t_bunny_pallet *pallet, t_bunny_pixelarray *picture) {
    int i = 0;
    for (int y = 0; y != (int)picture->clipable.clip_height ; y++, i++) {
        for (int x = 1; x < (int)(picture->clipable.clip_width); x++, i++) {
            ((t_color*)picture->pixels)[i] = pallet[map[y][x]].pallet;
        }
    }
}


int main() {
    t_bunny_data data;

    srand(time(NULL));
    data.pixel = bunny_new_pixelarray(1200, 800);
    data.win = bunny_start(1200, 800, false, "truc");
    data.pallet = std_init_pallet(data.pallet);
    data.map = std_init_map(data.pallet, data.pixel);
    data.map = std_draw_map(data.map, data.pixel, 16.0);
    data.buffer = 16.0;
    data.direction = 1.0;

    bunny_clear(&data.win->buffer, BLACK);
    bunny_set_loop_main_function(loop_function);
    bunny_set_display_function(display_function);
    bunny_set_key_response(eventHandler);
    bunny_loop(data.win, 60, &data);
    bunny_stop(data.win);
    free(data.pallet);
    free(data.map);
    return (0);
}