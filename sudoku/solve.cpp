#include<iostream>
#include<vector>
#include<algorithm>
#include"sudoku.h"
using namespace std;

int main() {
    /* initialize the variables */
    int i, j, k, find, r[3], c[3], count=0, v_map[9][9], temp[9][9], temp2[9][9];
    bool check=false;

    /* get the sudoku question */
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            cin >> v_map[i][j];
            temp[i][j] = v_map[i][j];
            temp2[i][j] = v_map[i][j];
        }
    }


    sudokuSolve solveObject;


    /* check each index and fill it with the correct number if this number is found out by exclusion method */
    while(true) {
        for(i=0; i<9; i++) {
            switch(i) {
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
            switch(i) {
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
            for(find=1; find<10; find++) {
                for(j=0; j<3; j++) {
                    for(k=0; k<3; k++) {
                        if(v_map[r[j]][c[k]] != 0)
                            continue;
                        check=solveObject.can_fit_in_specific_number(temp,v_map, r, c, find,  r[j], c[k]);
                        if(check == true)
                            count++;
                    }
                }
                if(count == 1) {
                    for(j=0; j<3; j++) {
                        for(k=0; k<3; k++)
                            v_map[r[j]][c[k]] = temp[r[j]][c[k]];
                    }
                } else if(count!=0) {
                    for(j=0; j<3; j++) {
                        for(k=0; k<3; k++)
                            temp[r[j]][c[k]] = v_map[r[j]][c[k]];
                    }
                }
                count = 0;
            }
        }
        check = solveObject.same(temp2, v_map);
        if(check == false)
            break;
    }//end_of_while


    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            temp[i][j] = v_map[i][j];
        }
    }
    
    bool answer = solveObject.recursiveSolution(v_map, 1);
    bool answer2 = solveObject.recursiveSolution(temp, 2);
    count = 0;
    if(answer == true && answer2 == true) {
        for(i=0; i<9; i++) {
            for(j=0; j<9; j++) {
                if(temp[i][j] != v_map[i][j])
                    count++;
            }
        }
    }
    if(answer==false)// there is no answer for this sudoku question
        cout << 0 << endl;
    else if(count>0) // there are more than one answer for this sudoku question
        cout << 2 << endl;
    else {
        cout << 1 << endl;
        for(i=0; i<9; i++) {
            for(j=0; j<9; j++) {
                cout << v_map[i][j];
                if(j!=8) cout << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
