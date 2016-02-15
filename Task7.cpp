#include <iostream>
#include <random>
#include <stdlib.h>
#include<string>
#include <time.h>
using namespace std;
enum Guesser {
	bad_num = -1,
	min_number,
	exit_num,
	max_number = 100
};

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
/*
*@[brief]: Function Launch PC logic for guessing user number;
*@[in]: No input requiered;
*@[out]: No return values needed if user is entering incorrect hints, PC will show message and exit program;
*/
void Pc_Guesser() {
	static int previous = Guesser::min_number;
	static int next = Guesser::max_number;
	int current = 0;
	int answer = 0;
	current = (next + previous)/2;
	cout << "Your number is " << current << " ?\n";
	cout << "1) Less?\n";
	cout << "2) Greater?\n";
	cout << "3) Correct!\n";
	
	cin >> answer;
	if (isbadinput(cin)) {
		answer = Guesser::bad_num;
	}
	if ((next - previous) == Guesser::exit_num) {
		cout << "Hey stop fooling me, i dont want to play!!";
		exit(true);
	}
	switch (answer) {
	case 1:
		next = current;
		Pc_Guesser();
		break;
	case 2: 
		previous = current;
		Pc_Guesser();
		break;
	case 3:
		cout << "Phew that was eeeeeasy)\n";
		break;
	default:
		system("cls");
		cout << "Bad input\n";
		Pc_Guesser();
		break;
	}
}
/*
*@[brief]: Function Launch user logic for guessing PC number;
*@[in]: No input requiered;
*@[out]: No return values needed;
*/

void User_Guesser() {
	srand(time(0));
	int pc_value = rand() % Guesser::max_number;
	int user_value = 0;
	int tries = 0;
	cout << "Welcome to pseudo number guesser 2000\n";
	cout << "Computer generated number from 0 to 99\n";
	cout << "Computer will indicate if you're wrong\n";
	cout << "If you will guess the number, game will be over\n";
	cout << "So let's begin\n";
	cout << "Hint: " << pc_value << "\n";
	do {
		cout << "Your answer? : ";
		cin >> user_value;
		if (isbadinput(cin)) {
			user_value = Guesser::bad_num;
			continue;
		}
		++tries;
		if (user_value < pc_value) {
			cout << "\nWrong number, try greater then " << user_value << "\n";
		}
		else if (user_value > pc_value) {
			cout << "\nWrong number, try less then " << user_value << "\n";
		}
	} while (user_value != pc_value);
	cout << "Great you guessed PC's value!!!\n";
	cout << "You tried " << tries << " times.\n";
}

void main() {
	int u_choice = 0;
	cout << "Welcome choose game type\n";
	cout << "1) User guess!\n";
	cout << "2) Pc guess!\n";
	cout << "3) Exit\n";
	cin >> u_choice;

	switch (u_choice) {
	case 1:
		User_Guesser();
		break;
	case 2:
		Pc_Guesser();
		break;
	case 3:
		cout << "Exiting...\n";
		break;
	default:
		cout << "Bad input\n";
		break;
	}
	

}
