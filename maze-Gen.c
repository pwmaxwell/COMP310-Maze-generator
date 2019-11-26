// Maze-Gen.c
// Patrick Maxwell, Nick Kolasinski, November 2019

/* Generates a two-dimensional ASCII maze file with one starting point and one exit. 
 * INFO:
	* Walls are represented with a 'b'
 	* Starting position is represented with an 's'
	* This program is designed to take multiple command line arguments in a sepecific order
		* EXAMPLE:
		* ./Maze-Gen.o -d -h 40 -w 40 -a "dfs" -n "maze" -c 5
		
		* EXPLANATION:
		* '-d' will enable debug mode that prints off variables as they are passed around
		* '-h 40' will set the height of the maze to 40
		* '-w 40' will set the width of the maze to 40
		* '-a "dfs"' will set the maze generation algorithm to depth-first search (see below for other options)
			* argument	| algorithm                      *
			*---------------|--------------------------------* 
			* "dfs"		| Depth-First Search             *
			* "rb"		| Recursive Backtracker          *
			* "rka"		| Randomized Kruskal's Algorithm *
			* "rpa"		| Randomized Prim's Algorithm    *
			* "wa"		| Wilson's Algorithm             *
		
		* '-n "maze"' will set the output file's name to maze.txt | NOTE: CANNOT BE >100 CHARACTERS
		* '-c 5' will create 5 randomized mazes of size 'h' and 'w', using the "alg" and a name of "maze"
			*NOTE: a number more than 1 (5 for this example) will number them off as seen below:
				* "maze0.txt", "maze1.txt", "maze2.txt", "maze3.txt", "maze4.txt"
				* for a total of 5 maze text files numbering from 0 to 4(5-1) */

// Libraries:
	// This program uses the following libraries:
#include <stdio.h>	// File input/output
#include <stdlib.h>	// General utilities
#include <unistd.h>	// Standard symbolic constants and types
#include <stdbool.h>	// Boolean type support library
#include <string.h>	// String type support library 		MAY OR MAY NOT BE USED
#include <time.h>	// Date and time utilities; aids in randomization for seeds
#include <iso646.h>	// Alternate operators and tokens; helps improve readability 

// DEFAULTS:
	// Failure to properly enter any command line arguments the following will be the default values
#define DEFAULT_H 15
#define DEFAULT_W 15
#define DEFAULT_ARG "dfs"
#define DEFAULT_NAME "maze"
#define DEFAULT_COUNT 1

//MAZE STRUCTURE
struct Maze{
	int height;
	int width;
	char alg[30];
	char name[100];
	int count;
} MAZE_DEFAULT = {DEFAULT_H, DEFAULT_W, DEFAULT_ARG, DEFAULT_NAME, DEFAULT_COUNT};

//GLOBAL DEBUG BOOL
bool debug = false;

//INITIALIZE FUNCTIONS
void initMaze(struct Maze*, int argc, char* argv[]);	



int main(int argc, char* argv[]){
	struct Maze *mazeStruct_ptr, mazeStruct;		// create the first maze structure for generation
	mazeStruct_ptr = &mazeStruct;
	
	mazeStruct = MAZE_DEFAULT;	

	initMaze(mazeStruct_ptr, argc, argv);

	// PRINT VALUES TO MAKE SURE INITMAZE WORKS
	printf("Here is the value of height: %d\n", mazeStruct_ptr->height);
	printf("Here is the value of width: %d\n", mazeStruct_ptr->width);
	printf("Here is the value of alg: %s\n", mazeStruct_ptr->alg);
	printf("Here is the value of name: %s\n", mazeStruct_ptr->name);
	printf("Here is the value of count: %d\n", mazeStruct_ptr->count);
	
	return 0; // End condition for main
}

void initMaze(struct Maze *maze, int argc, char *argv[]){
	int local_height, local_width, local_count, opt = 1;
	char local_alg[30], local_name[30];

	printf("\n");	
	while((opt = getopt(argc, argv, "dhwa:n:c")) not_eq -1){
		switch(opt){
			case 'd':
				debug = true;
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nDebug Mode: ON\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;
			case 'h':
				local_height = atoi(argv[optind]);
				if(local_height < 5){
					printf("The height argument you gave was too small or the wrong format, defaulting to %d\n", DEFAULT_H);
					local_height = DEFAULT_H;
				}
				maze->height = local_height;
				if(debug) printf("height: %d\n", maze->height);
				break;
			case 'w':
				local_width = atoi(argv[optind]);
				if(local_width < 5){
					printf("The width argument you gave was too small or in the wrong format, defaulting to %d\n", DEFAULT_W);
					local_width = DEFAULT_W; 
				}
				maze->width = local_width;
				printf("width: %d\n", maze->width);
				break;
			case 'a':
				strcpy(local_alg, optarg);
				// IF LOCAL_ALG ISNT ANY ONE OF THE ABOVE LITERALS, SET TO DEFAULT
				//
				//
				strcpy(maze->alg, local_alg);
				printf("algorithm: %s\n", maze->alg);
				break;
			case 'n':
				strcpy(local_name, optarg);
				strcpy(maze->name, local_name);
				printf("name: %s\n", maze->name);
				break;
			case 'c':
				local_count = atoi(argv[optind]);
				maze->count = local_count;
				printf("count: %d\n", maze->count);
				break;
			case '?':
				printf("unknown argument(s): %c\n", optopt);
				break;
			default:
				printf("Hmm... that's not supposed to happen");
				break;
		}
	}
}
