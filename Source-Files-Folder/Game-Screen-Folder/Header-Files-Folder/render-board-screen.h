
#ifndef RENDER_BOARD_SCREEN_H
#define RENDER_BOARD_SCREEN_H

bool render_game_board(Screen);

bool extract_file_image(Surface**, char[]);

bool extract_file_font(Font**, char[], int);

bool render_screen_image(Screen, Surface*, Rect);

bool render_screen_text(Screen, char[], Rect, Color);

bool default_folder_font(Font**, char[], int);

bool default_folder_image(Surface**, char[]);

#endif