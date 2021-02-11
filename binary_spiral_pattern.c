
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "mathfont.h"
#include <math.h>

#define DIMENSIONS 800
#define B4SCALED 200
#define TEXTAREAHEIGHT 15
#define INNERSQR 170
#define NUMPIXELS INNERSQR * INNERSQR

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

enum chars {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
#define NUMBEROFCHARS 18

const int CENTER = B4SCALED / 2;

typedef struct character {
	unsigned int * xcoords;
	unsigned int * ycoords;
	unsigned int size;
} Character;

typedef struct point {
	int x;
	int y;
	int color;
} Mpoint;

void drawPassLongLongInt(SDL_Renderer * renderer, SDL_Point * points, long long int n) {
	int ysign = -1;
	int xsign = 1;
	int xchange = 1;
	int ychange = 1;
	int number = 0;
	int centeroffsetsxy[2] = {CENTER, CENTER};
	int xmov = 0;
	int ymov = 0;
	int bit = 0;
	int loc = 0;
	int highestsetbit = 0;
	int c;
	highestsetbit = 64 - __builtin_clzll(n);

	if (highestsetbit == 0) {
		highestsetbit = 1;
	}

	while (number < NUMPIXELS) {
		if (number == 0) {
			if (n & 1 << bit) {
				SDL_Point p = {centeroffsetsxy[0], centeroffsetsxy[1]};
				points[loc] = p;
				loc++;
			}
			
		}

		for (xmov = 0; xmov < xchange; xmov++) {
			bit++;
			bit = bit % highestsetbit;
			number += 1;
			if (number < NUMPIXELS) {
				centeroffsetsxy[0] += 1 * xsign;
				if (n & 1 << bit) {
					SDL_Point p = {centeroffsetsxy[0], centeroffsetsxy[1]};
					points[loc] = p;
					loc++;
				}
			}
		}

		for (ymov = 0; ymov < ychange; ymov++) {
			number += 1;
			bit++;
			bit = bit % highestsetbit;
			if (number < NUMPIXELS) {
				centeroffsetsxy[1] += 1 * ysign;
				if (n & 1 << bit) {
					SDL_Point p = {centeroffsetsxy[0], centeroffsetsxy[1]};
					points[loc] = p;
					loc++;				}
			}
		}
		ysign *= -1;
		xsign *= -1;
		xchange += 1;
		ychange += 1;
	}
	

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoints(renderer, points, loc);
	SDL_RenderPresent(renderer);
	SDL_Delay(30);
}

void mainDrawingFunction(SDL_Renderer * renderer, int nchars, 
	                          int * array, Character * chars) {
	int c, ch;
	SDL_SetRenderDrawColor(renderer, 0,0,0, 0xFF);
	
	SDL_RenderClear(renderer);	
	
	

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
	for (ch = 0; ch < nchars; ch++) {
		SDL_Point points[chars[array[ch]].size];
		for (c = 0; c < chars[array[ch]].size; c++) {
			SDL_Point p = {chars[array[ch]].xcoords[c] + ch * 10, 
			               chars[array[ch]].ycoords[c]};
			points[c] = p;
		}
		SDL_RenderDrawPoints(renderer, points, chars[array[ch]].size);
	}
}

int main(int argc, char ** argv) {
	int str[NUMBEROFCHARS];
	char numstr[NUMBEROFCHARS] = {0};
	int nchars = 0;
	long long int number = 0;
	int c;

	SDL_Point points[NUMPIXELS];

	Character characters[NUMBEROFCHARS];

	characters[ZERO].xcoords = zerosxcoords;
	characters[ZERO].ycoords = zerosycoords;
	characters[ZERO].size = zerospixels;
	
	characters[ONE].xcoords = onesxcoords;
	characters[ONE].ycoords = onesycoords;
	characters[ONE].size = onespixels;

	characters[TWO].xcoords = twosxcoords;
	characters[TWO].ycoords = twosycoords;
	characters[TWO].size = twospixels;

	characters[THREE].xcoords = threesxcoords;
	characters[THREE].ycoords = threesycoords;
	characters[THREE].size = threespixels;

	characters[FOUR].xcoords = foursxcoords;
	characters[FOUR].ycoords = foursycoords;
	characters[FOUR].size = fourspixels;

	characters[FIVE].xcoords = fivesxcoords;
	characters[FIVE].ycoords = fivesycoords;
	characters[FIVE].size = fivespixels;

	characters[SIX].xcoords = sixsxcoords;
	characters[SIX].ycoords = sixsycoords;
	characters[SIX].size = sixspixels;

	characters[SEVEN].xcoords = sevensxcoords;
	characters[SEVEN].ycoords = sevensycoords;
	characters[SEVEN].size = sevenspixels;

	characters[EIGHT].xcoords = eightsxcoords;
	characters[EIGHT].ycoords = eightsycoords;
	characters[EIGHT].size = eightspixels;

	characters[NINE].xcoords = ninesxcoords;
	characters[NINE].ycoords = ninesycoords;
	characters[NINE].size = ninespixels;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("%s\n", SDL_GetError());
		return 0;
	}

