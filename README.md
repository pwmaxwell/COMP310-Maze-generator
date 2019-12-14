// Maze Generator
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
