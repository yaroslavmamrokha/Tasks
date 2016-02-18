#include<vector>
#include<iostream>
#include<valarray>
#include<string>
#include<type_traits>
#include<exception>
using namespace std;


/*
Class should take temperature array, or single temperature, methods for converting to fahrenheit,
celsii and Kelvin, arithmetic operations on them, and evaluatin of min/max temp for arrays,
Check for range specification, more info https://en.wikipedia.org/wiki/Operating_temperature
*/
template <typename T>
class Temperature {
#define KELVIN -1
#define CELSIUS 0
#define FAHRENHEIT 1
#define COMMERCIAL -100
#define MILITARY -101
#define INDUSTRIAL -102
#define AUTOMOTIVE -103
#define EXTENDED -104

	static_assert(is_arithmetic<T>::value, "Non-arithmetic type in temperature class!");
private:
	enum class Ranges_Celsius : int {
		lower_military = -55,
		lower_intdustrial = -40,
		lower_automotive = -40,
		lower_extended = -40,
		lower_commercial = 0,
		upper_commercial  = 85,
		upper_military = 125,
		upper_industrial = 100,
		upper_automotive = 125,
		upper_exetended = 125
	};
	enum class Ranges_Index : int {
		commercial =0,
		military,
		industrial,
		extended,
		automotive,
		not_in_range
	};
	vector<string> ranges_names{ "commercial","military","industrial","extended","automotive","not in range" };
	string def_spec;
	valarray<T> temp;
	bool is_kelvin{ false };
	bool is_celsius{ false };
	bool is_fahrenheit{ false };
	void append_range(string&, string);
	bool is_range(Temperature, int = COMMERCIAL);
	void set_flags_zero();
public:
	Temperature() = default;
	Temperature(valarray<T>, int = 0);
	Temperature(T, int = 0);
	Temperature(const Temperature&) = default;
	Temperature& operator=(const Temperature&) = default;
	Temperature(Temperature&&) = default;
	Temperature& operator=(Temperature&&) = default;
	virtual ~Temperature();


	Temperature to_Celsius(); //not implemented
	Temperature to_Kelvin();//not implemented
	Temperature to_Fahrenheit();//not implemented
	string in_what_range();
	Temperature min_temp();//not implemented
	Temperature max_temp();//not implemented

	Temperature operator+(const Temperature&);//not implemented
	Temperature operator-(const Temperature&);//not implemented
	Temperature operator*(const Temperature&);//not implemented
	Temperature operator/(const Temperature&);//not implemented
	Temperature& operator+=(const Temperature&);//not implemented
	Temperature& operator-=(const Temperature&);//not implemented
	Temperature& operator*=(const Temperature&);//not implemented
	Temperature& operator/=(const Temperature&);//not implemented

	template <typename T>
	friend ostream& operator<<(ostream&, const Temperature<T>&);
	template <typename T>
	friend istream& operator>>(istream&, const Temperature&); //not implemented
};

/*
*@[brief]: helper function append  range name depending on if it's first append or not
*@[in]: reference to appending string and range name
*/

template <typename T>
void Temperature<T>::append_range(string& range_var, string range) {
	if (range.empty()) {
		//throw Temperature exception class;
	}
	if (range_var.empty()) {
		range_var.append(range);
	}
	else {
		range_var.append(" ");
		range_var.append(range);
	}
}

/*
*@[brief]: function check for all possible ranges and add them to string
*@[out]: string with ranges in what is out temperature
*/


template <typename T>
string Temperature<T>::in_what_range() {
	Temperature<T> tmp;
	string range;
	if (!is_celsius) {
		//tmp = to_Celsius();
	}
	tmp = *this;
	Ranges_Index id;
	int index{ 0 };
	try {
		if (is_range(tmp, COMMERCIAL)) {
			id = Ranges_Index::commercial;
			index = static_cast<int>(id);
			append_range(range, ranges_names.at(index));
		}
		if (is_range(tmp, MILITARY)) {
			id = Ranges_Index::military;
			index = static_cast<int>(id);
			append_range(range, ranges_names.at(index));
		}
		if (is_range(tmp, INDUSTRIAL)) {
			id = Ranges_Index::industrial;
			index = static_cast<int>(id);
			append_range(range, ranges_names.at(index));
		}
		if (is_range(tmp, EXTENDED)) {
			id = Ranges_Index::extended;
			index = static_cast<int>(id);
			append_range(range, ranges_names.at(index));
		}
		if (is_range(tmp, AUTOMOTIVE)) {
			id = Ranges_Index::automotive;
			index = static_cast<int>(id);
			append_range(range, ranges_names.at(index));
		}
		if (range.empty()) {
			id = Ranges_Index::not_in_range;
			index = static_cast<int>(id);
			append_range(range, ranges_names.at(index));
		}
		return range;
	}
	catch (exception& ex) {
		cerr << "We got exception here: " << ex.what() << ". Closing program\n";
		exit(true);
	}
}

