#include <stdio.h>
#include <stdlib.h>
#include "TutorialConfig.h.in"


int** maze;
int** splitpath;
int rows = 2; //increased this number for testing purposes
int columns = 0;
int count = 1;
int startRow;
int startCol;
int numberOfPaths;
int* currentLocation;	

void aloc_maze(){ // taken from class discussion
	maze = malloc(rows * sizeof(int*));
	for(int i = 0; i < rows; i++)
		maze[i] = malloc(columns * sizeof(int*));
	splitpath = malloc(rows * sizeof(int*));
	for(int i = 0; i < rows; i++)
		splitpath[i] = malloc(columns * sizeof(int*));
	
}
void printMaze(){
	for (int i = 0; i < rows; ++i) { //this will print out the maze
		for (int j = 0; j < columns; ++j) {
			if(maze[i][j] !=99) // could not figure out how to remove the added 0s from my program so I am instead adding an if statement which will require maze[i][j] to not be 0 to print
				printf("%3i", maze[i][j]); //information on formating taken from https://www.eecs.wsu.edu/~cs150/reading/printf.htm
		}
		printf("\n");
	}	
	printf("\n");
	for (int i = 0; i < rows; ++i) { //this will print out the maze
		for (int j = 0; j < columns; ++j) {
			if(maze[i][j] !=99) // could not figure out how to remove the added 0s from my program so I am instead adding an if statement which will require maze[i][j] to not be 0 to print
				printf("%3i", splitpath[i][j]); //information on formating taken from https://www.eecs.wsu.edu/~cs150/reading/printf.htm
		}
		printf("\n");
	}
	printf("\n");
}

int solveMaze(int row, int col){
	currentLocation = &maze[row][col];
	numberOfPaths = 0;
	maze[row][col] = count;
	if(row != 0){
		if(maze[row-1][col] == 0){
			numberOfPaths++;
		}
		if(maze[row+1][col] == 0){
			numberOfPaths++;
		}
		if(maze[row][col-1] == 0){
			numberOfPaths++;
		}
		if(maze[row][col+1] == 0){
			numberOfPaths++;
		}
		if(numberOfPaths >= 2){
			numberOfPaths--;
			splitpath[row][col] = numberOfPaths;
		}
		if(maze[row][col -1] == 0){
			maze[row][col] = count;
			count++;
			solveMaze(row,col-1);
		}
		else if(maze[row+1][col] == 0){
			maze[row][col] = count;
			count++;
			solveMaze(row+1, col);
		}	
		else if(maze[row][col +1] == 0){
			maze[row][col] = count;
			count++;
			solveMaze(row, col + 1);	
		}
		else if(maze[row-1][col] == 0){
			maze[row][col] = count;
			count++;
			solveMaze(row-1, col);
		}
		else{
			maze[row][col] = count;
			return 1;
		}
	}
}


void getMaze(char* file_name){
	char c;
	char c2;
	FILE* file = fopen(file_name, "r");	
	
	/* find number of columns by examining the first line only. Could break if other lines have more or fewer columns. */
	while ((c = getc(file)) != EOF){ // this will determine how many columns and rows are needed to alocate them into the 2d array
		if(c == '\n'){
			columns++;
			break;
		}
		columns++;
	}
	//rows = 1;
	//printf("rows=%d, columns=%d\n", rows, columns);
	while((c = getc(file)) != EOF){
		if(c == '\n')
			rows++;
	}
	
	
	//printf("%i", rows);
	//printf("%c", '\n');
	//printf("%i", columns);
	aloc_maze();
	fclose(file);
	file = fopen(file_name, "r");
	
	for(int i = 0; i < rows; i++){ // this will put the numbers into the array
	int j;
		for (j = 0; j < columns; j++){
			c2= getc(file);
			if(c2 == 'b')
				maze[i][j] = -1;
			else if(c2 == ' ')
				maze[i][j] = 0;
			else if(c2 == 's')
				maze[i][j] = 1;
			else {
				//fprintf(stderr, "Unexpected character %c\n", c2);
				maze[i][j] = 99;
			}	
			if(c2 == 's'){ //this will figure out where to start
				startRow = i;
				startCol = j;			}
		}
		if (j < columns) {
			while (c2 != '\n')
				c2 = getc(file);
		}
	}
		fclose(file);
	solveMaze(startRow, startCol);
	
	/*for(int i =0; i< rows; i++){
		for(int j=0; j<columns -2 ; j++){
			for(int k = 0; k <splitpath[i][j];k++){			
				if(splitpath[i][j] == 1){
					count = maze[i][j];
					solveMaze(i,j);
				}
			}
			/*else if(splitpath[i][j] == 2){
				count =maze[i][j];
				solveMaze(i,j);
				count = maze[i][j];
				solveMaze(i,j);
			}
			elseif(splitpath[i][j] == 3){
				count = maze[i][j];
				solveMaze(i,j);
				count = maze[i][j];
				solveMaze(i,j);
				count = maze[i][j];
				solveMaze(i,j);
			}
			
		}
	}*/
	for(int i =0; i< rows; i++){
		for(int j=0; j<columns -2 ; j++){		
			while(splitpath[i][j] != 0){
				count = maze[i][j];
				//printf("\n");
				//printf("%i", count);
				//printf("\n");
				splitpath[i][j]--;
				solveMaze(i,j);
				
			}
		}
	}
	printMaze();
	

}




int main(){
	getMaze("maze1.txt");
}


