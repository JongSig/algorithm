/*
    No.2753 윤년

    problem
    연도가 주어졌을 때, 윤년이면 1, 아니면 0 출력
    
    윤년
    4의 배수, 100의 배수가 아닐 때, 400의 배수

    input
    2000

    output
    1

*/

#include <iostream>
using namespace std;

int main() {
    int enteredYear;

    cin >> enteredYear;

    if (enteredYear % 4 == 0 && (enteredYear % 100 != 0 || enteredYear % 400 == 0)) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}