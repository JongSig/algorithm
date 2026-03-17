/*
	No.9498 시험 성적

	problem
	학점을 출력하는 프로그램 작성

	input
	100

	output
	A

*/

#include <iostream>
using namespace std;

int main(){
	int enteredScore;

	cin >> enteredScore;

	if (enteredScore >= 90) {
		cout << "A" << endl;
	} else if (enteredScore >= 80) {
		cout << "B" << endl;
	} else if (enteredScore >= 70) {
		cout << "C" << endl;
	} else if (enteredScore >= 60) {
		cout << "D" << endl;
	} else {
		cout << "F" << endl;
	}

	return 0;
}