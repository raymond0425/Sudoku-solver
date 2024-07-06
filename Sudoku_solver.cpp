#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// get user input and store the game board in the 2D array b
void ReadBoard( int b[][9] )
{
    for (int i=0; i < 81; i++) {
        cin >> b[(i-i%9)/9][i%9]; // 1st box [0][0], 2nd box [0][1], etc.
    }
}

// display the game board stored in the 2D array b
void PrintBoard( int b[][9] )
{
    for (int i=0; i < 81; i++) {
        if (i==27 || i == 54) {cout << "------+-------+-------" << endl;}
        if (b[(i-i%9)/9][i%9] !=0) {cout << b[(i-i%9)/9][i%9] << ' ';} else {cout << 'x' << ' ';} // print 'x' if the value is 0
        if (i%9 == 2 || i%9 == 5) {cout << '|' << ' ';}
        if (i%9 == 8) {cout << endl;}
    }
}

int theOnlyAllowedDigit( int b[][9] , int i )
{
    int existingDigits[8] = {0,0,0,0,0,0,0,0};
    int numberOfAddedElement = 0;
    for (int j=0; j < 9; j++) { // checks horizontal
        if ( b[(i-i%9)/9][j] != 0 && find(begin(existingDigits), end(existingDigits), b[(i-i%9)/9][j]) == end(existingDigits)) { // if the digit is not 0 and not previously added to existingDigits
            existingDigits[numberOfAddedElement] = b[(i-i%9)/9][j];
            numberOfAddedElement += 1;
        }
    }
    for (int j=0; j < 9; j++) { // checks vertical
        if ( b[j][i%9] != 0 && find(begin(existingDigits), end(existingDigits), b[j][i%9]) == end(existingDigits)) { // if the digit is not 0 and not previously added to existingDigits
            existingDigits[numberOfAddedElement] = b[j][i%9];
            numberOfAddedElement += 1;
        }
    }
    int topLeftOfBox = i%9 - i%3 + ((i-i%27));
    for (int j=0; j < 3; j++) { // checks within the 3x3 box
        for (int k=0; k < 3; k++) {
            if ( b[((topLeftOfBox-topLeftOfBox%9)/9)+j][topLeftOfBox % 9 +k] != 0 && find(begin(existingDigits), end(existingDigits), b[((topLeftOfBox-topLeftOfBox%9)/9)+j][topLeftOfBox % 9 +k]) == end(existingDigits)) {
                existingDigits[numberOfAddedElement] = b[((topLeftOfBox-topLeftOfBox%9)/9)+j][topLeftOfBox % 9 +k];
                numberOfAddedElement += 1;
            }
        }
    }

    if (numberOfAddedElement == 8) {
        for (int x=1; x<10; x++) {
            if (find(begin(existingDigits), end(existingDigits), x) == end(existingDigits)) {
                return x;
            }
        }
    }
    return 0;
}

// solve a game board stored in b using the Naked Single technique only
// the (partial) solution is stored in the input array b
void SolveBoard( int b[][9] )
{
    for (int times=0; times< 81; times++) {
        for (int i=0; i < 81; i++) {
           if (b[(i-i%9)/9][i%9] == 0) {
               b[(i-i%9)/9][i%9] = theOnlyAllowedDigit( b , i );
           }
        }
    }
}

// You do not need to change anything in the main() function
int main()
{
  int board[9][9];    // the 9x9 game board

  ReadBoard( board );

  cout << "Input Sudoku board:" << endl;
  PrintBoard( board );

  // solve the board using the naked single technique only
  SolveBoard( board );

  cout << endl;
  cout << "Final Sudoku board:" << endl;
  PrintBoard( board );

  return 0;
}
