void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

bool is_complete(const char board[9][9]);
bool make_move(const char position[2], int digit, char board[9][9]);
bool save_board(const char* filename, char board[9][9]);

bool valid_move(int row, int col, const char digit, char board[9][9]);
bool solve_board(char board[9][9], int *stack);
