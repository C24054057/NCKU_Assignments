#include<iostream>
#include<vector>
#include<algorithm>
#include"sudoku.h"
using namespace std;

int sudokuSolve::find_test_index_block(int test_index_row, int test_index_column) {
    //0,1,2
    //3,4,5
    //6,7,8
    int r,c;
    r = test_index_row / 3;
    c = test_index_column / 3;
    return 3*r+c;
}

vector<int> sudokuSolve::can_fit_in_number(int map[9][9], int test_index_row, int test_index_column) {
    int count[10] = {0,0,0,0,0,0,0,0,0,0};
    vector<int> result;
    int index_block = find_test_index_block(test_index_row,test_index_column);
    int i, j, k, r[3], c[3];

    //row
    for(i=0; i<9; i++) {
        if(map[i][test_index_column] != 0)
            count[map[i][test_index_column]]++;
    }

    //column
    for(i=0; i<9; i++) {
        if(map[test_index_row][i] != 0)
            count[map[test_index_row][i]]++;
    }

    //block
    switch(index_block) {
    case 0:
    case 1:
    case 2:
        r[0]=0;
        r[1]=1;
        r[2]=2;
        break;
    case 3:
    case 4:
    case 5:
        r[0]=3;
        r[1]=4;
        r[2]=5;
        break;
    case 6:
    case 7:
    case 8:
        r[0]=6;
        r[1]=7;
        r[2]=8;
        break;
    }
    switch(index_block) {
    case 0:
    case 3:
    case 6:
        c[0]=0;
        c[1]=1;
        c[2]=2;
        break;
    case 1:
    case 4:
    case 7:
        c[0]=3;
        c[1]=4;
        c[2]=5;
        break;
    case 2:
    case 5:
    case 8:
        c[0]=6;
        c[1]=7;
        c[2]=8;
        break;
    }
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(map[r[i]][c[j]] != 0)
                count[map[r[i]][c[j]]]++;
        }
    }

    for(i=1; i<10; i++) {
        if(count[i] == 0)
            result.push_back(i);
    }
    return result;
}

bool sudokuSolve::recursiveSolution(int map[9][9], int test) {
    bool result = false;
    int i, j;
    int r=-1, c=-1;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            if(map[i][j] == 0) {
                r=i;
                c=j;
                break;
            }

        }
    }
    if(r==-1 && c==-1)
        return true;

    vector<int> canFitInNumber(can_fit_in_number(map,r,c));
    if(canFitInNumber.size()==0)
        return false;
    if(test == 1) {
        for(i=0; i<canFitInNumber.size(); i++) {
            map[r][c] = canFitInNumber[i];
            result = recursiveSolution(map,1);
            if(result == true)
                break;
        }
    } else {
        for(i=canFitInNumber.size()-1; i>=0; i--) {
            map[r][c] = canFitInNumber[i];
            result = recursiveSolution(map,2);
            if(result == true)
                break;
        }
    }

    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            if(map[i][j] == 0) {
                map[r][c] = 0;
                return false;
            }
        }
    }

    return true;
}
bool sudokuSolve::can_fit_in_specific_number(int m_temp[9][9],int map[9][9], int *a, int *b, int f, int row, int column) {
    int i,j;
    for(i=0; i<9; i++) {
        if(map[i][column] == f) return false;
        if(map[row][i] == f) return false;
    }
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++)
            if(map[a[i]][b[j]] == f) return false;
    }
    m_temp[row][column] = f;
    return true;
}

bool sudokuSolve::same(int a[9][9], int b[9][9]) {
    int i, j, count=0;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            if(a[i][j] != b[i][j]) {
                count++;
                a[i][j] = b[i][j];
            }
        }
    }
    if(count > 0)
        return true;
    else
        return false;
}
