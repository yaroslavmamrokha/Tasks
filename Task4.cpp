#include<iostream>
#include<string>
#include <vector>
using namespace std;

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
	vector<string> Drinks{ "Cola","Pepsi","Fanta","Sprite","7up" };
	int choice = 0;
	bool check = true;
	while (check) {
		{
			int i = 0;
			cout << "Choose beloved drink\n";
			for (auto x : Drinks) {
				cout << ++i << ") " << x << "\n";
			}
		}
		cin >> choice;
		check = isbadinput(cin);
	}
		try {
			cout << Drinks.at(choice - 1) << "\n";    //if subscript out of range at throws out_of_range exeption
		}
		catch (out_of_range) {
			cout << "Your choice is not vaild, take your money back\n";
			return;
		}

}
