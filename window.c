#include <stdio.h>
#include <SDL2/SDL.h>

int main (int argc, char *argv[]) 
{
	SDL_Window *window;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)  // SDL_INIT_AUDIO if needed
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}
	
	window = SDL_CreateWindow(
		"An SDL2 window",
		0,
		0,
		640,
		480,
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_MAXIMIZED
	);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Delay(3000);

	SDL_DestroyWindow(window);

	printf("I ran till the end\n");
	SDL_Quit();
	return 0;
}
