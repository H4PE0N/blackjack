
#ifndef RENDER_BOARD_SCREEN_H
#define RENDER_BOARD_SCREEN_H

bool render_game_board(Screen, Card*, Card*);

bool extract_file_image(Surface**, char[]);

bool extract_file_font(Font**, char[], int);

bool render_screen_image(Screen, Surface*, Rect);

bool render_screen_text(Screen, char[], Color, int, int, float);

bool default_folder_font(Font**, char[], int);

bool default_folder_image(Surface**, char[]);

bool render_screen_cards(Screen, Card[], int, int);

bool render_game_options(Screen);

bool render_player_values(Screen);

bool render_play_values(Screen);

bool render_result_screen(Screen, int, int);

#endif