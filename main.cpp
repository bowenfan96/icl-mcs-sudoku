#include <iostream>
#include <cstdio>
#include "sudoku.h"

#include <chrono>

using namespace std;

int main() {

  char board[9][9];
  
  int stack = 0;

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";
  
  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // write more tests

  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  } else {
    cout << "Save board failed." << '\n';
  }
  cout << '\n';
  
  cout << "=================== Question 4 ===================" << "\n\n";

  load_board("easy.dat", board);
  
  auto t1 = std::chrono::high_resolution_clock::now();
  
  if (solve_board(board, &stack)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
    
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    
    cout << "Time elasped: ";
    std::cout << duration;
    
    cout << "\nNumber of stacks: " << stack << '\n';
    stack = 0;
    
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  
  load_board("medium.dat", board);
  
  auto t3 = std::chrono::high_resolution_clock::now();

  if (solve_board(board, &stack)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
    
    auto t4 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t4 - t3 ).count();
    
    cout << "Time elasped: ";
    std::cout << duration;
    
    cout << "\nNumber of stacks: " << stack << '\n';
    stack = 0;
    
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // write more tests

  cout << "=================== Question 5 ===================" << "\n\n";

  // write more tests
  
  load_board("mystery1.dat", board);
  
  auto t5 = std::chrono::high_resolution_clock::now();
  
  if (solve_board(board, &stack)) {
    cout << "The 'mystery1' board has a solution:" << '\n';
    display_board(board);
    
    auto t6 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t6 - t5 ).count();
    
    cout << "Time elasped: ";
    std::cout << duration;
    
    cout << "\nNumber of stacks: " << stack << '\n';
    stack = 0;
    
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  load_board("mystery2.dat", board);
  if (solve_board(board, &stack)) {
    cout << "The 'mystery2' board has a solution:" << '\n';
    display_board(board);
    
    cout << "Number of stacks: " << stack << '\n';
    stack = 0;
    
  } else {
    cout << "A solution cannot be found." << '\n';
    display_board(board);
  }
  cout << '\n';
  
  load_board("mystery3.dat", board);
  
  auto t7 = std::chrono::high_resolution_clock::now();

  if (solve_board(board, &stack)) {
    cout << "The 'mystery3' board has a solution:" << '\n';
    display_board(board);
    
    auto t8 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t8 - t7 ).count();
    
    cout << "Time elasped: ";
    std::cout << duration;
    
    cout << "\nNumber of stacks: " << stack << '\n';
    stack = 0;
    
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
/*
  
  load_board("hardest.dat", board);
  if (solve_board(board, &stack)) {
    cout << "The 'hardest' board has a solution:" << '\n';
    display_board(board);
    
    cout << "Number of stacks: " << stack << '\n';
    stack = 0;
    
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
*/
  
  return 0;
}
