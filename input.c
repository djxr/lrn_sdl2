#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#define NUM_TILES 26

/* MAYBE THESE SHOULD BE LESS GLOBAL */
int		d_sel = 0;
SDL_Window	*win = NULL;
SDL_Renderer	*rend = NULL;
SDL_Texture	*atlas = NULL;
enum bool {false, true} game_quit = false;

enum sprindex {/*{{{*/
	dude,
	mdude,
	van,
	panel,
	graves,
	ptank,
	vantank,
	puss,
	beefy,
	erect,
	mtank,
	obs,
	warms,
	dstank,
	airbus,
	choppa,
	jet,
	jumbo,
	bomber,
	missle,
	grabby,
	boat,
	pboat,
	sub,
	bship,
	carrier
};/*}}}*/

enum sprindex brush = graves;

int init()/*{{{*/
{
	SDL_Rect	d_bounds;
	SDL_DisplayMode d_mode;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)  // SDL_INIT_AUDIO if needed
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	int should_be_zero = SDL_GetCurrentDisplayMode(d_sel, &d_mode);

	if(should_be_zero != 0)
		SDL_Log("Could not get display mode for video display #%d: %s", d_sel, SDL_GetError());
	else if(SDL_GetDisplayBounds(d_sel, &d_bounds) != 0)
	{
		SDL_Log("SDL_GetDisplayBounds failed: %s", SDL_GetError());
		return 1;
	}
	
	win = SDL_CreateWindow
	(
		"An SDL2 win",
		d_bounds.x,
		d_bounds.y,
		d_bounds.w,
		d_bounds.h,
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE
	);

	if(win == NULL)
	{
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if(rend == NULL)
	{
		SDL_Log("Could not create renerer: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}/*}}}*/

int tini()/*{{{*/
{
	SDL_DestroyTexture(atlas);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}/*}}}*/

int main (int argc, char *argv[]) 
{
	int		i = 0;
	int		j = 0;
	SDL_Surface	*sur = NULL;
	SDL_Rect	tile[NUM_TILES];
	SDL_Rect	target;
	int		scale = 32;
	
/* HANDLE ARGUMENTS *//*{{{*/
	for(i = 1; i < argc; i++)
	{
		if(strncmp(argv[i], "-d", 3) == 0)
		{
			i++;
			d_sel = atoi(argv[i]);
		}else if(strncmp(argv[i], "-s", 3) == 0)
		{
			i++;
			scale = atoi(argv[i]);
		}
	}/*}}}*/

	init();

/* DEFINE TILE-ATLAS SRC_RECTS *//*{{{*/
	for(i = 0; i < NUM_TILES; i++)
	{
		tile[i].x = i * 16;
		tile[i].y = 0;
		tile[i].h = 16;
		tile[i].w = 16;
	}/*}}}*/

/* LOAD THE ATLAS */ /*{{{*/
	sur = SDL_LoadBMP("tiles.bmp");
	atlas = SDL_CreateTextureFromSurface(rend, sur);
	SDL_FreeSurface(sur);/*}}}*/
	SDL_Event e;

	while(!game_quit)
	{
		if(SDL_PollEvent(&e))/*{{{*/
		{
			switch(e.type)
			{
				case SDL_QUIT:
					SDL_Log("Program quit after %i ticks", e.quit.timestamp);
					game_quit = true;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
						case SDLK_q:
							SDL_Log("Program quit after %i ticks", e.quit.timestamp);
							game_quit = true;
							break;
					}
					break;
					
			}
		}/*}}}*/
		SDL_Delay(16); // REMOVE THIS WHEN YOU UPDATE LOGIC AND RENDERING BASED ON TIME!
		// RENDER ONLY WHAT NEEDS TO CHANGE!
		/* CLEAR RENDERER *//*{{{*/
		SDL_SetRenderDrawColor(rend,0,0,0,255);
		SDL_RenderClear(rend);/*}}}*/
		/* PAINT TILES TO THE RENDERER *//*{{{*/
		for(i = 0; i < 10; i++)
		{
			for(j = 0; j < 10; j++)
			{
				target.x = j * scale;
				target.y = i * scale;
				target.h = scale;
				target.w = scale;
				SDL_RenderCopy(rend, atlas, &tile[brush], &target);
			}
		}/*}}}*/
		SDL_RenderPresent(rend);
	}

	tini();
	printf("I ran till the end\n");
	return 0;
}
