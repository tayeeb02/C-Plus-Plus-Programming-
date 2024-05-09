/*

  The following program solves the L-shape blocks problem

   Given
	  A 2^N x 2^N array (In this assignment, we restrict the value N as 1, 2 and 3 )
	   The location of the empty cell (x,y)
		  The legal (x,y) coordinates of the empty cell:

			  For a 2 x 2 block, the legal range is 0-1
			  For a 4 x 4 block, the legal range is 0-3
			  For a 8 x 8 block, the legal range is 0-7
	   You can assume all the input values are correct

	Output:

	  The empty cell (x,y) remains empty
	  All other cells are filled by non-overlapping L-shape blocks

	Output mode:
	  (0) Console output without normalization
	  (1) Console output with normalization

	   Author: Peter, Brian, Tommy
*/

#include <iostream>
using namespace std;

// Constants in global scope
const int MAX_WIDTH = 8;
const int LOCATEQUADRANT_NOT_IMPLEMENTED = 0;

// TODO:
// function locateQuadrant:
// @param x:  x coordinate of the empty cell
// @param y:  y coordinate of the empty cell
//
// If x < half width, y < half width, then return 1
// If x >= half width, y < half width, then return 2
// If x >= half width, y >= half width, then return 3
// If x < half width, y >= half width, then return 4
//
// @return: int
// The function returns after getting valid values for width, emptyXPos and emptyYPos
int locateQuadrant(int width, int x, int y)
{
	int half_Width = width/2; 

	if (x < half_Width && y < half_Width) {
		return 1;
	}
	else if(x >=half_Width && y < half_Width) {
		return 2;
	}
	else if(x >= half_Width && y >= half_Width) {
		return 3; 
	}
	else if(x < half_Width && y>=half_Width) {
		return 4;
	}

	// remove this line to start your work
	return LOCATEQUADRANT_NOT_IMPLEMENTED;
}

/**
	Given the puzzleMap (2D array from the recursive function),
	Generate the console output
 */
void visualizePuzzleByText(int width, char puzzleMap[][MAX_WIDTH])
{

	cout << "  ";
	for (int x = 0; x < width; x++)
		cout << x << " ";
	cout << endl;

	for (int y = 0; y < width; y++)
	{
		cout << y << ":";
		for (int x = 0; x < width; x++)
			cout << puzzleMap[x][y] << " "; 
		cout << endl;
	}
}

/**
 * Initialize the whole puzzleMap using by a space character: ' '
 */
void initializePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < width; y++)
			puzzleMap[x][y] = ' ';
}

// TODO:
// Normalize the whole puzzleMap. The space character ' ' will not be changed.
//
void normalizePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	char Letter[21];
	int letterNumber = 0; 

	for (int Row_Iterator = 0; Row_Iterator < width; Row_Iterator++){
		for (int Column_Iterator=0; Column_Iterator < width; Column_Iterator++){
			if (puzzleMap[Column_Iterator][Row_Iterator]>= 'A' && puzzleMap[Column_Iterator][Row_Iterator] <= 'Z'){
				bool Value_In_Letter_Array;
				int Letter_Location;
				for (int i = 0; i < 21; i++){
					if(puzzleMap[Column_Iterator][Row_Iterator]== Letter[i]){
						Value_In_Letter_Array = true;
						Letter_Location = i;
					}
				}

				if(Value_In_Letter_Array){
					puzzleMap[Column_Iterator][Row_Iterator] = Letter_Location + 'A';
				} 
				else {
					Letter[letterNumber] = puzzleMap[Column_Iterator][Row_Iterator];
					puzzleMap[Column_Iterator][Row_Iterator] = letterNumber + 'A';
					letterNumber+=1;
				}

				Value_In_Letter_Array = false;

			}
		}
	}




	return;
}

