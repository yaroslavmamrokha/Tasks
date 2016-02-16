#include <iostream>
#include <math.h>
#include <string>
#include<iomanip>

#define MAX_NUMBER 1000
#define MIN_NUMBER 0
using namespace std;
struct Tetrahedron_Pyramid_Edges {
	int AB;
	int CD;
	int AC;
	int BD;
	int BC;
	int AD;
};
class Tetrahedron_Pyramid {
private:
	Tetrahedron_Pyramid_Edges edges;
	double volume;
	double A_spec;
	double B_spec;
	double C_spec;
protected:
	void Calculate_Specs();
	bool Indiv_Check(int);
	bool Is_Bad_Data();
	void Calculate_Volume();
public:
	Tetrahedron_Pyramid() = default;
	Tetrahedron_Pyramid(Tetrahedron_Pyramid_Edges ed) {
		edges = ed;
		Calculate_Specs(); 
		Calculate_Volume();
	}
	Tetrahedron_Pyramid(const Tetrahedron_Pyramid&) = default;
	Tetrahedron_Pyramid(Tetrahedron_Pyramid&&) = default;
	~Tetrahedron_Pyramid() {
		memset(&edges, MIN_NUMBER, sizeof(edges));
	}

	friend ostream& operator<<(ostream&, const Tetrahedron_Pyramid&);
	friend istream& operator>>(istream&, Tetrahedron_Pyramid&);
	friend bool isbadinput(istream&);
};
/*
*@[brief]: overloaded output operator for class Tetrahedron_Pyramid
*@[in]: ostream object and const reference to Tetrahedron_Pyramid object
*@[out]: ostream reference for chain output
*/
ostream & operator<<(ostream & out, const Tetrahedron_Pyramid & obj)
{
	auto def_prec = out.precision();
	fixed(out);
	out.precision(4);
	out << obj.volume;
	out.precision(def_prec);
	out.unsetf(ios::fixed);
	return out;
}
/*
*@[brief]: overloaded input operator for class Tetrahedron_Pyramid
*@[in]: istream object and reference to Tetrahedron_Pyramid object
*@[out]: istream reference for chain input
*/
istream & operator>>(istream & in, Tetrahedron_Pyramid & obj)
{
	bool bad_in = true;
	while (bad_in) {
		in >> obj.edges.AB >> obj.edges.AC >> obj.edges.AD >> obj.edges.BC >> obj.edges.BD >> obj.edges.CD;
		bad_in = isbadinput(in)|obj.Is_Bad_Data();
		if (bad_in) {
			cout << "Bad Input\n";
		}
	}
	obj.Calculate_Specs();
	obj.Calculate_Volume();
	return in;
}
/*
*@[brief]: Function calculates specs for main formula
*/
void Tetrahedron_Pyramid::Calculate_Specs()
{
	A_spec = pow(edges.BD, 2) + pow(edges.CD, 2) - pow(edges.BC, 2);
	B_spec = pow(edges.AD, 2) + pow(edges.CD, 2) - pow(edges.AC, 2);
	C_spec = pow(edges.BD, 2) + pow(edges.AD, 2) - pow(edges.AB, 2);
}
/*
*@[brief]: function check if number is in needed range
*@[in]: test number
*@[out]: true if number incorrect, else false
*/
bool Tetrahedron_Pyramid::Indiv_Check(int num)
{
	if (num > MAX_NUMBER || num < MIN_NUMBER)
		return true;
	return false;
}	
/*
*@[brief]: function checks if all edges are well-defined
*@[out]: true if data is bad, else false
*/
bool Tetrahedron_Pyramid::Is_Bad_Data()
{
	bool tmp1 = Indiv_Check(edges.AB) | Indiv_Check(edges.AC) | Indiv_Check(edges.AD);
	bool tmp2 = Indiv_Check(edges.BD) | Indiv_Check(edges.BC) | Indiv_Check(edges.CD);
	return tmp1 | tmp2;
}
/*
*@[brief]: Function calculates volume of pyramid using specific formula
*/
void Tetrahedron_Pyramid::Calculate_Volume()
{
	 double pow_diff = pow(edges.AD, 2)*pow(A_spec, 2) - pow(edges.BD, 2)*pow(B_spec, 2) - pow(edges.CD, 2)*pow(C_spec, 2);
	 double pow_mult = pow(edges.AD, 2)*pow(edges.BD, 2)*pow(edges.CD, 2);
	 double tmp = 4 * pow_mult - pow_diff + A_spec * B_spec * C_spec;
	 volume = sqrt(tmp) /12;
}

/*
*@[brief]: Function check if istream object state is set to failbit, shows error and fix input stream;
*@[in]: istream object needed for fail check;
*@[out]: bool statement that shows function result, true if failbit enabled and false otherwise;
*/
bool isbadinput(istream& in) {
	if (in.fail()) {
		in.clear();
		in.ignore();
		return true;
	}
	return false;
}

void main(){
	int test_cases;
	cout << "Enter test count: ";
	cin >> test_cases;
	while (test_cases > MAX_NUMBER || test_cases < MIN_NUMBER || isbadinput(cin)) {
		system ("cls");
		cout << "bad input!\n";
		cout << "Enter test count: ";
		cin >> test_cases;
	}
	for (int i = 0; i < test_cases; i++) {
		Tetrahedron_Pyramid obj;
		cout << "Enter edges: AB AC AD BC BD CD\n";
		cin >> obj;
		cout << obj << endl;
	}
}
