// Maze-Gen.c
// Patrick Maxwell, Nick Kolasinski, November 2019

/* Generates a two-dimensional ASCII maze file with one starting point and one exit. 
 * INFO:
	* Walls are represented with a 'b'
 	* Starting position is represented with an 's'
	* This program is designed to take multiple command line arguments in a specific order
		* EXAMPLE:
		* ./Maze-Gen.o -h 40 -w 40 -a "dfs" -n "maze" -c 5
		
		* EXPLANATION:
		* '-h 40' will set the height of the maze to 40
		* '-w 40' will set the width of the maze to 40
		* '-a "dfs"' will set the maze generation algorithm to depth-first search (see below for other options)
			* argument	| algorithm                      *
			*---------------|--------------------------------* 
			* "dfs"		| Depth-First Search             *
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

//Thanks to user August Karlstrom from https://stackoverflow.com/questions/34134074/c-size-of-two-dimensional-array
	// This is an easy macro to get the length of an array quickly without room for error
#define LEN(arr) ((int) (sizeof (arr) / sizeof(arr)[0]))

//DEFAULTS:
	// failure to properly enter valid command line arguments whill cause the following to be the default
#define DEFAULT_H 15
#define DEFAULT_W 15
#define DEFAULT_ALG "dfs"
#define DEFAULT_NAME "maze"
#define DEFAULT_COUNT 1
static char* DEFAULT_ALGS[4] = {"dfs", "rka", "rpa", "wa"};
char** DEFAULT_ALGS_POINTER = &DEFAULT_ALGS[0];


//MAZE STRUCTURE:
struct Maze{
	int height;
	int width;
	char alg[5];
	char name[100];
	int count;
	int** mazeArray;
	int** visitedArray;
} MAZE_DEFAULT = {DEFAULT_H, DEFAULT_W, DEFAULT_ALG, DEFAULT_NAME, DEFAULT_COUNT};


//GLOBAL VARIABLES:
FILE* file;

//GLOBAL DEBUG BOOL:
bool debug = false;

//INITIALIZE FUNCTIONS:
void initMaze(struct Maze *maze, int argc, char* argv[]);	
void printStats(struct Maze *maze);
void dfs(struct Maze *maze);
void printMaze(struct Maze *maze);
void createFile(struct Maze *maze);
void createExit(struct Maze *maze);	
int** allocateMazeSize(struct Maze *maze, int** mazeMap); // this is unused right now
void getAndPrintQuote();	// this doesn't work yet

	
int main(int argc, char* argv[]){
	struct Maze *mazeStruct_ptr, mazeStruct;		// create the first maze structure for generation
	mazeStruct_ptr = &mazeStruct;
	
	mazeStruct = MAZE_DEFAULT; //set default values 
	
	initMaze(mazeStruct_ptr, argc, argv);	// get the command line arguments
	if(debug)printf("DEBUG: start of main\n");
	printStats(mazeStruct_ptr);	//print off the values for the user to confirm
		
	dfs(mazeStruct_ptr);
	printMaze(mazeStruct_ptr);
	createFile(mazeStruct_ptr);
	//getAndPrintQuote();
	
	if(debug)printf("DEBUG: end of main\n");
	return 0; // End condition for main
}

void printStats(struct Maze *maze){
	printf("Creating %d %dx%d maze(s) ",maze->count, maze->width, maze->height);
	printf("using the %s algorithm, ", maze->alg);
	printf("with the naming format: %s.\n", maze->name);
}

void initMaze(struct Maze *maze, int argc, char *argv[]){
	int local_height, local_width, local_count, opt = 1;
	char local_alg[5], local_name[30];
	
	while((opt = getopt(argc, argv, "dhwa:n:c")) not_eq -1){
		switch(opt){
			
	
			case 'd':
				debug = true; // set the global variable to TRUE
				printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nDebug Mode: ON\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("DEBUG: start of initMaze()");
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
					printf("\t\tSorry, that algorithm is too long. Defaulting to: %s\n", DEFAULT_ALG);
					strcpy(maze->alg, DEFAULT_ALG);
					printf("algorithm 2: %s\n", maze->alg);
					found = 1;
					break;
				}
				
				
				// below we loop through the array of algorithms to see if what the user decided is a valid alg				1
				for(int a = 0; a < DEFAULT_ALGS_SIZE; a++){		
					if(strcmp(optarg, DEFAULT_ALGS_POINTER[a]) == 0){
						memcpy(local_alg,DEFAULT_ALGS_POINTER[a],sizeof(local_alg));
						strcpy(local_alg, optarg);
						printf("DEBUG: you are using the %s algorithm.\n", local_alg);
						found = 1;
					}
						
				}
				if(found == 0){
						printf("\t\tSorry, that algorithm is not found. Defaulting to: %s\n", DEFAULT_ALG);
						strcpy(local_alg,DEFAULT_ALG);
				}
				strcpy(maze->alg, local_alg);
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
				printf("Hmm.. It looks like one of your arguments was off\n");
				break;
		}
	}
	if(debug) printf("DEBUG: end of initMaze().\n");
}

void printMaze(struct Maze* maze){
	if(debug)printf("DEBUG: start of printMaze()\n");
	
	for (int i = 0; i < maze->width; ++i) { //this will print out the maze width
		for (int j = 0; j < maze->height; ++j) { // height for 11
			if(maze->mazeArray[i][j] !=99){
				printf("%3i", maze->mazeArray[i][j]); //information on formating taken from https://www.eecs.wsu.edu/~cs150/reading/printf.htm
				
			}
		}
		printf("\n");
	}
	if(debug)printf("DEBUG: end of printMaze()\n");
}

void createFile(struct Maze* maze){
	if(debug)printf("DEBUG: start of createFile()\n");
	file = fopen("maze.txt", "w");
	
	
	
	for(int i = 0; i < maze->height; i++){
		for(int j = 0; j < maze->width; j++){
			fprintf(file, "%d ", maze->mazeArray[i][j]);
		}
		fprintf(file, "\n");
	}
	if(debug)printf("DEBUG: end of createFile()\n");
}

void dfs(struct Maze* maze){
	if(debug)printf("DEBUG: start of dfs()\n");
	int width = maze->width;
	int height = maze->height;
	int** mazeArray; 
	int** visitedArray;
	
	srand(time(0));
	int startCol = (width -1) / 2;
	int startRow = (height -1) / 2;
	int endRow; 
	int endCol;
	
	mazeArray = malloc(height * sizeof(int*)); //allocating the array
	for(int i = 0; i< height; i++){
		mazeArray[i]= malloc(width * sizeof(int*));
	}
	visitedArray = malloc(height * sizeof(int*));
	for(int i = 0; i< height; i++){
		visitedArray[i]= malloc(width * sizeof(int*));
	}
	printf("dfs: %d %d \n", height, width);
	for(int i = 0; i < height; i++){
		for( int j = 0; j < width; j++){
			mazeArray[i][j] = 1;
		}
	}
	for(int i = 0; i < height; i++){
		for( int j = 0; j < width; j++){
			visitedArray[i][j] = 1;
		}
	}
	
	mazeArray[startRow][startCol] = 0; //set  the start location
	// Time to start making the maze
	int curRow = startRow;
	int curCol = startCol;
	int testCount = 200;
	
	while(testCount >= 1){
		
		int direction = rand() % (4-1+1)+1; //choose direction to move (if it can move that way)
		//printf("cur: %d %d \n", curRow, curCol);
		//printf("dir: %d \n", direction);
		//printf("dfs: %d \n", height);
		
		if(direction == 1 && curRow != 0 && curRow - 1 != 0){ //up
			if(mazeArray[curRow - 2][curCol] == 1){
				mazeArray[curRow - 1][curCol] = 0;
				mazeArray[curRow - 2][curCol] = 0;
				curRow = curRow -2;
			}
		}
		if(direction == 2 && curRow + 1 != height && curRow +2 != height){ //down
			if(mazeArray[curRow + 2][curCol] == 1){
				mazeArray[curRow +1 ][curCol] = 0;
				mazeArray[curRow +2 ][curCol] = 0;
				curRow = curRow + 2;
			}
		}
		if(direction == 3 && curCol != width && curCol + 1 != width){ //right 
			if(mazeArray[curRow][curCol + 2] == 1){
				mazeArray[curRow][curCol + 1] = 0;
				mazeArray[curRow][curCol + 2] = 0;
				curCol = curCol +2;
			}
		}

		if(direction == 4 && curCol != 0 && curCol -1 != 0){ //left
			if(mazeArray[curRow][curCol-2] == 1){
				mazeArray[curRow][curCol-1] = 0;
				mazeArray[curRow][curCol-2] = 0;
				curCol = curCol -2;
			}
		}
		
		//commence backtracking. will shorten later....
		int backtrackingCount = 0; //really bad way of backtracking
		if(curRow != 0 && curRow - 1 != 0 && curRow - 2 != 0){
			if(mazeArray[curRow - 2][curCol] == 0){
				backtrackingCount = backtrackingCount + 1;
			}
		}
		else{
			backtrackingCount = backtrackingCount + 1;
		}
		if(curRow != height - 1 && curRow + 1 != height - 1 && curRow + 2 != height - 1){
			if(mazeArray[curRow + 2][curCol] == 0){
				backtrackingCount = backtrackingCount + 1;
				
			}
		}
		else{
			backtrackingCount = backtrackingCount + 1;
		}
		if(curCol != 0 && curCol -1 != 0 && curCol - 2 != 0){
			if(mazeArray[curRow][curCol - 2] == 0){
				backtrackingCount = backtrackingCount + 1;
			}
		}
		else{
			backtrackingCount = backtrackingCount + 1;
		}
		if(curCol != width - 1 && curCol +1 != width - 1 && curCol + 2 != width - 1){
			if(mazeArray[curRow][curCol + 2] == 0){
				backtrackingCount = backtrackingCount + 1;
			}
		}
		else{
			backtrackingCount = backtrackingCount + 1;
		}
		//printf("backtrack: %d \n",backtrackingCount);
		
		if(backtrackingCount >= 4){
			if(mazeArray[curRow - 1][curCol] == 0 && visitedArray[curRow - 1][curCol] != 0){
				visitedArray[curRow - 1][curCol] = 0;
				visitedArray[curRow][curCol] = 0;
				curRow = curRow - 2;	
				
			}
			if(mazeArray[curRow + 1][curCol] == 0 && visitedArray[curRow + 1][curCol] != 0){
				visitedArray[curRow + 1][curCol] = 0;
				visitedArray[curRow][curCol] = 0;
				curRow = curRow +2;
				
			}
			if(mazeArray[curRow][curCol - 1] == 0 && visitedArray[curRow][curCol - 1] != 0){
				visitedArray[curRow][curCol - 1] = 0;
				visitedArray[curRow][curCol] = 0;
				curCol = curCol -2;
				
			}
			if(mazeArray[curRow][curCol + 1] == 0 && visitedArray[curRow][curCol + 1] != 0){
				visitedArray[curRow][curCol + 1] = 0;
				visitedArray[curRow][curCol] = 0;
				curCol = curCol + 2;
				
			}
		}
		//printf("backtrack (updated): %d \n", backtrackingCount);
		backtrackingCount = 0;
		
		testCount = testCount-1;
		//printf("test count: %d \n", testCount);
	}
	//printf("here");
	
	memcpy(maze->mazeArray, mazeArray, sizeof(maze->mazeArray));
	createExit(maze);
	printf("Maze created using dfs\n");
	if(debug)printf("DEBUG: end of maze creation (dfs)\n");
}

int** allocateMazeSize(struct Maze* maze, int** mazeMap){
	if(debug)printf("DEBUG: start of allocateMazeSize()");
	
	for(int i = 0; i< maze->width; i++){
		mazeMap[i]= malloc(maze->height * sizeof(int*));
	}
	for(int i = 0; i < maze->height; i++){
		for( int j = 0; j < maze->height; j++){
			mazeMap[i][j] = 1;
		}
	}
	if(debug)printf("DEBUG: end of allocateMazeSize()");
	return mazeMap;
}

void createExit(struct Maze *maze){
	bool exitFound = false;
	
	while(!exitFound){
		srand(time(0));
		int exitLocation = rand() % LEN(maze->mazeArray);
		if(maze->mazeArray[1][exitLocation] == 0){
			maze->mazeArray[0][exitLocation] = 0;
			exitFound;
		}
	}
}

void getAndPrintQuote(){
	if(debug)printf("DEBUG: start of getAndPrintQuote()\n");
	//This is a mess, i wasn't able to successfully generate a random even number between 10 and 187, and then grab only one of those at random.
	int line_no, count, length;
	char line[175], ch;
	FILE *fp;
	
	count = 0;
	fp = fopen("george.quotes", "r");
	
	//generate a random number between 10 and 186
	line_no = (rand() % (188 - 10 + 1) + 10); //found from https://www.geeksforgeeks.org/generating-random-number-range-c/
		if(line_no > 188 || line_no < 10) line_no = 126;// if it somehow generates a number too large, set the quote to my favorite one
		if(line_no % 2 not_eq 0) line_no--;	// if line_no isn't even
	
	while(!feof(fp)){
		while(count > 0){
			fscanf(fp, "%s\t",line);
			printf("go");
		}
	}
	fclose(fp);
	if(debug)printf("DEBUG: end of getAndPrintQuote()\n");
}