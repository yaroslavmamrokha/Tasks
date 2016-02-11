#include <vector>
#include <iostream>

using namespace std;
enum Numbs {
	STOP_NUMBER = 42,
	DIVISOR = 10
};



void main() {
	const char Yes = 'Y';
	const char No = 'N';
	vector<int> numbers;
	int input = 0;
	int counter = 0;
	bool valid_input = true;
	bool stop_input = false;
	bool bad_input = true;
	cout << "Enter numbers: " << endl;
	while (true) {
		cin >> input;
		//Handling non-integer input
		if (cin.fail()) {
			cout << "Non-integer value\n";
			cin.clear();
			cin.ignore();	
			continue;
		}
		//Checking if user entered 42 to stop adding numbers to sequence
		if (input == Numbs::STOP_NUMBER) {
			bad_input = true;
			while (bad_input) {
				cout << "Do you want to stop input? Y/N" << endl;
				char ch;
				cin >> ch;
				switch (toupper(ch)) {
				case Yes:
					stop_input = true;
					bad_input = false;
					break;
				case No:
					bad_input = false;
					break;
				default:
					bad_input = true;
					break;
				}
			}
			valid_input = false; //stop adding numbers
		}
		// if user asked to stop input, break loop and goto output
		if (stop_input) {
			break;
		}
		
		if (valid_input) {
			numbers.push_back(input);
		}else {
			//ask each 10nth number if user want to stop entering numbers
			counter++;
			if (counter % Numbs::DIVISOR == 0) {
				bad_input = true;
				while (bad_input) {
					cout << "Do you want to stop input? Y/N" << endl;
					char input_ch;
					cin >> input_ch;

					switch (toupper(input_ch)) {
					case Yes:
						stop_input = true;
						bad_input = false;
						break;
					case No:
						bad_input = false;
						break;
					default:
						bad_input = true;
						break;
					}
				}
				if (stop_input) {
					break;
				}
			}
		}
	}
	cout << "Output: " << endl;
	for (auto x : numbers) {
		cout << x <<"\n";
	}

}
