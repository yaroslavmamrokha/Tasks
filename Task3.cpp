#include <iostream>

using namespace std;

enum Grade {
	Incorrect_Grade = -1,
	A_Grade = 'A',
	B_Grade = 'B',
	C_Grade = 'C',
	D_Grade = 'D',
	F_Grade = 'F'	
};

enum Grade_Ranges {
	F_Lower_Bound,
	F_Upper_Bound =59,
	D_Lower_Bound,
	D_Upper_Bound = 69,
	C_Lower_Bound,
	C_Upper_Bound = 79,
	B_Lower_Bound,
	B_Upper_Bound = 89,
	A_Lower_Bound,
	A_Upper_Bound = 100
};
/*
*@[brief]: Function check in what range is income value
*@[in]: integer value in range from 1 to 100
*@[out]: if score in range function outputs it name, else function return -1 to indicate bad score
*/

char Convert_To_Letter_Grade(int score) {
	
	if (score <= Grade_Ranges::F_Upper_Bound && score >= Grade_Ranges::F_Lower_Bound) {
		return Grade::F_Grade;
	}else if (score <= Grade_Ranges::D_Upper_Bound && score >= Grade_Ranges::D_Lower_Bound) {
		return Grade::D_Grade;
	}else if (score <= Grade_Ranges::C_Upper_Bound && score >= Grade_Ranges::C_Lower_Bound) {
		return Grade::C_Grade;
	}else if (score <= Grade_Ranges::B_Upper_Bound && score >= Grade_Ranges::B_Lower_Bound) {
		return Grade::B_Grade;
	}else if (score <= Grade_Ranges::A_Upper_Bound && score >= Grade_Ranges::A_Lower_Bound) {
		return Grade::A_Grade;
	}
	return Grade::Incorrect_Grade;
}
/*
*@[brief]: Function check if istream object state is set to failbit, shows error and fix input stream;
*@[in]: istream object needed for fail check;
*@[out]: bool statement that shows function result, true if failbit enabled and false otherwise;
*/

bool isbadinput(istream& in) {
	if (in.fail()) {
		cout << "Bad input\n";
		in.clear();
		in.ignore();
		return true;
	}
	return false;
}


void main() {
	char Letter_Grade;
	int Numeric_Grade = 0;
	bool check = true;
	while (check) {
		cout << "Welcome to grade converter\n";
		cout << "Please enter your grade in numeric form (0-100)\n";
		cin >> Numeric_Grade;
		check = isbadinput(cin);
		if (!check) {
			if (Numeric_Grade<Grade_Ranges::F_Lower_Bound || Numeric_Grade>Grade_Ranges::A_Upper_Bound) {
				cout << "Value not in range (0-100)\n";
				check = true;
			}
		}
	}
	Letter_Grade = Convert_To_Letter_Grade(Numeric_Grade);
	if (Numeric_Grade == Grade_Ranges::A_Upper_Bound) {
		cout << "You got perfect score!!\n";
	}
	cout << "Your score in letter grade is ( " << Letter_Grade << " )\n";


}
