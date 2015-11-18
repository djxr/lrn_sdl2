#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#define NUM_TILES 26

typedef enum {false, true} bool;
typedef enum sprindex{/*{{{*/
	clear,
	dude,
	pallete,
	panel,
	graves,
	clearbump,
	select,
	dblue,
	lblue,
	dgreen,
	lgreen,
	dred,
	lred,
	dyellow,
	lyellow,
	dteal,
	lteal,
	dpurpleflat,
	rock,
	tealflat,
	yellowflat,
	anotherflat,
	up,
	right,
	left,
	down
}sprindex;/*}}}*/
typedef enum special{/*{{{*/
	redkey_door,
	redkey,
	shotgun,
	devil_trap
}special;/*}}}*/
typedef struct tile{/*{{{*/
	int		id;
	sprindex	sp;
	SDL_Rect	loc;
	bool		walkable;
	bool		draw;
	special		keyword;
	
}tile;/*}}}*/
typedef struct cursor{/*{{{*/
	sprindex	sp;
	int		x;
	int		y;
}cursor;/*}}}*/

/* SHOULD BE LESS GLOBAL */
int		d_sel = 1;
SDL_Window	*win = NULL;
SDL_Renderer	*rend = NULL;
SDL_Texture	*atlas = NULL;
bool 		game_quit = false;
cursor ch =	{.sp = dude, .x = 20, .y = 11};
cursor m =	{.sp = select};

/* FIX: LOAD MAP FROM FILE */
int layer_base[22][40]=/*{{{*/
{
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,03,03,03,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,03,03,03,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00}
};/*}}}*/
int layer_atop[22][40]=/*{{{*/
{
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,18,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
{00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00}
};/*}}}*/

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

	SDL_ShowCursor(0);

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
	SDL_Rect	img_tile[NUM_TILES];
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
		img_tile[i].x = i * 16;
		img_tile[i].y = 0;
		img_tile[i].h = 16;
		img_tile[i].w = 16;
	}/*}}}*/

/* LOAD THE ATLAS */ /*{{{*/
	sur = SDL_LoadBMP("tiles.bmp");
	SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, 255, 0, 255));
	atlas = SDL_CreateTextureFromSurface(rend, sur);
	SDL_FreeSurface(sur);/*}}}*/

	SDL_Event 	e;
	Uint32		ms_update = 1000/120;
	Uint32		ms_render = 1000/60;
	//Uint32		ms_loop = ms_render * 2;
	Uint32		last_update = 0;
	Uint32		last_render = 0;
	//Uint32		last_loop = 0;
	
	int		bg_pulse = 0;

	while(!game_quit)
	{
		while(SDL_PollEvent(&e))/*{{{*/
		{
			switch(e.type)
			{
				case SDL_QUIT:
					SDL_Log("Program quit after %i ticks", e.quit.timestamp);
					game_quit = true;
					break;
				case SDL_MOUSEMOTION:
					m.x = e.motion.x / scale;
					m.y = e.motion.y / scale;
					break;
				case SDL_MOUSEWHEEL:
					scale += ((int)e.wheel.y)*8;
					if(scale < 8)
						scale = 8;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
						case SDLK_q:
							SDL_Log("Program quit after %i ticks", e.quit.timestamp);
							game_quit = true;
							break;
						case SDLK_UP:
						case SDLK_w:
							ch.sp = up;
							ch.y -= 1;
							break;
						case SDLK_LEFT:
						case SDLK_a:
							ch.sp = left;
							ch.x -= 1;
							break;
						case SDLK_RIGHT:
						case SDLK_d:
							ch.sp = right;
							ch.x += 1;
							break;
						case SDLK_DOWN:
						case SDLK_s:
							ch.sp = down;
							ch.y += 1;
							break;
					}
					break;
					
			}
		}/*}}}*/

		/* LOGIC *//*{{{*/
		if(SDL_TICKS_PASSED(SDL_GetTicks(), last_update + ms_update))
		{
			last_update = SDL_GetTicks();
			if(bg_pulse < 255)
				bg_pulse++;
			else
				bg_pulse = 0;
		}/*}}}*/

		/* RENDER ( FIX: RENDER ONLY THE SCREEN AND ONLY WHAT NEEDS TO CHANGE! ) *//*{{{*/
		if(SDL_TICKS_PASSED(SDL_GetTicks(), last_render + ms_render))
		{
			/* CLEAR RENDERER */
			last_render = SDL_GetTicks();
			SDL_SetRenderDrawColor(rend,bg_pulse,bg_pulse,bg_pulse,255);
			SDL_RenderClear(rend);

			/* PAINT TILES TO THE RENDERER */
			for(i = 0; i < 22; i++)
			{
				for(j = 0; j < 40; j++)
				{
					target.x = j * scale;
					target.y = i * scale;
					target.h = scale;
					target.w = scale;
					SDL_RenderCopy(rend, atlas, &img_tile[layer_base[i][j]], &target);
				}
			}
			for(i = 0; i < 22; i++)
			{
				for(j = 0; j < 40; j++)
				{
					target.x = j * scale;
					target.y = i * scale;
					target.h = scale;
					target.w = scale;
					SDL_RenderCopy(rend, atlas, &img_tile[layer_atop[i][j]], &target);
				}
			}
			target.x = ch.x * scale;
			target.y = ch.y * scale;
			target.h = scale;
			target.w = scale;
			SDL_RenderCopy(rend, atlas, &img_tile[ch.sp], &target);
			target.x = m.x * scale;
			target.y = m.y * scale;
			target.h = scale;
			target.w = scale;
			SDL_RenderCopy(rend, atlas, &img_tile[m.sp], &target);
		}/*}}}*/
		SDL_RenderPresent(rend);
		/* THROTTLE FIX: TIE TO LOGIC UPDATE *//*{{{*/
		//if(!SDL_TICKS_PASSED(SDL_GetTicks(), last_loop + ms_loop))
		//{
		//	SDL_Delay((SDL_GetTicks() - last_loop) + ms_loop);
		//}
		//last_loop = SDL_GetTicks();
		/* UNSATISFACTORY TROTTLE METHODOLOGY */
		SDL_Delay(1);/*}}}*/
	}

	tini();
	printf("I ran till the end\n");
	return 0;
}
