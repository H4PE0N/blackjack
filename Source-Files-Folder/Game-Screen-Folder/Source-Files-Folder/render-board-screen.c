
#include "../Header-Files-Folder/screen-include-file.h"

bool create_card_filename(char* filename, Card card)
{
	unsigned int suit = CARD_SUIT_MACRO(card);
	unsigned int rank = CARD_RANK_MACRO(card);

	if(!NUMBER_IN_BOUNDS(suit, 1, DECK_SUITS) || !NUMBER_IN_BOUNDS(rank, 1, DECK_RANKS)) return false;

	sprintf(filename, CARD_FILE_MALL, SUIT_STRINGS[suit], RANK_STRINGS[rank]);

	return true;
}

bool extract_card_image(Surface** image, Card card)
{
	char filename[256];

	if(!create_card_filename(filename, card)) return false;

	return default_folder_image(image, filename);
}

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

bool render_game_board(Screen screen, Card* playerCards, Card* dealerCards)
{
	Surface* tableImage = NULL;
	if(!default_folder_image(&tableImage, (char*) TABLE_IMAGE)) return false;
	
	Rect tablePosition = {0, 0, 800, 800};
	
	if(!render_screen_image(screen, tableImage, tablePosition)) return false;


	if(!render_screen_cards(screen, dealerCards, 400, 120)) return false;

	if(!render_screen_cards(screen, playerCards, 400, 680)) return false;


	int playerValue = 0;

	playing_cards_value(&playerValue, playerCards);

	char text[200];

	sprintf(text, "Value: %d", playerValue);

	Rect position = {580, 700, 200, 40};

	Color color = {255, 255, 255};

	render_screen_text(screen, text, position, color);


	return true;
}

bool render_screen_card(Screen screen, Card card, int width, int height)
{
	Surface* cardImage = NULL;

	if(!extract_card_image(&cardImage, card)) return false;

	Rect position = {width, height, CARD_WIDTH, CARD_HEIGHT};

	return render_screen_image(screen, cardImage, position);
}

bool render_screen_cards(Screen screen, Card cards[], int width, int height)
{
	unsigned int amount = card_array_amount(cards);

	int renderHeight = height - (CARD_HEIGHT / 2);
	int startWidth = width - ((CARD_MARGIN * (amount - 1) + CARD_WIDTH) / 2);

	for(int index = 0; index < amount; index += 1)
	{
		int renderWidth = startWidth + (CARD_MARGIN * index);

		if(!render_screen_card(screen, cards[index], renderWidth, renderHeight)) return false;
	}

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