#include <vector>
#include <iostream>

using namespace std;

void main() {
	vector<int> numbers;
	int input = 0;
	int counter = 0;
	bool valid_input = true;
	bool stop_input = false;
	bool bad_input = true;
	cout << "Enter numbers: " << endl;
	while (true) {
		cin >> input;
		if (input == 42) {
			while (bad_input) {
			cout << "Do you want to stop input? Y/N" << endl;
			char ch;
			cin >> ch;
				switch (toupper(ch)) {
				case 'Y':
					stop_input = true;
					bad_input = false;
					break;
				case 'N':
					bad_input = false;
					break;
				default:
					bad_input = true;
					break;
				}
		}
			valid_input = false;
		}
		if (stop_input) {
			break;
		}
		if (valid_input) {
			numbers.push_back(input);
		}
		else {
			counter++;
			if (counter % 10 == 0) {
				while (bad_input) {
				cout << "Do you want to stop input? Y/N" << endl;
				char ch;
				cin >> ch;
			
					switch (toupper(ch)) {
					case 'Y':
						stop_input = true;
						bad_input = false;
						break;
					case 'N':
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
		cout << x << endl;
	}

}
