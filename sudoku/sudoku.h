#ifndef SUDOKU_H
#define SUDOKU_H
#include<vector>
#include<algorithm>
using namespace std;
/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/

class sudokuSolve {
  public:
    int find_test_index_block(int test_index_row, int test_index_column);
    vector<int> can_fit_in_number(int map[9][9], int test_index_row, int test_index_column);
    bool recursiveSolution(int map[9][9], int test);
    bool can_fit_in_specific_number(int m_temp[9][9],int map[9][9], int *a, int *b, int f, int row, int column);
    bool same(int a[9][9], int b[9][9]);

};

#endif // SUDOKU_H
