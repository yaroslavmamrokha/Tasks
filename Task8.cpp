//PvP TicTacToe Game
#include <iostream>
#include <exception>
#include <vector>
#include<Windows.h>
#include <algorithm>
#include <time.h>

/*************************************Defines for program*************************************************/
#define BAD_INPUT -1
#define EMPTY_FIELD ' '
#define FIELD_SIZE 9
#define PAD_DIVIDER "##"
#define FIELD_DIVIDER "||"
#define SLEEP_PERIOD 400
#define ROWSANDCOLUMNS 3
#define WIN_STREAK 3
#define DIVIDER_BY_THREE 3
#define DIVIDER_BY_FOUR 4
#define DIVIDER_BY_FIVE 5
#define DIVIDER_BY_SIX 6
#define X_TURN 1
#define O_TURN 2
#define X_NAME 'X'
#define O_NAME '0'

/*************************************Namespaces requierd for work****************************************/

using namespace std;

/*************************************Function prototypes*************************************************/

/*
*@[brief]: Function prints gameboard with current Xand0 positions
*@[in]: vector with elements
*/
void Print_Board(vector<char>);

/*
*@[brief]: Function prints pad for choosing positions 
*/
void Print_Pad();

/*
*@[brief]: Function announce winner using char parameter which indicates current turn
*@[in]: current turn in char format
*/
void Announce_Winner(char);

/*
*@[brief]: Function checks for correct input position and check for win/draw 
*@[in]: refernce to vector that handles all positions, it's needed to add marks on positions, also int position and char turn;
*@[out]: boolean value that indicates if something happend, win, lose .. etc
*/
bool Rules_Check(vector<char>&, int, char);

/*
*@[brief]: Function simply runs all needed functions to start game;
*/
void Start_Game();

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

/**********************************************************************************************/

void Print_Board(vector<char> board) {
	int elem_counter = 0;
	cout << FIELD_DIVIDER;
	for (auto x : board) {
		cout << x << FIELD_DIVIDER;
		++elem_counter;
		if ((elem_counter % DIVIDER_BY_THREE) == 0) {
			cout << "\n";
			if (elem_counter != FIELD_SIZE) {
				cout << FIELD_DIVIDER;
			}
		}
	}

}

/**********************************************************************************************/

void Print_Pad() {
	int elem_counter = 0;
	cout << "\n\n\n";
	cout << PAD_DIVIDER;
	static vector<int> pad{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (auto x : pad) {
		cout << x << PAD_DIVIDER;
		++elem_counter;
		if ((elem_counter % DIVIDER_BY_THREE) == 0) {
			cout << "\n";
			if (elem_counter != FIELD_SIZE) {
				cout << PAD_DIVIDER;
			}
		}
	}
}

/**********************************************************************************************/

void Announce_Winner(char turn) {
	cout << "Winner user who played with " << turn << " !!!Congratulations\n";
}

/**********************************************************************************************/

bool Rules_Check(vector<char>& board, int position, char turn) {
	int elem_counter = 0;
	int row_sum = 0;
	vector<int> elem_sums;
	int U_val = WIN_STREAK * turn;
	if (position < 0) {
		cout << "Bad position setting to 0\n";
		position = 0;
	}

	
	try {
		elem_sums.push_back(board.at(0));
		elem_sums.push_back(board.at(1));
		elem_sums.push_back(board.at(2));
		if (board.at(position) == EMPTY_FIELD) {
			board.at(position) = turn;
		}
		else {
			bool ret;
			bool stop = true;
			Sleep(SLEEP_PERIOD);
			system("cls");
			while (stop) {
				cout << "Whoaa sorry but user who play with " << board.at(position) << " already placed there!!\n";
				Print_Board(board);
				Print_Pad();
				cin >> position;
				stop = isbadinput(cin);
			}
			ret = Rules_Check(board, --position, turn);

			return ret;
		}
	}
	catch(exception& ex){
		cout << "Error: " << ex.what() << " can't handle exception closing program\n";
		exit(true);
	}
	for (auto x : board) {
		++elem_counter;
		row_sum += x;

		if ((row_sum / DIVIDER_BY_THREE) == turn) {
			Sleep(SLEEP_PERIOD);
			system("cls");
			Print_Board(board);
			Announce_Winner(turn);
			return true;
		}
		if ((elem_counter % DIVIDER_BY_THREE) == 0) {
			row_sum = 0;
		}
	}

	elem_counter = 0;

	for (auto x : board) {
		++elem_counter;
		try {
			if ((elem_counter % DIVIDER_BY_FOUR) == 0) {
				elem_sums.at(0) += x;
			}
			if ((elem_counter % DIVIDER_BY_FIVE) == 0) {
				elem_sums.at(1) += x;
			}
			if ((elem_counter % DIVIDER_BY_SIX) == 0) {
				elem_sums.at(2) += x;
				elem_counter = ROWSANDCOLUMNS;
			}

		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << " can't handle exception closing program\n";
			exit(true);
		}
		
	}

	vector<int>::iterator winner = find(elem_sums.begin(), elem_sums.end(), U_val);

	if (winner != elem_sums.end()) {
		Sleep(SLEEP_PERIOD);
		system("cls");
		Print_Board(board);
		Announce_Winner(turn);
		return true;
	}
	try {
		elem_counter = 0;
		elem_sums.at(0) = 0;
		elem_sums.at(1) = 0;

		for (int k = 0, j = 2; elem_counter < ROWSANDCOLUMNS; k += 4, j += 2, elem_counter++) {
			elem_sums.at(0) += board.at(k);
			elem_sums.at(1) += board.at(j);
		}
	}
	catch (exception& ex) {
		cout << "Error: " << ex.what() << " can't handle exception closing program\n";
		exit(true);
	}
	

	winner = find(elem_sums.begin(), elem_sums.end(), U_val);
	if (winner != elem_sums.end()) {
		Sleep(SLEEP_PERIOD);
		system("cls");
		Print_Board(board);
		Announce_Winner(turn);
		return true;
	}

	vector<char> ::iterator draw = find(board.begin(), board.end(), EMPTY_FIELD);
	if (draw == board.end()) {
		cout << "Draw!!!\n";
		return true;
	}
	return false;
}

/**********************************************************************************************/

void Start_Game() {
	vector<char> board(FIELD_SIZE, EMPTY_FIELD);
	int position;
	int swapper = 0;
	char turn;
	bool returned = false;
	while (!swapper) {
		Sleep(SLEEP_PERIOD);
		system("cls");
		cout << "Who is playing first: X or 0?: ";
		cin >> turn;
		switch (toupper(turn)) {
		case 'X':
			swapper = X_TURN;
			break;
		case '0':
			swapper = O_TURN;
			break;
		default:
			cout << "Bad input!!\n";
			break;
		}
	}

	while (!returned) {
		Sleep(SLEEP_PERIOD);
		system("cls");
		Print_Board(board);
		Print_Pad();
		cin >> position;
		if (isbadinput(cin)) {
			position = BAD_INPUT;
		}
		switch (--position) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8: 
			turn = (swapper == X_TURN ? X_NAME : O_NAME);
			swapper = (swapper == X_TURN ? O_TURN : X_TURN);
			returned = Rules_Check(board, position, turn);
			break;

		default:
			cout << "Bad input\n";
			break;
		}
	}
}

/**********************************************************************************************/

void main() {
	Start_Game();

}
/**********************************************************************************************/
