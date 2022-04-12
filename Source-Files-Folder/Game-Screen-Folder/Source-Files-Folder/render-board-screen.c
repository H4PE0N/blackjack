
#include "../Header-Files-Folder/screen-include-file.h"

bool render_game_board(Screen screen)
{
	Surface* boardImage = NULL;
	if(!extract_file_image(&boardImage, "../Source-Files-Folder/Game-Screen-Folder/Images-Folder/table.jpeg")) return false;
	
	Rect boardPosition = {0, 0, 800, 800};

	render_screen_image(screen, boardImage, boardPosition);



	Surface* cardImage = NULL;
	if(!extract_file_image(&cardImage, "../Source-Files-Folder/Game-Screen-Folder/Images-Folder/spades-ace.png")) return false;
	
	Rect cardPosition = {300, 300, 200, 200};

	render_screen_image(screen, cardImage, cardPosition);

	return true;
}

bool extract_file_image(Surface** image, char filename[])
{
	*image = IMG_Load(filename);

	return (*image != NULL);
}

bool extract_file_font(TTF_Font** font, char filename[], int size)
{
	*font = TTF_OpenFont(filename, size);

	return (*font != NULL);
}

bool render_screen_image(Screen screen, Surface* image, Rect position)
{
	Texture* texture = NULL;

	if(!make_surface_texture(&texture, screen.renderer, image)) return false;
	
	SDL_RenderCopy(screen.renderer, texture, NULL, &position);

	SDL_DestroyTexture(texture);

	return true;
}

bool render_screen_text(Screen screen, char text[], Rect position, Color color)
{
	TTF_Font* textFont = NULL;

	if(!extract_file_font(&textFont, (char*) FONT_FILE, FONT_SIZE)) return false;	

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(textFont, text, color); 

	SDL_Texture* message = SDL_CreateTextureFromSurface(screen.renderer, surfaceMessage);

	SDL_RenderCopy(screen.renderer, message, NULL, &position);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);

	return true;
}