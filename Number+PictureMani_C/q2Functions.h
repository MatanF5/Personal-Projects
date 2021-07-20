#ifndef __Q2FUNCTIONS__
#define __Q2FUNCTIONS__
enum Move { MOVE_UP = 0, MOVE_DOWN = 1, MOVE_LEFT = 2, MOVE_RIGHT = 3 };
void gameStart(int* mat, int rows, int cols, const int SHUFFEL_COUNT);
int gameUpdate(int* mat, int rows, int cols, enum Move move);
int gameIsFinished(int* mat, int rows, int cols);
int gameMove(int *mat, int rows, int cols,int number);
#endif
