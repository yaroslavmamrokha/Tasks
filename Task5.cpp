#include <iostream>

using std::cout;
using std::cin;

enum numbers_type {
	bad_number = 5,
	max_iterations = 10
};

void main() {
	int user_number = 0;
	bool exit_status = false;
	int iterations = 0;
	do {
		cout << "Enter any number exept "<< iterations << " !!\n";
		cin >> user_number;	
	} while (user_number != iterations++);
		cout << "You weren't supposed to enter " << iterations - 1 << "!!!\n";


}
