/*
    No.2525 오븐 시계

    problem
    오븐구이가 끝나는 시간 계산하는 프로그램 작성

    input
    14 30
    20

    output
    14 50

*/
#include<iostream>
using namespace std;

int main(){
    int entered_H, entered_M;
    int H, M;
    int cookTime;

    cin >> entered_H >> entered_M;
    cin >> cookTime;

    H = entered_H;
    M = entered_M + cookTime;

    if (M >= 60) {
        H += M/60;
        M %= 60;

        if (H > 23) {
            H %= 24;
        }
    }

    cout << H << " " << M << endl;

    return 0;
}