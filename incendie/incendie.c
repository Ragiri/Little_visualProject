#include "incendie.h"


t_bunny_pallet *std_init_pallet(t_bunny_pallet *pallet) {
    pallet = calloc(129, sizeof(t_bunny_pallet));
    pallet[0].pallet.full = BLACK;
    for (int i = 1; i != 128; i++) {
        pallet[i].nb = i;
        if (i <= 32) {
            pallet[i].pallet.argb[ALPHA_CMP] = 128;
            pallet[i].pallet.argb[RED_CMP] = i * (255 / 32);
            pallet[i].pallet.argb[GREEN_CMP] = 0;
            pallet[i].pallet.argb[BLUE_CMP] = 0;
            continue;
        } if (i <= 64) {
            pallet[i].pallet.argb[ALPHA_CMP] = 128;
            pallet[i].pallet.argb[RED_CMP] = 255;
            pallet[i].pallet.argb[GREEN_CMP] = (i - 32) * (255 / 32);
            pallet[i].pallet.argb[BLUE_CMP] = 0;
            continue;
        } if (i <= 96) {
            pallet[i].pallet.argb[ALPHA_CMP] = 128;
            pallet[i].pallet.argb[RED_CMP] = 255;
            pallet[i].pallet.argb[GREEN_CMP] = 255;
            pallet[i].pallet.argb[BLUE_CMP] = (i - 64) * (255 / 32);
            continue;
        }
        pallet[i].pallet.full = WHITE;
    }
    return pallet;
}


int **std_init_map(t_bunny_pallet *pallet, t_bunny_pixelarray *picture) {
    int **map = calloc( picture->clipable.clip_height + 1, sizeof(int*));

    srand(time(NULL));
    for (int i = 0; i < (int)picture->clipable.clip_height; i++) {
        map[i] = calloc((picture->clipable.clip_width + 2), sizeof(int));
        if (i == (int)picture->clipable.clip_height - 1 || i == (int)picture->clipable.clip_height - 2) {
            for(int x = 0; x < (int)(picture->clipable.clip_width + 2); x++) {
                map[i][x] = pallet[rand() % 129].nb;
            }
        }
    }
    return (map);
}

int **std_draw_map(int **map, t_bunny_pixelarray *picture) {
    for (int y = (int)picture->clipable.clip_height - 3; y >= 0; y--) {
        for (int x = 1; x < (int)picture->clipable.clip_width + 1; x++) {
            map[y][x] = (map[y + 1][x] + map[y + 1][x - 1] + map[y + 1][x + 1] + map[y + 2][x]) / 4;
            map[y][x] -= rand() % 2;
            map[y][x] += rand() % 2;
            //printf("%d\n", map[y][x]);
        }
    }
    return ( map);
}

void std_draw_fire(int **map, t_bunny_pallet *pallet, t_bunny_pixelarray *picture) {
    int i = 0;
    for (int y = 0; y != (int)picture->clipable.clip_height ; y++, i++) {
        for (int x = 1; x < (int)(picture->clipable.clip_width); x++, i++) {
            ((t_color*)picture->pixels)[i] = pallet[map[y][x]].pallet;
        }
    }
}


int main() {
    t_bunny_data data;
    data.pixel = bunny_new_pixelarray(500, 400);
    data.win = bunny_start(500, 400, false, "truc");
    data.pallet = std_init_pallet(data.pallet);
    data.map = std_init_map(data.pallet, data.pixel);
    data.map = std_draw_map(data.map, data.pixel);

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