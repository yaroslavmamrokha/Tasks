#include <string>
#include <iostream>
using namespace std;

class Polish_Converter {
private:
	enum Op_sym {
		PLUS = '+',
		MINUS = '-',
		MULTIP = '*',
		DIVID = '/',
		POW = '^',
		L_BRACE = '(',
		R_BRACE = ')',
		SPACE_SYM = ' '
	};
	string input_string;
	string output_string;
	string op_stack;
protected:
	char last_sym;
public:
	Polish_Converter() = default;
	Polish_Converter(string in) : input_string(in){}
	Polish_Converter(const Polish_Converter&) = default;
	~Polish_Converter() { input_string.clear(); output_string.clear(); op_stack.clear(); }

	string Get_Input_String()const;
	string Get_Output_String()const;
	void Set_Input_String(string);
	void Convert_To_Polish();

	friend ostream& operator<<(ostream&, const Polish_Converter&);
};

ostream& operator<<(ostream& out, const Polish_Converter& obj) { 
	out << obj.output_string;
	return out;
}

void Polish_Converter::Convert_To_Polish()
{
	for (auto x : input_string) {
		if (isspace(x)) {
			continue;
		}
		if (isalpha(x)||isdigit(x)) {
			output_string.push_back(x);
		}
		switch (x) {
		case PLUS:
		case MINUS:
			output_string.push_back(SPACE_SYM);
			if (op_stack.empty()) {
				op_stack.push_back(x);
			}
			else {
				last_sym = op_stack.back();
				switch (last_sym) {
				case PLUS:
				case MINUS:
				case MULTIP:
				case DIVID:
				case POW:
					output_string.push_back(op_stack.back());
					op_stack.pop_back();
					op_stack.push_back(x);
					output_string.push_back(SPACE_SYM);
					break;
				case L_BRACE:
					op_stack.push_back(x);
					break;
				}
			}
			break;
		case MULTIP:
		case DIVID:
			output_string.push_back(SPACE_SYM);
			if (op_stack.empty()) {
				op_stack.push_back(x);
			}
			else {
				last_sym = op_stack.back();
				switch (last_sym) {
				case MULTIP:
				case DIVID:
				case POW:
					output_string.push_back(op_stack.back());
					op_stack.pop_back();
					op_stack.push_back(x);
					output_string.push_back(SPACE_SYM);
					break;
				case L_BRACE:
					op_stack.push_back(x);
					break;
				}
			}
			break;
		case POW:
			output_string.push_back(SPACE_SYM);
		case L_BRACE:
			op_stack.push_back(x);
			break;
		case R_BRACE:
			int tmp_count = 0;
			output_string.push_back(SPACE_SYM);
			string::iterator b = op_stack.end()-1;
			for (; *b != L_BRACE; --b) {
				output_string.push_back(*b);
				output_string.push_back(SPACE_SYM);
				tmp_count++;
			}
			tmp_count++;
			op_stack.erase(op_stack.end() - tmp_count, op_stack.end());
			break;
		}
	}
	if (!op_stack.empty()) {
		string::iterator b = op_stack.end() - 1;
		for (; b != op_stack.begin()-1; --b) {
			output_string.push_back(*b);
		}
		output_string.push_back(SPACE_SYM);
		op_stack.clear();
	}
}

string Polish_Converter::Get_Input_String() const
{
	return input_string;
}

string Polish_Converter::Get_Output_String() const
{
	return output_string;
}

void Polish_Converter::Set_Input_String(string in)
{
	input_string = in;
}

void main() {
	Polish_Converter obj;
	obj.Set_Input_String("((a + b)/(3*2/4^3))");
	obj.Convert_To_Polish();
	cout << obj << endl;
	Polish_Converter * p_obj = new Polish_Converter("1*+b");
	p_obj->Convert_To_Polish();
	cout << *p_obj;

}