/*
*@[brief]: function check if temperature is in given range, if no range given default(commercial) is used
*@[in]: Temperature object that holds temperature, int range type
*@[out]: true if in range else false
*/
template<typename T>
bool Temperature<T>::is_range(Temperature<T> obj, int range_type) {
	if (obj.temp.size() > 1 || obj.temp.size() == 0) {
		//throw Temperature exception class;
	}
	Ranges_Celsius low_range;
	Ranges_Celsius up_range;
	auto temper = obj.temp[0];
	switch (range_type) {
	case COMMERCIAL:
		low_range = Ranges_Celsius::lower_commercial;
		up_range = Ranges_Celsius::upper_commercial;
		break;
	case MILITARY:
		low_range = Ranges_Celsius::lower_military;
		up_range = Ranges_Celsius::upper_military;
		break;
	case INDUSTRIAL:
		low_range = Ranges_Celsius::lower_intdustrial;
		up_range = Ranges_Celsius::upper_industrial;
		break;
	case EXTENDED:
		low_range = Ranges_Celsius::lower_extended;
		up_range = Ranges_Celsius::upper_exetended;
		break;
	case AUTOMOTIVE:
		low_range = Ranges_Celsius::lower_automotive;
		up_range = Ranges_Celsius::upper_automotive;
		break;
	default:
		cout << "Bad range type, setting to default(commercial)\n";
		low_range = Ranges_Celsius::lower_commercial;
		up_range = Ranges_Celsius::upper_commercial;
		break;
	}
	auto up_bound = static_cast<int>(up_range);
	auto low_bound = static_cast<int>(low_range);
	if (temper<low_bound || temper>up_bound)
		return false;
	return true;
}


/*
*@[brief]: overloaded input operator for class Temperature
*@[in]: istream object for input, const class object for buffer
*@[out]: istream object for chain input
*/
template <typename T>
istream& operator>>(istream& is, const Temperature<T>& temper) {
	return is;
}

/*
*@[brief]: overloaded output operator for class Temperature
*@[in]: ostream object for output, const class object for data
*@[out]: ostream object for chain output
*/
template <typename T>
ostream& operator<<(ostream& os, const Temperature<T>&temper) {
	for (const auto x : temper.temp) {
		os << x << temper.def_spec << " ";
	}
	return os;
}





/*
*@[brief]: Set flags that indicate current temperature type to false(zero)
*/
template<typename T>
void Temperature<T>::set_flags_zero() {
	is_celsius = false;
	is_fahrenheit = false;
	is_kelvin = false;
}


/*
*@[brief]: Constructor with parametrs with default celsius type
*@[in]: valarray<T> - array of temperatures, int - temperature type (-1 - kelvin, 0 - celsius(default), 1 - fahrenheit
*/
template<typename T>
Temperature<T>::Temperature(valarray<T> temp_arr, int type = 0)
{
	set_flags_zero();
	switch (type) {
	case -1:
		is_kelvin = true;
		def_spec = "^K";
		break;
	case 0:
		is_celsius = true;
		def_spec = "^C";
		break;
	case 1:
		is_fahrenheit = true;
		def_spec = "^F";
		break;
	default:
		cout << "Bad temp type, setting default type (celsius)\n";
		type = 0;
		break;
	}
	temp = temp_arr;
}
/*
*@[brief]: Constructor with parametrs with default celsius type
*@[in]: valarray<T> - array of temperatures, int - temperature type (-1 - kelvin, 0 - celsius(default), 1 - fahrenheit
*/
template<typename T>
Temperature<T>::Temperature(T temp_arg, int type)
{
	set_flags_zero();
	switch (type) {
	case -1:
		is_kelvin = true;
		def_spec = "^K";
			break;
	case 0:
		is_celsius = true;
		def_spec = "^C";
		break;
	case 1:
		is_fahrenheit = true;
		def_spec = "^F";
		break;
	default:
		cout << "Bad temp type, setting default type (celsius)\n";
		type = 0;
		break;
	}
	temp *= 0;
	temp.resize(1);
	temp[0] = temp_arg;
}
template<typename T>
Temperature<T>::~Temperature() {
	set_flags_zero();
	temp *= 0;
	temp.resize(0);
}

void main() {
	Temperature<int> obj(-56);
	cout << obj.in_what_range()<<"\n";
}
