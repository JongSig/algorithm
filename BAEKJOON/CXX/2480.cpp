/*
    No.2480 주사위 세개

    problem
    3개의 주사위를 던져서 상금을 받는 게임
    
    1. 같은 주사위 3개, 10,000 + (같은 눈) x 1,000
    2. 같은 주사위 2개, 1,000 + (같은 눈) x 100
    3. 서로 다른 주사위, (그 중 가장 큰 눈) x 100

    상금을 계산하는 프로그램 작성

    input
    3 3 6

    output
    1300

*/

#include <iostream>
using namespace std;

int main(){
    int dice1, dice2, dice3;
    int maxValue;
    int prizeMoney;

    cin >> dice1 >> dice2 >> dice3;

    maxValue = dice1;

    if (dice2 > maxValue) maxValue = dice2;
    if (dice3 > maxValue) maxValue = dice3;

    if (dice1 == dice2 && dice2 == dice3) {
        prizeMoney = 10000 + dice1 * 1000;
    } else if (dice1 == dice2) {
        prizeMoney = 1000 + dice1 * 100;
    } else if (dice1 == dice3) {
        prizeMoney = 1000 + dice1 * 100;
    } else if (dice2 == dice3) {
        prizeMoney = 1000 + dice2 * 100;
    } else {
        prizeMoney = maxValue * 100;
    }

    cout << prizeMoney << endl;

    return 0;
}