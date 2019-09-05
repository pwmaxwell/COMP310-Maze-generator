#include <stdio.h>
#include <stdlib.h>

int** maze;
int rows = 2; //increa sed this number for testing purposes
int columns = 0;


void aloc_maze(){ // taken from class discussion
	maze = malloc(rows * sizeof(int*));
	for(int i = 0; i < rows; i++)
		maze[i] = malloc(columns * sizeof(int*));
}


void getMaze(char* file_name){
	char c;
	char c2;
	FILE* file = fopen(file_name, "r");	
	
	while ((c = getc(file)) != EOF){
		//printf("%c", c); //remove this print statement and add a print_maze()
		
		if(c == '\n'){
			columns++;
			
			break;
		}
		columns++;
	}
	while((c = getc(file)) != EOF){
		if(c == '\n')
			rows++;
		
	}
	
	aloc_maze();
	fclose(file);
	file = fopen(file_name, "r");	
	for(int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			c2= getc(file);
			if(c2 == 'b')
				maze[i][j] = 1;
			//if(c2 == '\n')
				//maze[i][j] = '\n';
				
			if(c2 == ' ')
				maze[i][j] = 9;
			if(c2 == 's')
				maze[i][j] = 0;
		}
	}
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			printf("%i", maze[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	
	
	//printf("%c", '\n');
	//printf("%i", columns);
	fclose(file);
}

int main(){
	getMaze("maze1.txt");
}

