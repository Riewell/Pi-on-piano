/*  Pi on piano

  Playing Pi with notes from piano
  Version 1.0

  Copyright 2015 Konstantin Zyryanov <post.herzog@gmail.com>
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
  MA 02110-1301, USA.
*/

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Pi
char Pi[1001]="1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989";

//The sound effects that will be used
Mix_Chunk *w0 = NULL;
Mix_Chunk *w1 = NULL;
Mix_Chunk *w2 = NULL;
Mix_Chunk *w3 = NULL;
Mix_Chunk *w4 = NULL;
Mix_Chunk *w5 = NULL;
Mix_Chunk *w6 = NULL;
Mix_Chunk *w7 = NULL;
Mix_Chunk *w8 = NULL;
Mix_Chunk *w9 = NULL;

int init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_AUDIO ) == -1 )
    {
        return 1;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return 1;
    }

    //If everything initialized fine
    return 0;
}

int load_files()
{
    //Load the sounds of notes
    w0 = Mix_LoadWAV( "Notes/w0.wav" );
    w1 = Mix_LoadWAV( "Notes/w1.wav" );
    w2 = Mix_LoadWAV( "Notes/w2.wav" );
    w3 = Mix_LoadWAV( "Notes/w3.wav" );
    w4 = Mix_LoadWAV( "Notes/w4.wav" );
    w5 = Mix_LoadWAV( "Notes/w5.wav" );
    w6 = Mix_LoadWAV( "Notes/w6.wav" );
    w7 = Mix_LoadWAV( "Notes/w7.wav" );
    w8 = Mix_LoadWAV( "Notes/w8.wav" );
    w9 = Mix_LoadWAV( "Notes/w9.wav" );
    
    //If there was a problem loading the sounds
    if( ( w0 == NULL ) || ( w1 == NULL ) || ( w2 == NULL ) || ( w3 == NULL ) || ( w4 == NULL ) || ( w5 == NULL ) || ( w6 == NULL ) || ( w7 == NULL ) || ( w8 == NULL ) || ( w9 == NULL ) )
    {
        return 1;
    }

    //If everything loaded fine
    return 0;
}

void clean_up()
{
    //Free the sound effects
    Mix_FreeChunk( w0 );
    Mix_FreeChunk( w1 );
    Mix_FreeChunk( w2 );
    Mix_FreeChunk( w3 );
    Mix_FreeChunk( w4 );
    Mix_FreeChunk( w5 );
    Mix_FreeChunk( w6 );
    Mix_FreeChunk( w7 );
    Mix_FreeChunk( w8 );
    Mix_FreeChunk( w9 );

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* argv[] )
{
    //For debug only!!!
    int pi_length = 20;
    //Default number of playing notes
    //int pi_length = 100;
    
    //Reading arguments
    if (argc > 1)
	{
		//Show short help message and quit
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
		{
			printf("Usage: %s [option]\n\n", argv[0]);
			printf("Where option can be integer number of playing notes of Pi (max. 1000)\n");
			printf("or -h|--help for this message\n");
			return 0;
		}
		//Read number of notes from user
		char* argument = argv[1];
		int i;
		for (i = 0; i < strlen(argument); i++)
		{
			//If given value is not integer number - show help message and quit
			if (!isdigit(argument[i]))
			{
				printf("Usage: %s [option]\n\n", argv[0]);
				printf("Where option can be integer number of playing notes of Pi (max. 1000)\n");
				printf("or -h|--help for this message\n");
				return 1;
			}
		}
		//Convert given argument into integer and assignment it to corresponding variable
		pi_length = atoi(argument);
		if (pi_length > 100)
		{
			//If number of notes is more than 1000 - show error message and quit
			if (pi_length > 1000)
			{
				printf("Cannot to play so much... Pi is so hard!");
				return 1;
			}
			//If number of notes is more than 100 - show warning message and request of confirmation
			char confirm[3];
			printf("Recommended value is up to 100 (max. 1000)\n");
			printf("You enter very large number. Do you really want to hear so long?\n");
			printf("Confirm with 'y' or 'Y' key or reject with any else: ");
			fgets(confirm, 3, stdin);
			//If user enter something different from 'y'/'Y' - quit
			if (strncmp(confirm, "y\n", 2) && strncmp(confirm, "Y\n", 2) && strncmp(confirm, "y ", 2) && strncmp(confirm, "Y ", 2))
			{
				return 0;
			}
		}
	}
	
	//Initialize SDL
    if( init() == 1 )
    {
		printf("Cannot initialize SDL!");
        return 2;
    }
    printf("%s\n", "Initialization... done");

    //Load the files
    if( load_files() == 1 )
    {
		printf("Cannot load music files!");
        return 3;
    }
    printf("%s\n", "Loading... done");
    
    //Read Pi from array Pi[] and play corresponding notes
    //If some wrong with playing - show error message and jump to next note
    //However, adjusting play time of notes with time in SDL_Delay
    //(and partially with buffer size in Mix_OpenAudio) solves some problem
    int i;
	for (i = 0; i < pi_length; i++)
	{
		char a = Pi[i];
		switch (a)
		{
			case '0':
				if (Mix_PlayChannel( -1, w0, 0 ) == -1 )
				{
					printf("No. %i Error 10\n", i);
				}
				SDL_Delay(500);
				break;
			case '1':
				if (Mix_PlayChannel( -1, w1, 0 ) == -1 )
				{
					printf("No. %i Error 11\n", i);
				}
				SDL_Delay(500);
				break;
			case '2':
				if (Mix_PlayChannel( -1, w2, 0 ) == -1 )
				{
					printf("No. %i Error 12\n", i);
				}
				SDL_Delay(500);
				break;
			case '3':
				if (Mix_PlayChannel( -1, w3, 0 ) == -1 )
				{
					printf("No. %i Error 13\n", i);
				}
				SDL_Delay(500);
				break;
			case '4':
				if (Mix_PlayChannel( -1, w4, 0 ) == -1 )
				{
					printf("No. %i Error 14\n", i);
				}
				SDL_Delay(500);
				break;
			case '5':
				if (Mix_PlayChannel( -1, w5, 0 ) == -1 )
				{
					printf("No. %i Error 15\n", i);
				}
				SDL_Delay(500);
				break;
			case '6':
				if (Mix_PlayChannel( -1, w6, 0 ) == -1 )
				{
					printf("No. %i Error 16\n", i);
				}
				SDL_Delay(500);
				break;
			case '7':
				if (Mix_PlayChannel( -1, w7, 0 ) == -1 )
				{
					printf("No. %i Error 17\n", i);
				}
				SDL_Delay(500);
				break;
			case '8':
				if (Mix_PlayChannel( -1, w8, 0 ) == -1 )
				{
					printf("No. %i Error 18\n", i);
				}
				SDL_Delay(500);
				break;
			case '9':
				if (Mix_PlayChannel( -1, w9, 0 ) == -1 )
				{
					printf("No. %i Error 19\n", i);
				}
				SDL_Delay(500);
				break;
		}	
	}

    //Free surfaces, fonts and sounds
    //then quit SDL_mixer, SDL_ttf and SDL
    clean_up();
	printf("\n");
	
    return 0;
}
