#include<iostream>
#include<vector>
#include<type_traits>
#include<valarray>
#include<cassert>
#define TRASH_IN -1

using namespace std;
template<typename T>
class Matrix {
private:
	static_assert(is_arithmetic<T>::value, "Non arithmetic class");
	valarray<T> matx;
	int columns;
	int rows;
	int size;
public:
	Matrix() = default;
	Matrix(const Matrix&) = default;
	Matrix& operator=(const Matrix&) = default;
	Matrix(Matrix&&) = default;
	Matrix& operator=(Matrix&&) = default;
	Matrix(int, int);
	Matrix operator+(const Matrix&);
	Matrix operator+(const T&);
	Matrix operator-(const Matrix&);
	Matrix operator-(const T&);
	Matrix operator*(const T&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator+=(const T&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator-=(const T&);
	Matrix& operator*=(const T&);
	~Matrix();
	template<typename T>
	friend ostream& operator<<(ostream&, const Matrix<T>&);
	template<typename T>
	friend istream& operator>>(istream&, Matrix<T>&);
};


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

/*
*@[brief]: overloaded output operator for class Matrix
*@[in]: ostream object for output and const Matrix reference
*@[out]: ostream object for chain output
*/
template<typename T>
ostream & operator<<(ostream & os, const Matrix<T> & obj)
{
	int  i = 0;
	for (auto x : obj.matx) {
		cout << x << " ";
		i++;
		if (i == obj.columns) {
			cout << "\n";
			i = 0;
		}
	}
	return os;
}
/*
*@[brief]: overloaded input operator for class Matrix
*@[in]: istream object for input and  Matrix reference
*@[out]: istream object for chain input
*/
template<typename T>
istream & operator>>(istream & is, Matrix<T>& obj)
{
	bool bad_size = true;
	while (bad_size) {
		cout << "Enter rows and columns: ";
		is >> obj.rows >> obj.columns;
		bad_size = isbadinput(is);
	}
	obj.size = obj.columns*obj.rows;
	obj.matx.resize(obj.size);
	obj.matx *= 0;
	obj.matx += TRASH_IN;
	cout << "Enter elements: \n";
	for (int i = 0; i < obj.size; i++) {
		is >> obj.matx[i];
		if (isbadinput(is)) {
			i--;
			continue;
		}
	}
	return is;
}

/*
*@[brief]: Constructor that takes rows and columns and waits for element input
*@[in]: Rows and columns;
*/
template<typename T>
Matrix<T>::Matrix(int row, int column){
	bool tmp1 = (row < 0) ? false : true;
	bool tmp2 = (column < 0) ? false : true;
	if (!(tmp1 | tmp2)) {
		cout << "Error negative numbers!!!\n";
		abort();
	}
	rows = row;
	columns = column;
	size = row*column;
	matx.resize(size);
	matx *= 0;
	matx += TRASH_IN;
	cout << "Enter elements: \n";
	for (int i = 0; i < size; i++) {
		cin >> matx[i];
		if (isbadinput(cin)) {
			i--;
		}
	}
}

/*
*@[brief]: overloaded operator + for addition of two Matrix;
*@[in]: const reference to second object;
*@[out]: sum of two object
*/
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix & obj)
{
	Matrix tmp;
	tmp.columns = this->columns;
	tmp.rows = this->rows;
	tmp.size = this->size;
	tmp.matx *= 0;
	tmp.matx += TRASH_IN;
	tmp.matx = this->matx + obj.matx;
	return tmp;
}

/*
*@[brief]: overloaded operator + for addition number to matrix;
*@[in]: const reference to number;
*@[out]: matrix with added numbers
*/
template<typename T>
Matrix<T> Matrix<T>::operator+(const T & obj)
{
	Matrix tmp = *this;
	tmp.matx += obj;
	return tmp;
}

/*
*@[brief]: overloaded operator - for sub of two Matrix;
*@[in]: const reference to second object;
*@[out]: diff of two object
*/
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix & obj)
{
	Matrix tmp;
	tmp.columns = this->columns;
	tmp.rows = this->rows;
	tmp.size = this->size;
	tmp.matx = this->matx - obj.matx;
	return tmp;
}

/*
*@[brief]: overloaded operator - for sub number from matrix;
*@[in]: const reference to number;
*@[out]: matrix with subbed numbers
*/
template<typename T>
Matrix<T> Matrix<T>::operator-(const T & obj)
{
	Matrix tmp = *this;
	tmp.matx -= obj;
	return tmp;
}

/*
*@[brief]: overloaded operator * for mul number to matrix;
*@[in]: const reference to number;
*@[out]: matrix with mulled numbers
*/
template<typename T>
Matrix<T> Matrix<T>::operator*(const T & obj)
{
	Matrix tmp = *this;
	tmp.matx *= obj;
	return tmp;
}




/*
*@[brief]: overloaded operator += for addition of two Matrix;
*@[in]: const reference to second object;
*@[out]: added object
*/
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix & obj)
{
	this->matx += obj.matx;
	return *this;
}

/*
*@[brief]: overloaded operator += for addition number to matrix;
*@[in]: const reference to number;
*@[out]: added object
*/
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const T & obj)
{
	this->matx += obj;
	return *this;
}

/*
*@[brief]: overloaded operator -= for sub of two Matrix;
*@[in]: const reference to second object;
*@[out]: subbed object
*/
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix & obj)
{
	this->matx -= obj.matx;
	return *this;
}

/*
*@[brief]: overloaded operator - for sub number from matrix;
*@[in]: const reference to number;
*@[out]: subbed object
*/
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const T & obj)
{
	this->matx -= obj;
	return *this;
}

/*
*@[brief]: overloaded operator *= for mul number to matrix;
*@[in]: const reference to number;
*@[out]: mulled object
*/
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T & obj)
{
	this->matx *= obj.matx;
	return *this;
}

template<typename T>
Matrix<T>::~Matrix()
{
	matx *= 0;
	matx += TRASH_IN;
	matx.resize(0);
	rows = TRASH_IN;
	columns = TRASH_IN;
	size = TRASH_IN;
}

void main() {
	cout << "First matrix: \n";
	Matrix<int> a(3,3);
	cout << "Second matrix: \n";
	Matrix<int> b(3,3);
	a += b;
	cout << "Summ of 2 matrix!: \n";
	cout << a;
}
