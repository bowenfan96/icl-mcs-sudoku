#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
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

/* QUESTION 1 */

bool is_complete(const char board[9][9]) {
    for (int row=0; row<9; row++) {
        for (int col=0; col<9; col++) {
                        
            if ((!isdigit(board[row][col])) || (board[row][col] == 0)) {
                return false;
            }
        }
    }
    return true;
}

/* QUESTION 2 */

bool make_move(const char position[2], const int digit, char board[9][9]) {
    int row = position[0] - 'A';
    int col = position[1] - '1';

    /*
    cout << "\nRow: " << row << endl;
    cout << "Col: " << col << endl;
    */
    
    if ((row < 0 || row > 8) || (col < 0 || col > 8)) {
        return false;
    }
    else if (isdigit(board[row][col])) {
        return false;
    }
    
    for (int row_iter=0; row_iter<9; row_iter++) {
        if (digit == board[row_iter][col]) {
            return false;
        }
    }
        
    for (int col_iter=0; col_iter<9; col_iter++) {
        if (digit == board[row][col_iter]) {
            return false;
        }
    }
    
    int subgrid_row = (row/3)*3;
    int subgrid_col = (col/3)*3;
    
    for (int row_iter=0; row_iter<3; row_iter++) {
        for (int col_iter=0; col_iter<3; col_iter++) {
            if (digit == board[subgrid_row + row_iter][subgrid_col + col_iter]) {
                return false;
            }
        }
    }
    
    board[row][col] = digit;
    return true;
}

/* QUESTION 3 */

bool save_board(const char* filename, char board[9][9]) {
    ofstream file;
    file.open (filename, ios::out);
    
    if (file.is_open()) {
        for (int row=0; row<9; row++) {
            for (int col=0; col<9; col++) {
                file << board[row][col];
            }
            file << endl;
        }
        file.close();
        return true;
    }
    
    else {
        return false;
    }
}

/* QUESTION 4 */

bool solve_board(char board[9][9]) {
    for (int row=0; row<9; row++) {
        for (int col=0; col<9; col++) {
            if (board[row][col] == '.') {
                for (int digit=1; digit<10; digit++) {
                    if (valid_move(row, col, digit, board)) {
                        board[row][col] = digit;
                        solve_board(board);
                        board[row][col] = '.';
                    }
                }
                return true;
            }
        }
    }
    return true;
}
                
                
/* Validity checker */

bool valid_move(const int row, const int col, const int digit, char board[9][9]) {
    for (int row_iter=0; row_iter<9; row_iter++) {
        if (digit == board[row_iter][col]) {
            return false;
        }
    }
        
    for (int col_iter=0; col_iter<9; col_iter++) {
        if (digit == board[row][col_iter]) {
            return false;
        }
    }
    
    int subgrid_row = (row/3)*3;
    int subgrid_col = (col/3)*3;
    
    for (int row_iter=0; row_iter<3; row_iter++) {
        for (int col_iter=0; col_iter<3; col_iter++) {
            if (digit == board[subgrid_row + row_iter][subgrid_col + col_iter]) {
                return false;
            }
        }
    }
    return true;
}
