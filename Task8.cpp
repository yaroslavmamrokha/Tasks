//PvP TicTacToe Game
#include <iostream>
#include <vector>
#include<Windows.h>
#include <algorithm>
#include <time.h>

/*************************************Defines for program*************************************************/

#define EMPTY_FIELD ' '
#define FIELD_SIZE 9
#define PAD_DIVIDER "##"
#define FIELD_DIVIDER "||"
#define SLEEP_PERIOD 400
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

void Print_Board(vector<char>);
void Print_Pad();
void Announce_Winner(char);
bool Rules_Check(vector<char>&, int, char);
void Start_Game();
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
	int U_val = 3 * turn;
	vector<int> elem_sums{ board[0],board[1],board[2] };

	if (board[position] == EMPTY_FIELD) {
		board[position] = turn;
	}
	else {
		bool ret;
		Sleep(SLEEP_PERIOD);
		system("cls");
		cout << "Whoaa sorry but user who play with " << board[position] << " already placed there!!\n";
		Print_Board(board);
		Print_Pad();
		cin >> position;
		ret = Rules_Check(board, --position, turn);

		return ret;
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
		if ((elem_counter % DIVIDER_BY_FOUR) == 0) {
			elem_sums[0] += x;
		}
		if ((elem_counter % DIVIDER_BY_FIVE) == 0) {
			elem_sums[1] += x;
		}
		if ((elem_counter % DIVIDER_BY_SIX) == 0) {
			elem_sums[2] += x;
			elem_counter = 3;
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

	elem_counter = 0;
	elem_sums[0] = 0;
	elem_sums[1] = 0;

	for (int k = 0, j = 2; elem_counter < 3; k += 4, j += 2, elem_counter++) {
		elem_sums[0] += board[k];
		elem_sums[1] += board[j];
	}

	winner = find(elem_sums.begin(), elem_sums.end(), U_val);
	if (winner != elem_sums.end()) {
		Sleep(500);
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
	char pos = 0;
	int position;
	int swapper = 0;
	char turn;
	bool returned = false;
	while (!swapper) {
		Sleep(SLEEP_PERIOD);
		system("cls");
		cout << "Who is playing first: X or 0?: ";
		cin >> turn;
		switch (turn) {
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
		cin >> pos;
		position = pos -'0';
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
