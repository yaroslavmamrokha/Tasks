#include <iostream>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
enum Grade {
	A_Grade = 'A',
	B_Grade = 'B',
	C_Grade = 'C',
	D_Grade = 'D',
	F_Grade = 'F'
};

char Convert_To_Letter_Grade(int score) {
	
	if (score <= 59 && score >=0) {
		return Grade::F_Grade;
	}else if (score <= 69 && score >= 60) {
		return Grade::D_Grade;
	}else if (score <= 79 && score >= 70) {
		return Grade::C_Grade;
	}else if (score <= 89 && score >= 80) {
		return Grade::B_Grade;
	}else if (score <= 100 && score >= 90) {
		return Grade::A_Grade;
	}
}




void main() {
	char Letter_Grade;
	int Numeric_Grade = 0;
	cout << "Welcome to grade converter\n";
	cout << "Please enter your grade in numeric form (0-100)\n";
	cin >> Numeric_Grade;

	Letter_Grade = Convert_To_Letter_Grade(Numeric_Grade);
	if (Numeric_Grade == 100) {
		cout << "You got perfect score!!\n";
	}
	cout << "Your score in letter grade is ( " << Letter_Grade << " )\n";


}
