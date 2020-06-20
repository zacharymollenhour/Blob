//
//*************************************************************
//*************************************************************
// * Name: Blob.cpp					      					  *
// * Class: COP3330					      					  *
// * Description: Cpp file for blob program taht checks text  *
// * To see if its a blob or not at hte location              *
// * Author: Zachary Mollenhour                               *
// * Date: june 19th, 2020				      				  *
//*************************************************************
#include <iostream>
#include <fstream>
using namespace std;


/* printBlob takes a 2d character array image prints the image to the screen.*/
void printBlob(char** image, const int arrayRows, const int arraycols);

/* Function that takes in a parameter of a 2d array and detects if a blob exists at that location */
int blobLocater(char** image, const int arrayRows, const int arraycols, const int search_row, const int search_col);

int main(void){
	
	const int numRows = 20;			//Number of row records in the file
	const int numcols = 70;			//Number of columns records in the file
	const int arrayRows = numRows+2;	// Array row counter for tracking.
	const int arraycols = numcols+2;	// Array column counter for tracking.
	ifstream inFile;				// Input file for blob text.
	char nextChar;					// character from input file.
	int totalBlob = 0;				// number of blobs, default to 0.

	// Initalize an array that will hold the blob
	char** blob = new char*[arrayRows];
	for(int row = 0; row < arrayRows; row++){
		blob[row] = new char[arraycols];
	}

	// Open blob text file
	inFile.open("blob.txt", ifstream::in);

	// Read the blob image into an array.
	//row variable for current row
	for(int row = 0; row < numRows; row++){
		for( int col = 0; col < numcols; col++ ){

			// Read in the next charcter
			inFile.get(nextChar);

			// Save the character from the file to the array.
			blob[row+1][col+1] = nextChar;
		}

		// Read the return line character and ignore.
		inFile.get(nextChar);
	}

	// Close input file.
	inFile.close();

	// Print the image.
	printBlob(blob, arrayRows, arraycols);

	// Search the image for blobs.
	// col variable for current column
	for(int row = 1; row < arrayRows-1; row++){
		for( int col = 1; col < arraycols-1; col++ ){
			// Check this location for a blob.
			if( blobLocater(blob, arrayRows, arraycols, row, col) == 1 ){

				// Increment blob counter.
				totalBlob += 1;

				// Print message for blob found and their location.
				cout << "Found one at row=" << row << " and col=" << col << endl;
			}
		}
	}

	// Print number of total blobs found.
	cout << endl << "Number of blobs = " << totalBlob << endl;

	// Delete the image array for extra credit.
	for(int row = 0; row < arrayRows; row++){
		delete blob[row];
	}
	delete blob;
}

int blobLocater(char** blob, const int arrayRows, const int arraycols, const int search_row, const int search_col){
	
	// Default return value to 0.
	int found = 0;

	// Check if a blob exists at this location.
	if( blob[search_row][search_col] != ' ' ){
		
		// Set return value.
		found = 1;

		// Clear this location once blob found.
		blob[search_row][search_col] = ' ';

		// Search up 1.
		if( search_row > 1){
			blobLocater(blob, arrayRows, arraycols, search_row-1, search_col);
		}

		// Search diaganol, right and up 1.
		if( search_col < arraycols-2 && search_row > 1){
			blobLocater(blob, arrayRows, arraycols, search_row-1, search_col+1);
		}

		// Search right 1.
		if( search_col < arraycols-2 ){
			blobLocater(blob, arrayRows, arraycols, search_row, search_col+1);
		}

		// Search diaganol, left and down.
		if( search_col > 1 && search_row < arrayRows-2){
			blobLocater(blob, arrayRows, arraycols, search_row+1, search_col-1);
		}

		// Search down.
		if( search_row < arrayRows-2 ){
			blobLocater(blob, arrayRows, arraycols, search_row+1, search_col);
		}

		// Search diaganol, right and down.
		if( search_col < arraycols-2 && search_row < arrayRows-2){
			blobLocater(blob, arrayRows, arraycols, search_row+1, search_col+1);
		}

		// Search left.
		if( search_col > 1){
			blobLocater(blob, arrayRows, arraycols, search_row, search_col-1);
		}

		// Search diaganol, left and up.
		if( search_col > 1 && search_row > 1){
			blobLocater(blob, arrayRows, arraycols, search_row-1, search_col-1);
		}
	}
	//return the number of found ones
	return found;
}

//extra credit functions
void printBlob(char** blob, const int arrayRows, const int arraycols){
	
	// Define preset sizes of the image
	const int numRows = arrayRows - 2;
	const int numcols = arraycols - 2;

	// Print the header for extra credit.
	
	// Print tens label row.
	const int tensCount = numcols/10;
	for( int curTens = 0; curTens < tensCount; curTens++ ){
		cout << "         " << curTens+1;
	}
	cout << endl;

	// Print ones label row.
	for( int onesCount = 0; onesCount < numcols; onesCount++ ){
		cout << (onesCount+1)%10;
	}
	cout << endl;

	// Print the image for extra credit.
	for( int row = 0; row < numRows; row++ ){
		for( int col = 0; col < numcols; col++ ){
			cout << blob[row+1][col+1];
		}
		cout << endl;
	}
}