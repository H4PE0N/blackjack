
#include "../Header-Files-Folder/master-include-file.h"

int main(int argc, char* argv[])
{
	Screen screen;

	if(!setup_screen_struct(&screen, 800, 800, "treestump\0"))
	{
		printf("Could not setup screen!\n");

		return false;
	}

	render_game_board(screen);

	SDL_UpdateWindowSurface(screen.window);

	Event event;

	while(event.type != SDL_QUIT && !(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
	{
		SDL_WaitEvent(&event);

		SDL_Delay(100);
	}


	printf("free_screen_struct\n");
	free_screen_struct(screen);

	return false;
}