/*
    No.2884 알람 시계

    problem
    45분 일찍 알람 설정하기

    input
    10 10

    output
    9 25

*/
#include <iostream>
using namespace std;

int main(){
    int H, M;

    cin >> H >> M;

    if (M < 45) {
        
        M = M + 15;

        if (H == 0) {
            H = 23;
        } else {
            H -= 1;
        }

    } else {
        M -= 45;
    }

    cout << H << " " << M << endl;

    return 0;
}