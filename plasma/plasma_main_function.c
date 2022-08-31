
#include "plasma.h"

t_bunny_response eventHandler(t_bunny_event_state state, t_bunny_keysym key, void *data) {
    (void)data;
    return state == GO_DOWN && key == BKS_ESCAPE ? EXIT_ON_SUCCESS : GO_ON;
}

t_bunny_response loop_function(void *d) {
    t_bunny_data *data = (t_bunny_data*)d;
    
    data->buffer =  data->buffer + data->direction;
    if (data->buffer <= 1.0)
        data->direction = -1.0;
    if (data->buffer >= 16.0)
        data->direction = 1.0;
    return (GO_ON);
}


t_bunny_response display_function(void *d) {
    t_bunny_data *data = (t_bunny_data*)d;

    std_clear_pixelarray(data->pixel, BLACK);
    data->map = std_draw_map(data->map, data->pixel, data->buffer);
    std_draw_plasma(data->map, data->pallet, data->pixel);
    bunny_blit(&data->win->buffer, &data->pixel->clipable, &(t_bunny_position){0, 0});
    bunny_display(data->win);
    return (GO_ON);
}
void std_clear_pixelarray(t_bunny_pixelarray *picture, unsigned int color) {
    for(int i = 0; i < (int)(picture->clipable.clip_width * picture->clipable.clip_height) ; i++) {
        ((t_color*)picture->pixels)[i].full = color;
    }
}