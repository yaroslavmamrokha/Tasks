#include<iostream>
#include<vector>

using namespace std;

class Prime_Generator {
private:
	long long int m_num;
	long long int n_num;
	vector<long long int> primes;
protected:
	vector<long long int>& Generated_Primes();
public:
	Prime_Generator() = delete;
	Prime_Generator(long long int m, long long int n) {
		bool bad_input = true;
		long long int differ = n - m;
		while (m>n||differ>100000|| m<1) {
			cout << "M must be less equal N, both M and N greater or equal 1" << endl;
			cout << "And n - m les equal 100000!" << endl;
			cout << "And N must be less equal 1000000000" << endl;
			cout << "Enter correct M and N: ";
			cin >> m >> n;
			differ = n - m;
		}
		m_num = m;
		n_num = n;
	}
	Prime_Generator(const Prime_Generator&) = default;
	void Print_Prime_Numbers();
	~Prime_Generator() {  m_num = -1; n_num = -1; }
};

vector<long long int>& Prime_Generator::Generated_Primes()
{
	int divy = 0;
	for (long long int i = m_num; i <= n_num; i++){
		for (long long int j = 2; j <= i; j++) {
			if ((i%j) == 0) {
				++divy;
			}
		}
		if (divy == 1) {
			primes.push_back(i);
	
		}
		divy = 0;
	}
	return primes;
}

void Prime_Generator::Print_Prime_Numbers()
{
	vector<long long int> tmp_primes{ Generated_Primes() };
	for (auto x : tmp_primes) {
		cout << x << endl;
	}
}



void main() {
	Prime_Generator obj(1, 100);
	obj.Print_Prime_Numbers();


}
