// maze-gen.c
// Patrick Maxwell, Nick Kolasinski, November 2019

/* Generates a two-dimensional ASCII maze file with one starting point and one exit. 
 * INFO:
  * Walls are represented with a 'b'
  * Starting position is represented with an 's'
  * This program is designed to take multiple command line arguments in a sepecific order
   * EXAMPLE:
    * ./Maze-Gen.o -h 40 -w 40 -a "dfs" -n "maze" -c 5
	 * EXPLANATION:
	  * '-h 40' will set the height of the maze to 40
	  * '-w 40' will set the width of the maze to 40
	  * '-a "dfs"' will set the maze generation algorithm to depth-first search (see below for other options)
	   * argument  | algorithm                      *
	   *-----------|--------------------------------* 
	   * "dfs"     | Depth-First Search             *
	   * "rka"	  | Randomized Kruskal's Algorithm *
	   * "rpa"	  | Randomized Prim's Algorithm    *
	   * "wa"	  | Wilson's Algorithm             *
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
#define DEFAULT_ALG "dfs"
#define DEFAULT_NAME "maze"
#define DEFAULT_COUNT 1
static char* DEFAULT_ALGS[4] = {"dfs", "rka", "rpa", "wa"};
char** DEFAULT_ALGS_POINTER = &DEFAULT_ALGS[0];


//MAZE STRUCTURE
struct Maze{
	int height;
	int width;
	char alg[5];
	char name[100];
	int count;
} MAZE_DEFAULT = {DEFAULT_H, DEFAULT_W, DEFAULT_ALG, DEFAULT_NAME, DEFAULT_COUNT};

//GLOBAL DEBUG BOOL
bool debug = false;

//INITIALIZE FUNCTIONS
void initMaze(struct Maze*, int argc, char* argv[]);	
int getArgInt();

int main(int argc, char* argv[]){
	struct Maze *mazeStruct_ptr, mazeStruct; // create the maze structure, and a pointer to that maze struct
	mazeStruct_ptr = &mazeStruct; // set the pointer to the value of the maze struct
	
	mazeStruct = MAZE_DEFAULT; //set default values 

	initMaze(mazeStruct_ptr, argc, argv);
	if(debug)printf("DEBUG: start of main post-initMaze()\n");

	printf("Creating %d %dx%d maze(s) ",mazeStruct_ptr->count, mazeStruct_ptr->width, mazeStruct_ptr->height);
	printf("using the %s algorithm, ", mazeStruct_ptr->alg);
	printf("with a naming format: %s.\n", mazeStruct_ptr->name);
	
	if(debug)printf("DEBUG: end of main\n");
	return 0; // End condition for main
}

void initMaze(struct Maze *maze, int argc, char *argv[]){
	int local_height, local_width, local_count, opt = 1;
	char local_alg[5], local_name[30];
	
	while((opt = getopt(argc, argv, "dhwa:n:c")) not_eq -1){
		switch(opt){
			
			
			case 'd':
				
				debug = true; // set the global variable to TRUE
				
				printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nDebug Mode: ON\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				
				printf("DEBUG: Start of initMaze()");
				
				printf("\nDEBUG:\tMaze Values\n");	
				
				break;
			
			
			case 'h': // check if the height is at-least 5 (otherwise the maze will be too small to be useful)
			
				local_height = atoi(argv[optind]);
								
				if(local_height >= 5){
					maze->height = local_height;
				}
				else{
					printf("\t\tSorry, the height argument you gave was too small or the wrong format, defaulting to: %d\n", DEFAULT_H);
					// maze->height is already equal to DEFAULT_H so we don't need to assign anything again if its invalid
				}
				
				if(debug) printf("\t height: %d\n", maze->height);
				
				break;
				
				
			case 'w': // check if the width is atleast 5 (otherwise the maze will be too small to be useful)
				
				local_width = atoi(argv[optind]);
				
				if(local_width >= 5){
					maze->width = local_width;
				}
				else{
					printf("\t\tSorry, your maze would be too short!. Defaulting to: %d\n", DEFAULT_W);
					// maze->width is already equal to DEFAULT_W so we don't need to assign anything again if its invalid
				}

				if(debug) printf("\t width: %d\n", maze->width);
				
				break;
			
			
			case 'a':; 
				
				bool found = 0; // a boolean set to '1' when we have found the algorithm
				int DEFAULT_ALGS_SIZE = (sizeof(DEFAULT_ALGS) / sizeof(DEFAULT_ALGS[0])); // we need the size because we will later have to iterate through and compare
				
				//below we check to make sure the users' input won't seg fault for being too long
				if(strlen(optarg) > 5){
					printf("\t\tSorry, that algorithm is not found. Defaulting to: %s\n", DEFAULT_ALG);
					//optarg = DEFAULT_ALG;
					strcpy(maze->alg, DEFAULT_ALG);
					found = 1;
				}
				
				// below we loop through the array of algorithms to see if what the user decided is a valid alg				
				
				for(int a = 0; a < DEFAULT_ALGS_SIZE; a++){		
					if(strcmp(optarg, DEFAULT_ALGS_POINTER[a]) == 0 || found == 0){
						strcpy(local_alg, optarg);
						found = 1;
					}
					else{
						if(found == 0){
							printf("\t\tSorry, that algorithm is not found. Defaulting to: %s\n", DEFAULT_ALG);
						}
					}
				}
				
				if(debug) printf("\t algorithm: %s\n", maze->alg);
				
				break;
			
			
			case 'n':
			
				if(strlen(optarg) > 30){
					printf("\t\tSorry, your name was too long. Defaulting to: %s\n", DEFAULT_NAME);	
					optarg = DEFAULT_NAME;
				}
		
				strcpy(maze->name, optarg);
				
				
				
				
				// DEBUG & break
				if(debug) printf("\t name: %s\n", maze->name);
				
				break;
		
		
			case 'c':
				local_count = atoi(argv[optind]);
				
				if(local_count > 100){
					printf("\t\tSorry, you're attempting to create too many mazes. Defaulting to: %d\n", DEFAULT_COUNT);
					local_count = DEFAULT_COUNT;
				}
				maze->count = local_count;
				
				if(debug)printf("\t count: %d\n", maze->count);
				
				break;


			default: // this should never happen
				printf("Hmm.. It looks like one of your arguments was off.\n");
				break;
		}
	}
	if(debug) printf("DEBUG: End of initMaze()\n");
}