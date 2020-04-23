#include<iostream>
using namespace std;


int d_table[9][9];

void swap(int &a, int &b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int setStartPoint(int &a) {
    if(a==0) return 0;
    if(a==1) return 3;
    if(a==2) return 6;
}

void duplicate(int a[][9]) {
    int i, j;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++)
            d_table[i][j] = a[i][j];
    }
}
int main() {
    // finish your transform code...
    int i, j, c1, c2, c2_1, c3, c3_1, table[9][9];

    for(i=0; i<9; i++) {
        for(j=0; j<9; j++)
            cin >> table[i][j];
    }


    while(cin >> c1) {
        if(c1 == 0)
            break;
        else if(c1 == 1) {
            scanf("%d %d", &c2, &c3);
            for(i=0; i<9; i++) {
                for(j=0; j<9; j++) {
                    if(table[i][j] == c2) table[i][j] = c3;
                    else if(table[i][j] == c3) table[i][j] = c2;
                }
            }
        } else if(c1 == 2) {
            scanf("%d %d", &c2, &c3);
            c2_1 = setStartPoint(c2);
            c3_1 = setStartPoint(c3);
            for(i=0; i<3; i++, c2_1++, c3_1++) {
                for(j=0; j<9; j++)
                    swap(table[c2_1][j], table[c3_1][j]);
            }
        } else if(c1 == 3) {
            scanf("%d %d", &c2, &c3);
            c2_1 = setStartPoint(c2);
            c3_1 = setStartPoint(c3);
            for(i=0; i<3; i++, c2_1++, c3_1++) {
                for(j=0; j<9; j++)
                    swap(table[j][c2_1], table[j][c3_1]);
            }
        } else if(c1 == 4) {
            cin >> c2;
            c2 = c2%4;
            duplicate(table);
            if(c2 == 1) {
                for(i=0; i<9; i++) {
                    for(j=0; j<9; j++)
                        table[j][8-i] = d_table[i][j];
                }
            } else if(c2 == 2) {
                for(i=0; i<9; i++) {
                    for(j=0; j<9; j++)
                        table[8-i][8-j] = d_table[i][j];
                }
            } else if(c2 == 3) {
                for(i=0; i<9; i++) {
                    for(j=0; j<9; j++)
                        table[8-j][i] = d_table[i][j];
                }
            } else {}
        } else if(c1 == 5) {
            cin >> c2;
            duplicate(table);
            if(c2 == 0) {
                for(i=0; i<9; i++) {
                    for(j=0; j<9; j++)
                        table[8-i][j] = d_table[i][j];
                }
            } else {
                for(i=0; i<9; i++) {
                    for(j=0; j<9; j++)
                        table[j][8-i] = d_table[j][i];
                }
            }
        } else
            cout << "Wrong input format!\n";

    }
    //output
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            cout << table[i][j];
            if(j!=8) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
