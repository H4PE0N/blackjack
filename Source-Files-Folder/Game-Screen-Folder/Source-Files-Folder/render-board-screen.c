
#include "../Header-Files-Folder/screen-include-file.h"

bool default_folder_image(Surface** image, char filename[])
{
	char filePath[256];

	sprintf(filePath, "%s/%s", IMAGE_FOLDER, filename);

	return extract_file_image(image, filePath);
}

bool default_folder_font(Font** font, char filename[], int size)
{
	char filePath[256];

	sprintf(filePath, "%s/%s", FONT_FOLDER, filename);

	return extract_file_font(font, filePath, size);
}

bool render_game_board(Screen screen)
{
	Surface* tableImage = NULL;
	if(!default_folder_image(&tableImage, (char*) TABLE_IMAGE)) return false;
	
	Rect boardPosition = {0, 0, 800, 800};

	render_screen_image(screen, tableImage, boardPosition);



	Surface* cardImage = NULL;
	if(!default_folder_image(&cardImage, "spades-three.png")) return false;
	
	Rect cardPosition = {300, 300, CARD_WIDTH, CARD_HEIGHT};

	render_screen_image(screen, cardImage, cardPosition);


	Surface* cardImage2 = NULL;
	if(!default_folder_image(&cardImage2, "hearts-ace.png")) return false;
	
	Rect cardPosition2 = {340, 300, CARD_WIDTH, CARD_HEIGHT};

	render_screen_image(screen, cardImage2, cardPosition2);

	return true;
}

bool extract_file_image(Surface** image, char filePath[])
{
	return ( (*image = IMG_Load(filePath)) != NULL);
}

bool extract_file_font(Font** font, char filePath[], int size)
{
	return ( (*font = TTF_OpenFont(filePath, size)) != NULL);
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
	Font* textFont = NULL;

	if(!default_folder_font(&textFont, (char*) FONT_FILE, FONT_SIZE)) return false;	

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(textFont, text, color); 

	SDL_Texture* message = SDL_CreateTextureFromSurface(screen.renderer, surfaceMessage);

	SDL_RenderCopy(screen.renderer, message, NULL, &position);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);

	return true;
}