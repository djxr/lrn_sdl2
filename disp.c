#include <stdio.h>
#include <SDL2/SDL.h>

int main (int argc, char *argv[]) 
{
	int i;
	SDL_DisplayMode dmode;
	SDL_Window 	*window;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)  // SDL_INIT_AUDIO if needed
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	for(i = 0; i < SDL_GetNumVideoDisplays(); ++i)
	{
		int should_be_zero = SDL_GetCurrentDisplayMode(i, &dmode);

		if(should_be_zero != 0)
			SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
		else
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, dmode.w, dmode.h, dmode.refresh_rate);
	}
	
	window = SDL_CreateWindow
	(
		"An SDL2 window",
		0,
		0,
		640,
		480,
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_MAXIMIZED
	);

	if (window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Delay(5000);

	SDL_DestroyWindow(window);

	printf("I ran till the end\n");
	SDL_Quit();
	return 0;
}
