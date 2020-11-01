#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>   // standard library that provides the isdigit() function
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */


/* TASK 1 */

bool is_complete(const char board[9][9]) {
    // iterate through all cells from left to right, then top to bottom
    for (int row=0; row<9; row++) {
        for (int col=0; col<9; col++) {
            
            // check if the char in each cell is a digit (0 to 9) - using isdigit() from cctype
            // outputs false if the char is not a digit, OR if the digit is 0
            if ((!isdigit(board[row][col])) || (board[row][col] == '0')) {
                return false;
            }
        }
    }
    return true;
}


/* TASK 2 */

bool make_move(const char position[2], const char digit, char board[9][9]) {
    // translate the position characters into integers which locate the cell in the board array
    int row = position[0] - 'A';
    int col = position[1] - '1';
    
    // check if the position given is out of bounds
    if ((row < 0 || row > 8) || (col < 0 || col > 8)) {
        return false;
    }
    
    // check if the position given is already occupied by a digit
    else if (isdigit(board[row][col])) {
        return false;
    }
    
    // check if the same digit already exists on the same column
    for (int row_iter=0; row_iter<9; row_iter++) {
        if (digit == board[row_iter][col]) {
            return false;
        }
    }
        
    // check if the same digit already exists on the same row
    for (int col_iter=0; col_iter<9; col_iter++) {
        if (digit == board[row][col_iter]) {
            return false;
        }
    }
    
    // check if the same digit already exists in the same subgrid
    int subgrid_row = (row/3)*3;
    int subgrid_col = (col/3)*3;
    
    for (int row_iter=0; row_iter<3; row_iter++) {
        for (int col_iter=0; col_iter<3; col_iter++) {
            if (digit == board[subgrid_row + row_iter][subgrid_col + col_iter]) {
                return false;
            }
        }
    }
    
    // if this line is reached, the move is valid and the digit is placed
    board[row][col] = digit;
    
    return true;
}


/* TASK 3 */

bool save_board(const char* filename, char board[9][9]) {
    // declare a file object and associate the actual file with it; set mode to output (write)
    ofstream file;
    file.open (filename, ios::out);
    
    // check if file is successfully opened
    // then iterate through each cell and write value to file
    if (file.is_open()) {
        for (int row=0; row<9; row++) {
            for (int col=0; col<9; col++) {
                file << board[row][col];
            }
            file << endl;
        }
        
        // check if the write operation was successful using the state flag "fail()"
        if (!file.fail()) {
            file.close();
            return true;
        }
    }
    
    // this line is reached only if the file cannot be opened,
    // OR if it is opened but the write failed
    return false;
}


/* TASK 4 */

/* Validity checker */
// Helper function for solve_board() with code borrowed from TASK 2
// Returns true if the digit is unique in its row, column, and subgrid (i.e. obey Sudoku rules),
// returns false otherwise

bool valid_move(int row, int col, const int digit, char board[9][9]) {
    // cast integer digit as ASCII character
    char asc_digit = digit + '0';
    
    // check if the same digit already exists on the same column
    for (int row_iter=0; row_iter<9; row_iter++) {
        if (asc_digit == board[row_iter][col]) {
            return false;
        }
    }
    
    // check if the same digit already exists on the same row
    for (int col_iter=0; col_iter<9; col_iter++) {
        if (asc_digit == board[row][col_iter]) {
            return false;
        }
    }
    
    // check if the same digit already exists in the same subgrid
    int subgrid_row = (row/3)*3;
    int subgrid_col = (col/3)*3;
    
    for (int row_iter=0; row_iter<3; row_iter++) {
        for (int col_iter=0; col_iter<3; col_iter++) {
            if (asc_digit == board[subgrid_row + row_iter][subgrid_col + col_iter]) {
                return false;
            }
        }
    }
    
    // if this line is reached, the move is valid
    return true;
}

/* Solver */
// Solves the board using a recursive backtracking algorithm
// This is a brute-force algorithm which tests all cells starting from the digit 1
// until a dead-end is reached
// It then backtracks to the previous cell and increases the trial digit by 1
// In doing so, possible cell values are exhaustively tested until a solution is found

bool solve_board(char board[9][9]) {
    // iterate through all cells from left to right, then top to bottom
    for (int row=0; row<9; row++) {
        for (int col=0; col<9; col++) {
            
            // check if cell is empty
            if (board[row][col] == '.') {
                
                // if cell is empty, try to put the smallest valid digit in it
                for (int digit=1; digit<10; digit++) {
                    if (valid_move(row, col, digit, board)) {
                        
                        board[row][col] = digit + '0';
                        
                        // the function calls itself, but will skip the current cell, n,
                        // as a digit has already been placed
                        // if a valid move exists for the next cell, n+1, the move is made and
                        // the function calls itself again, moving to cell n+2
                        
                        // if no valid move exists, the function backtracks to cell n-1
                        // and attempts now to place the next smallest valid digit in it
                        // if no valid move exists for cell n-1, then it backtracks to cell n-2,
                        // and so on, until a valid move is possible
                        
                        solve_board(board);
                        
                        // the following if statement is reached on recursion stack n 
                        // if stack n+1 returns
                        // n+1 will return only if it reaches a dead-end, OR if the board is complete
                        
                        // if cell n+1 reaches a dead-end, then we must have made a wrong move
                        // in cell n (or earlier)
                        // hence, we reset cell n and try to place the next valid digit in it
                        
                        if (!is_complete(board)) {
                            board[row][col] = '.';
                        }
                    }
                }
                
                // this line is reached if the solution is found, OR if we have reached a dead-end
                // if the solution is found, the recursion stacks return true successively
                // until the original call in main() is reached
                if (is_complete(board)) {
                    return true;
                }
                
                // this line is reached only if we have reached a dead-end
                // we return to the previous cell and try the next valid digit
                // if this line is still reached after we tested all cells with digits, then
                // there is no possible solution for the puzzle
                return false;
            }
        }
    }
    
    // the next return line is reached only once - when the solution has just been found
    // the final recursion is called, and the last stack frame pops onto the stack
    // it discovers that the board is filled and nothing needs to be done, so
    // it returns and pops itself off, and every previous stack frame starts to get popped off,
    // until main() is reached
    
    return true;
}