// TODO:
// [The most important function in this program]
// The recursive function to fill up the character array: puzzleMap
// You need to figure out the parameters of the fillPuzzleRecursive function by yourself
//
void fillPuzzleRecursive(int width, char puzzleMap[][MAX_WIDTH],int tx,
						int ty, int  x, int y, char &nextChar)
{

	// tx: top Left X coordinate
	// ty: top Left Y coordinate
	// x:  x coordinate of the empty cell
	// y:  y coordinate of the empty cell
	if (width == 2)
	{
		// The base case...
		//cout << "BASE CASE" << endl;

		//Handling Quadrant 1 being empty
		if (x==tx && y==ty) {
			puzzleMap[tx+1][ty]=nextChar;
			puzzleMap[tx][ty+1]=nextChar;
			puzzleMap[tx+1][ty+1]=nextChar;
			nextChar+=1;
			return;
		}

		//Handling Quadrant 2 being empty
		if (x==tx+1 && y==ty) {
			puzzleMap[tx][ty]=nextChar;
			puzzleMap[tx][ty+1]=nextChar;
			puzzleMap[tx+1][ty+1]=nextChar;
			nextChar+=1;
			return;
		}

		//Handling Quadrant 3 being empty
		if (x==tx+1 && y==ty+1) {
			puzzleMap[tx][ty]=nextChar;
			puzzleMap[tx+1][ty]=nextChar;
			puzzleMap[tx][ty+1]=nextChar;
			nextChar+=1;
			return;
		}

		//Handling Quadrant 4 being empty
		if (x==tx && y==ty+1) {
			puzzleMap[tx][ty]=nextChar;
			puzzleMap[tx+1][ty]=nextChar;
			puzzleMap[tx+1][ty+1]=nextChar;
			nextChar+=1;
			return;
		}

	}

	// The general case
	//
	// Key idea:
	//  Because qual must be equal to either 1, 2, 3 or 4
	// As a result:
	//    A L-shape MUST be created at the center of the bigger rectangle
	//    Each Quad MUST have exactly 1 empty space
	else {


		int quad = locateQuadrant(width, x-tx, y-ty);

		if (quad == 1){

			puzzleMap[((width/2)-1) + tx][(width/2) + ty] = nextChar;
			puzzleMap[(width/2) + tx][(width/2) + ty] = nextChar;
			puzzleMap[(width/2) + tx][((width/2)-1) + ty] = nextChar;
			nextChar +=1;
			
			fillPuzzleRecursive(width/2, puzzleMap, tx + 0, ty + 0, x, y, nextChar);
				//cout << "Calling Recursion";
			fillPuzzleRecursive(width/2, puzzleMap, tx + (width/2), ty + 0, tx + (width/2), ty + ((width/2)-1), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx + (width/2), ty + (width/2), tx + (width/2), ty + (width/2), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx+ 0, ty+ (width/2), tx+ ((width/2)-1), ty+ (width/2), nextChar);
			
		}

		if (quad == 2) {

			puzzleMap[((width/2)-1) + tx][((width/2)-1) + ty] = nextChar;
			puzzleMap[(width/2) + tx][ (width/2) + ty] = nextChar;
			puzzleMap[(width/2-1) + tx][((width/2)) + ty] = nextChar;

			nextChar +=1;
	
			fillPuzzleRecursive(width/2, puzzleMap, tx +0,ty + 0, tx+ ((width/2)-1), ty+ ((width/2)-1), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx + (width/2), ty+ 0, x, y, nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx+ (width/2), ty + (width/2), tx + (width/2), ty + (width/2), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx + 0, ty + (width/2), tx + ((width/2)-1), ty + (width/2), nextChar);

			

		}

		if (quad == 3) {

			puzzleMap[((width/2)-1) + tx][ ((width/2)-1) + ty] = nextChar;
			puzzleMap[((width/2)-1) + tx][(width/2) + ty] = nextChar;
			puzzleMap[(width/2) + tx][((width/2)-1) + ty] = nextChar;
			nextChar +=1;
				
			fillPuzzleRecursive(width/2, puzzleMap, tx + 0,ty+ 0, tx+ ((width/2)-1), ty + ((width/2)-1), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap,tx+ (width/2),ty+ 0, tx+ ((width/2)), ty+ ((width/2)-1), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx + (width/2), ty+ (width/2), x, y, nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx + 0, ty+ (width/2), tx+ ((width/2)-1), ty+ (width/2), nextChar);

			

		}

		if(quad == 4){
			puzzleMap[((width/2)-1) + tx][((width/2)-1) + ty] = nextChar;
			puzzleMap[((width/2)) + tx][(width/2 - 1) + ty] = nextChar;
			puzzleMap[(width/2) + tx][((width/2)) + ty] = nextChar;
			nextChar +=1;
				
			fillPuzzleRecursive(width/2, puzzleMap, tx + 0,ty+ 0, tx + ((width/2)-1), ty + ((width/2)-1), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx + (width/2), ty+ 0,  tx + ((width/2)), ty + ((width/2)-1), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx+ (width/2), ty + (width/2), tx + (width/2), ty+ (width/2), nextChar);
			fillPuzzleRecursive(width/2, puzzleMap, tx + 0, ty + (width/2), x, y, nextChar);

			

	}
}
}

