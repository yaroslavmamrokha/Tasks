#include <iostream>
#include<sstream>
#include<ctime>
#include<limits>
#include <string>
#include <exception>
using namespace std;
#define DEF_SIZE 40


class Crypter {
private: 
	time_t user_time;
	string date;
protected:
	bool iscorrectinput();
	friend bool isbadinput(istream&);
public:
	Crypter(time_t t_sec) :user_time{ t_sec } {}
	Crypter() = delete;
	Crypter(const Crypter&) = default;
	~Crypter() {
		cout << "Destr" << endl;
		date.clear();
		user_time = 0;
	}
	void ConvertToDate();
	friend ostream& operator<<(ostream&, const Crypter&);
};

/*
*@[brief]: Function check if user_time is not negative, it helps to find if user entered negetive or higher value then time_t can handle;
*@[out]: bool statement that shows function result, true if user_time is valid and false otherwise;
*/
bool Crypter::iscorrectinput()
{
	if(user_time<0)
		return false;
	return true;
}

/*
*@[brief]: Function converts user_time in second to date
*@[out]: function is void cause it assign date to private data;
*/
void Crypter::ConvertToDate()
{
	while (!iscorrectinput() || isbadinput(cin)) {
		cout << "Error incorrect input!\n";
		cout << "Enter user time in seconds: ";
		cin >> user_time;
	}
	char tmp[DEF_SIZE];
		strftime(tmp, sizeof(tmp), "%a %d %b %Y %HH:%MM:%SS", localtime(&user_time));
		date.assign(tmp);
}

/*
*@[brief]: Function check if istream object state is set to failbit, shows error and fix input stream;
*@[in]: istream object needed for fail check;
*@[out]: bool statement that shows function result, true if failbit enabled and false otherwise;
*/

bool isbadinput(istream & in)
{
	if (in.fail()) {
		cout << "Bad input\n";
		in.clear();
		in.ignore();
		return true;
	}
	return false;
}
/*
*@[brief]: Friend output operator for Crypto class used to output date;
*@[in]: ostream object for out put, and const class object for date member, and secure from modifications;
*@[out]: ostream object for needed to make chain output available;
*/
ostream & operator<<(ostream &os, const Crypter &obj)
{
	cout << obj.date;
	return os;
}


void main() {
	time_t timestamp;
	bool check = true;
	while (check) {
		cout << "Enter timestamp in seconds: ";
		cin >> timestamp;
		check = isbadinput(cin);
	}
	Crypter date{ timestamp };
	date.ConvertToDate();
	cout << date << "\n";
}
