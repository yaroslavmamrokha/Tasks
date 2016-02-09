#include <iostream>
#include <math.h>
#include <string>
#include<iomanip>
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
	void Calculate_Volume();
public:
	Tetrahedron_Pyramid() = delete;
	Tetrahedron_Pyramid(Tetrahedron_Pyramid_Edges ed) {
		edges = ed;
		Calculate_Specs(); 
		Calculate_Volume();
	}
	Tetrahedron_Pyramid(const Tetrahedron_Pyramid&) = default;
	Tetrahedron_Pyramid(Tetrahedron_Pyramid&&) = default;
	~Tetrahedron_Pyramid() {
		memset(&edges, 0, sizeof(edges));
	}

	friend ostream& operator<<(ostream&, const Tetrahedron_Pyramid&);
};

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

void Tetrahedron_Pyramid::Calculate_Specs()
{
	A_spec = pow(edges.BD, 2) + pow(edges.CD, 2) - pow(edges.BC, 2);
	B_spec = pow(edges.AD, 2) + pow(edges.CD, 2) - pow(edges.AC, 2);
	C_spec = pow(edges.BD, 2) + pow(edges.AD, 2) - pow(edges.AB, 2);
}

void Tetrahedron_Pyramid::Calculate_Volume()
{
	 double pow_diff = pow(edges.AD, 2)*pow(A_spec, 2) - pow(edges.BD, 2)*pow(B_spec, 2) - pow(edges.CD, 2)*pow(C_spec, 2);
	 double pow_mult = pow(edges.AD, 2)*pow(edges.BD, 2)*pow(edges.CD, 2);
	 double tmp = 4 * pow_mult - pow_diff + A_spec * B_spec * C_spec;
	 volume = sqrt(tmp) /12;
}


void main(){
	int test_cases;
	cout << "Enter test count: ";
	cin >> test_cases;
	while (test_cases > 1000 || test_cases < 0) {
		system ("cls");
		cout << "bad input!\n";
		cout << "Enter test count: ";
		cin >> test_cases;
	}
	for (int i = 0; i < test_cases; i++) {
		Tetrahedron_Pyramid_Edges ed;
		cout << "Enter edges: \n";
		cout << "AB: ";
		cin >> ed.AB;
		if (ed.AB > 1000 || ed.AB < 0) {
			cout << "bad input!\n";
			i--;
			continue;
		}
		cout << "AC: ";
		cin >> ed.AC;
		if (ed.AC > 1000 || ed.AC < 0) {
			cout << "bad input!\n";
			i--;
			continue;
		}
		cout << "AD: ";
		cin >> ed.AD;
		if (ed.AD > 1000 || ed.AD < 0) {
			cout << "bad input!\n";
			i--;
			continue;
		}
				
		cout << "BC: ";
		cin >> ed.BC;
		if (ed.BC > 1000 || ed.BC < 0) {
			cout << "bad input!\n";
			i--;
			continue;
		}
		cout << "BD: ";
		cin >> ed.BD;
		if (ed.BD > 1000 || ed.BD < 0) {
			cout << "bad input!\n";
			i--;
			continue;
		}

		cout << "CD: ";
		cin >> ed.CD;
		if (ed.CD > 1000 || ed.CD < 0) {
			cout << "bad input!\n";
			i--;
			continue;
		}
		
		Tetrahedron_Pyramid obj{ ed };
		cout << obj << endl;
	}
}