	window = SDL_CreateWindow("Binary Spiral", 
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	DIMENSIONS, DIMENSIONS, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 200, 200);

	// event loop
	SDL_Event event;
	int kill = 0;
	while (!kill) {
		while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			kill = 1;
			break;
			} 
		else if (event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_0 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = 0;
						numstr[nchars] = '0';
						nchars++;
						number = atoll(numstr);
					}	
					break;
				} 
					
				case SDLK_1 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = 1;
						numstr[nchars] = '1';
						nchars++;
						number = atoll(numstr);
					}	
					break;
				} 

				case SDLK_2 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = 2;
						numstr[nchars] = '2';
						nchars++;
						number = atoll(numstr);
					}	
					break;
				} 

				case SDLK_3 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = THREE;
						numstr[nchars] = '3';
						nchars++;
						number = atoll(numstr);
					}	
					break;
				} 
					

				case SDLK_4 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = FOUR;
						numstr[nchars] = '4';
						nchars++;
						number = atoll(numstr);
					}	
					break;
				} 

				case SDLK_5 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = FIVE;
						numstr[nchars] = '5';
						nchars++;
						number = atoll(numstr);
					}	
					break;
				} 

				case SDLK_6 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = SIX;
						numstr[nchars] = '6';
						nchars++;
						number = atoll(numstr);
					}	
					break;				
				} 

				case SDLK_7 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = SEVEN;
						numstr[nchars] = '7';
						nchars++;
						number = atoll(numstr);
					}	
					break;
				}

				case SDLK_8 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = EIGHT;
						numstr[nchars] = '8';
						nchars++;
						number = atoll(numstr);
					}	
					break;
				} 

				case SDLK_9 : {
					if (nchars < NUMBEROFCHARS) {
						str[nchars] = NINE;
						numstr[nchars] = '9';
						nchars++;
						number = atoll(numstr);
						
					}	
					break;
				} 

				case SDLK_BACKSPACE : {
					if (nchars > 0) {
						nchars--;
						numstr[nchars] = '\0';
						number = atoll(numstr);	
					}		
					break;
				}

				case SDLK_UP : {
					number++;
				}
				break;

				case SDLK_DOWN : {
					number--;
				}
				break;

				case SDLK_LEFT : {
					number /= 2;
				}
				break;

				case SDLK_RIGHT : {
					number *= 2;
				}
				break;
			}
	      }
		}
		//printf("%d", nchars);	
		mainDrawingFunction(renderer, nchars, str, &characters);

		drawPassLongLongInt(renderer, &points,  number);

		// actually display  the render
		SDL_RenderPresent(renderer);
		SDL_Delay(30);
	}
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}