// TODO:
// function checkInput:
//
// @param width: the width of the square. Valid values: 2, 4, 8
// You can assume inputs are always integers.
// @param emptyXPos: the x-axis of the empty position.
// Valid range: [0, width-1].
// You can assume inputs are always integers.
// @param emptyYPos: the y-axis of the empty position.
// Valid range: [0, width-1].
// You can assume inputs are always integers.
//
//  Note: The pass-by-reference variables will be used in the main function.
// @return: void
// The function returns after getting valid values for width, emptyXPos and emptyYPos
void checkInput(int &width, int &emptyXPos, int &emptyYPos)
{
	// Some helper lines for you to use:
	cout << "Enter the width/height of the puzzle (2, 4, 8): " << endl;
	cin >> width; 
	//cout << endl; Have removed this line because apparently, taking input automatically has an endline character so it 
	//moves to the next line without me having to do anything. 

	/*
		This Condition is checking whether the width input is correct or not. 
		cout << lines have been removed because apparently, taking input automatically ends with a newline character. 

		It checks if the width is (NOT equal to 2) AND (NOT equal to 4) AND (NOT equal to 8). The AND matters here. 
		Because, if either on of them is equal to 2 or equal to 4 or equal to 8, one of the condition becomes false and the 
		while loop exits. 
	
	*/
	while(width!=2 && width!=4 && width!=8) {
		
		cout << "Enter the width/height of the puzzle (2, 4, 8): " << endl;
		cin >> width;
		//cout << endl;
	}


	//cout << endl; // Not needed apparently. 
	cout << "Enter the x-coordinate of the empty cell (0-" << width - 1 << "): " << endl;
	cin >> emptyXPos;
	//cout << endl;

	/* 
		This condition is the same for Y position so, I'll write it once. It simply checks if the position entered is less than 0 
		OR if it is greater than or equal to the width. OR matters here. 
	
	*/

	while(emptyXPos<0 || emptyXPos>=width) {
		
		cout << "Enter the x-coordinate of the empty cell (0-" << width - 1 << "): " << endl;
		cin >> emptyXPos;
		//cout << endl;
		
	}

	cout << "Enter the y-coordinate of the empty cell (0-" << width - 1 << "): " << endl;
	cin >> emptyYPos;
	//cout << endl;

	while(emptyYPos<0 || emptyYPos>=width) {
		
		cout << "Enter the y-coordinate of the empty cell (0-" << width - 1 << "): " << endl;
		cin >> emptyYPos;
		//cout << endl;
		
	}
	

	return;
}

// You are NOT ALLOWED to modify the main function
int main()
{

	int width = 0;
	int emptyXPos = 0;
	int emptyYPos = 0;

	checkInput(width, emptyXPos, emptyYPos);

	// initialized with empty spaces..
	char puzzleMap[MAX_WIDTH][MAX_WIDTH];

	// initialize
	initializePuzzleMap(width, puzzleMap);

	int modeOfOperation = 0;
	do
	{
		cout
			<< "0: Exit directly (for testing checkInput function), 1: Output Quadrant of the empty cell,"
			<< endl
			<< "2: Output without normalization (for student's debug only), 3: Output with normalization"
			<< endl;
		cout << "Enter the output mode: ";
		cin >> modeOfOperation;
		cout << endl;
	} while (modeOfOperation < 0 || modeOfOperation > 3);

	if (modeOfOperation == 0)
	{
		return 0;
	}
	if (modeOfOperation == 1)
	{
		int quad = locateQuadrant(width, emptyXPos, emptyYPos);
		cout << "Quadrant for the empty cell: " << quad << endl;
		return 0;
	}
	char nextChar = 'A';

	// invoke the recursive call here...
	// Result: puzzleMap will be filled by characters
	fillPuzzleRecursive(width, puzzleMap, 0, 0, emptyXPos, emptyYPos, nextChar);

	int quad = locateQuadrant(width, emptyXPos, emptyYPos);
	cout << "Quadrant for the empty cell: " << quad << endl;
	if (modeOfOperation == 2)
	{
		visualizePuzzleByText(width, puzzleMap);
	}
	else
	{
		normalizePuzzleMap(width, puzzleMap);
		visualizePuzzleByText(width, puzzleMap);
	}
	return 0;
}
