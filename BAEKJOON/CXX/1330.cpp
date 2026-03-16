/*
    No.1330 두 수 비교하기

    problem
    두 정수 A와 B가 주어졌을 때, A와 B를 비교하는 프로그램 작성

    input
    1 2

    output
    >
*/

#include <iostream>
using namespace std;

int main(void) {
    int A, B;
    
    cin >> A >> B;
    
    if (A > B) {
        cout << ">" << endl;
    }else if (A < B) {
        cout << "<" << endl;
    } else {
        cout << "==" << endl;
    }

    return 0;
}