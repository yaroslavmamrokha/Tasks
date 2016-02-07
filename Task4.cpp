#include<iostream>
#include<string>
#include <vector>
using std::cout;
using std::cin;
using std::cerr;
using std::vector;
using std::string;

void main() {
	vector<string> Drinks{ "Cola","Pepsi","Fanta","Sprite","7up" };
	{
		int i = 0;
		cout << "Choose beloved drink\n";
		for (auto x : Drinks) {
			cout << ++i << ") " << x << "\n";
		}
	}
	int choice = 0;
	cin >> choice;
		try {
			cout << Drinks.at(choice - 1) << "\n";    //if subscript out of range at throws out_of_range exeption
		}
		catch (std::out_of_range) {
			cout << "Your choice is not vaild, take your money back\n";
			return;
		}

}
