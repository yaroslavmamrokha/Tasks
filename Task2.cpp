#include<iostream>
#include<vector>
#include<exception>

using namespace std;
using llint = long long int;

bool isbadinput(istream&);

class Prime_Generator {
private:
	llint m_num;
	llint n_num;
	vector<llint> primes;
protected:
	friend bool isbadinput(istream&);
public:
	enum PrimeClassNums {
		TrashNum = -1,
		CorrectDiv = 2,
		LowerBound = 1,
		DiffUpperBound = 100000,
		UpperBound = 1000000000
	};
	Prime_Generator() = delete;
	Prime_Generator(llint m, llint n) {
		m_num = m;
		n_num = n;
	}
	void Generate_Primes();
	Prime_Generator(const Prime_Generator&) = default;
	friend ostream& operator<<(ostream&, const Prime_Generator&);
	~Prime_Generator() {  m_num = TrashNum; n_num = TrashNum; }
};

/*
*@[brief]: friend function for Prime generator class, Function provides specific output for class object
*@[in]: ostream object for output and Prime_Generator const object, for access to needed data without modifing it  
*@[out]: ostream object reference for chain output; 
*/
ostream&operator<<(ostream& os, const Prime_Generator& obj) {
	for (const auto x : obj.primes) {
		os << x << endl;
	}
	return os;
}
/*
*@[brief]: Function generates prime numbers using modular algorithm;
*@[in]: Function doesn't requier any input data cause it uses private data members, and is secured from bad input;
*@[out]: No output provided cause all generated numbers store in private data part;
*/
void Prime_Generator::Generate_Primes()
{
	bool bad_input = false;
	llint differ = n_num - m_num;
	//This condition check out of range possibility, and non integer input
	while (n_num > UpperBound || differ > DiffUpperBound || m_num < LowerBound || bad_input) {
		cout << "M must be less equal N, both M and N greater or equal 1\n";
		cout << "And n - m les equal 100000!\n";
		cout << "And N must be less equal 1000000000\n";
		cout << "Enter correct M and N: ";
		cin >> m_num >> n_num;
		differ = n_num - m_num;
		bad_input = isbadinput(cin);
	}

	int divy = 0;
	for (llint i = m_num; i <= n_num; i++){
		//Divide on 2(CorrectDiv) cause all numbers can be divided on 1, so thats why we ignore it
		for (llint j = CorrectDiv; j <= i; j++) {
			if ((i%j) == 0) {
				++divy;
			}
		}
		if (divy == 1) {
			primes.push_back(i);
	
		}
		divy = 0;
	}
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
	int test_cases = Prime_Generator::TrashNum;
	bool check = false;
	// pair and vector of pairs used to provide first of all input of rangesk for every test case and then use it for generator
	pair<llint, llint>input_pair;
	vector<pair<llint, llint>>input_data;
	while (test_cases < 0 || check) {
		cout << "enter tests count(>0): ";
		cin >> test_cases;
		check = isbadinput(cin);
	}
	for (int i = 0; i < test_cases; (check == false)? i++:i) {
		cout << "Enter M and N to generate prime numbers for test# "<<i+1<<": ";
		cin >> input_pair.first >> input_pair.second;
		check = isbadinput(cin);
		if (!check) {
			input_data.push_back(input_pair);
		}
	}
	cout << "\nOutput:\n";
	for (int i = 0; i < test_cases; i++) {
		cout << "Test #" << i + 1 << "\n";
		try {
			Prime_Generator testI(input_data.at(i).first, input_data.at(i).second);
			testI.Generate_Primes();
			cout << testI << endl;
			
		}
		catch (out_of_range) {
			cout << "iterator out of range, closing program\n";
			break;
		}

		catch (exception& ex) {
			cout << "Error:" << ex.what() << " can't handle, closing program\n";
			break;
		}
		catch (...) {
			cout << "Undefined error, can't handle closing program\n";
			break;
		}
	}


}
