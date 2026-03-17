/*
    No.14681 사분면 고르기

    problem
    점의 좌표를 입력받아 어느 사분면에 속하는지 알아내는 프로그램 작성

    input
    12
    5

    output
    1

*/

#include <iostream>
using namespace std;

int main() {
    int inputX, inputY;

    cin >> inputX;
    cin >> inputY;

    if(inputX > 0 && inputY > 0) {
        cout << 1 << endl;
    } else if(inputX < 0 && inputY > 0) {
        cout << 2 << endl;
    } else if(inputX < 0 && inputY < 0) {
        cout << 3 << endl;
    } else {
        cout << 4 << endl;
    }

    return 0;
}