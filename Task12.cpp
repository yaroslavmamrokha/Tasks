#include<iostream>
#include<type_traits>
#include<valarray>

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
protected:
	void Set_Rows(int);
	void Set_Columns(int);
	void Set_Size();
	void Resize_Matrix();
	bool isbadinput(istream&);
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
	Matrix operator*(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator+=(const T&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator-=(const T&);
	Matrix& operator*=(const T&);
	
	template<typename T>
	friend ostream& operator<<(ostream&, const Matrix<T>&);
	template<typename T>
	friend istream& operator>>(istream&, Matrix<T>&);
	template<typename T>
	friend Matrix<T> operator+(const T&, const Matrix<T>&);
	template<typename T>
	friend Matrix<T> operator-(const T&, const Matrix<T>&);
	template<typename T>
	friend Matrix<T> operator*(const T&, const Matrix<T>&);
	
	
	~Matrix();
};




/*
*@[brief]: Function check if istream object state is set to failbit, shows error and fix input stream;
*@[in]: istream object needed for fail check;
*@[out]: bool statement that shows function result, true if failbit enabled and false otherwise;
*/
template<typename T>
bool Matrix<T>::isbadinput(istream& in) {
	if (in.fail()) {
		in.clear();
		in.ignore();
		cout << "Bad input, istream fixed, re-enter pls\n";
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
	obj.Resize_Matrix();
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
	Set_Rows(row);
	Set_Columns(column);
	Resize_Matrix();
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
*@[brief]: friend overloaded operator + for addition number to matrix;
*@[in]: const reference to number;
*@[out]: matrix with added numbers
*/
template<typename T>
Matrix<T> operator+(const T & obj1, const Matrix<T> & obj2)
{
	Matrix<T> obj3{ obj2 };
	obj3 += obj1;
	return obj3;
}
/*
*@[brief]: friend overloaded operator - for addition number to matrix;
*@[in]: const reference to number;
*@[out]: matrix with added numbers
*/
template<typename T>
Matrix<T> operator-(const T & obj1, const Matrix<T> & obj2)
{
	Matrix<T> obj3{ obj2 };
	obj3 _= obj1;
	return obj3;
}
/*
*@[brief]: friend overloaded operator * for addition number to matrix;
*@[in]: const reference to number;
*@[out]: matrix with added numbers
*/
template<typename T>
Matrix<T> operator*(const T & obj1, const Matrix<T> & obj2)
{
	Matrix<T> obj3{ obj2 };
	obj3 *= obj1;
	return obj3;
}

/*
*@[brief]: overloaded operator + for addition matrix to number;
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
	Matrix tmp = *this;
	tmp.matx -= obj.matx;
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

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix & mat2)
{
	Matrix tmp = *this;
	if (tmp.columns != mat2.rows) {
		cout << "Bad matrix sizes!!!!\n";
		exit(true);
	}
	Matrix res_mat;
	res_mat.Set_Rows(tmp.rows);
	res_mat.Set_Columns(mat2.columns);
	res_mat.Resize_Matrix();
	int sum = 0;
	int next = 0;
	int brk = 0;
	int jrl = 0;
	for (int k = 0; k < tmp.rows; k++) {
		for (int p = 0; p < mat2.columns; p++) {
		for (int i = jrl, j = brk++, iter = 0; iter < tmp.columns; i++, iter++, j = j + mat2.columns) {
			sum = sum + tmp.matx[i] * mat2.matx[j];
		}
	
		res_mat.matx[next++] = sum;
		sum = 0;
	}
		jrl += tmp.columns;	
		brk = 0;
		sum = 0;
		
	}
	return res_mat;
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
	this->matx *= obj;
	return *this;
}
/*
*@[brief]: Function set value of private data 'rows'
*@[in]: integer value of rows
*/
template<typename T>
void Matrix<T>::Set_Rows(int r_tmp)
{
	if (r_tmp < 0) {
		cout << "Error: Negative rows value!\n";
		exit(1);
	}
	rows = r_tmp;
}
/*
*@[brief]: Function set value of private data 'columns'
*@[in]: integer value of columns
*/
template<typename T>
void Matrix<T>::Set_Columns(int c_tmp)
{
	if (c_tmp < 0) {
		cout << "Error: Negative columns value!\n";
		exit(1);
	}
	columns = c_tmp;
}
/*
*@[brief]: function calculates size for given rows and columns
*/
template<typename T>
void Matrix<T>::Set_Size()
{
	size = rows*columns;
}
/*
*@[brief]: Function resizes data array using size  calculated from rows and columns ,multiplication
*/
template<typename T>
void Matrix<T>::Resize_Matrix()
{
	Set_Size();
	matx.resize(size);
	matx *= 0;
	matx += TRASH_IN;
}

template<typename T>
Matrix<T>::~Matrix()
{
	Set_Columns(0);
	Resize_Matrix();
}



void main() {
	cout << "First matrix: \n";
	Matrix<int> a(1,2);
	cout << "Second matrix: \n";
	Matrix<int> b(2,1);
	Matrix<int>c = a*b;
	cout << "\n" << c;
	
}
