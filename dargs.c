#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

int main (int argc, char *argv[]) 
{
	int i = 0;
	int d_sel = 0;

	for(i = 1; i < argc; i++)
	{
		if(strncmp(argv[i], "-d", 3) == 0)
		{
			i++;
			d_sel = atoi(argv[i]);
		}
	}
	printf("Selected Display is #%d\n", d_sel);

	SDL_DisplayMode d_mode;
	SDL_Rect d_b;
	SDL_Window 	*window;
	
	if(SDL_Init(SDL_INIT_VIDEO) != 0)  // SDL_INIT_AUDIO if needed
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	int should_be_zero = SDL_GetCurrentDisplayMode(d_sel, &d_mode);

	if(should_be_zero != 0)
		SDL_Log("Could not get display mode for video display #%d: %s", d_sel, SDL_GetError());
	else
	{
		SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", d_sel, d_mode.w, d_mode.h, d_mode.refresh_rate);
		if(SDL_GetDisplayBounds(d_sel, &d_b) != 0)
		{
			SDL_Log("SDL_GetDisplayBounds failed: %s", SDL_GetError());
			return 1;
		}
		SDL_Log("Display #%d bounds: x %d-%d , y %d-%d", d_sel, d_b.x, d_b.x + d_b.w, d_b.y, d_b.y + d_b.h);
	}
	
	window = SDL_CreateWindow
	(
		"An SDL2 window",
		d_b.x,
		d_b.y,
		d_b.w,
		d_b.h,
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_MAXIMIZED
	);

	if(window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Delay(2000);

	SDL_DestroyWindow(window);

	printf("I ran till the end\n");
	SDL_Quit();
	return 0;
}
