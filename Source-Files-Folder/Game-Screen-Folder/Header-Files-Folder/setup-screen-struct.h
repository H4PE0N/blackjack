
#ifndef SETUP_BOARD_SCREEN_H
#define SETUP_BOARD_SCREEN_H

bool make_screen_window(Window**, unsigned int, unsigned int, char[]);

bool make_window_surface(Surface**, Window*);

bool make_surface_renderer(Renderer**, Surface*);

bool make_surface_texture(Texture**, Renderer*, Surface*);

bool setup_screen_struct(Screen*, unsigned int, unsigned int, char[]);

void free_screen_struct(Screen);

#endif
