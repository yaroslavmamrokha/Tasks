#include <iostream>
#include<memory>
#include <algorithm>
#include <functional>
using namespace std;

enum array_nums {
	undef_input = -1,
	first_element = 0,
	next_element,
	array_size = 10,
	biggest,
	lowest
};


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

/*
*@[brief]: function sort pancake eaters in descending way, and print their position and value;
*@[in]: arr - pointer to original user array and it's copy aka arr_copy, arr_size - size of arr and arr_copy, must be equal!!
*/

void Print_Pancake_Eaters(int* arr, int* arr_copy, int arr_size) {
	bool next = false;
	if (!arr || !arr_copy) {
		cout << "Error: nullptr passed to Print_Pancake_Eaters!!\n";
		exit(true);
	}
	if (arr_size <= 0) {
		cout << "Invalid size! Size must be greater then 0!\n";
		exit(true);
	}
	int* arr_numeric = new int[arr_size];
	memset(arr_numeric, array_nums::undef_input, arr_size);
	
	cout << "List of pancake eaters!!!!: \n";
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			if (arr[i] == arr_copy[j]) {
				for (int p = 0; p < arr_size; p++) {
					if (arr_numeric[p] == j) {
						next = true;
						break;
					}
				}
				if (next) {
					next = false;
					continue;
				}
				arr_numeric[i] = j;
				cout << j + 1 << ") Person ate: " << arr[i] << " cakes!!\n";
				break;
			}

		}
	}
	memset(arr_numeric, array_nums::undef_input, arr_size);
	delete[]arr_numeric;
}

/*
*@[brief]:Function finds biggest by default, or lowest if chosen number in given array;
*@[in]: user array, with it's size and if needed explicit operation type;
*@[out]: position of needed element, or exit if incorrect operation type;
*/

 int Find_Num(int* user_array, int array_size,  const int op_type = array_nums::biggest) {
	 if (!user_array) {
		 cout << "Error: nullptr passed to Find_Num!!\n";
		 exit(true);
	 }
	 if (array_size <= 0) {
		 cout << "Invalid size! Size must be greater then 0!\n";
		 exit(true);
	 }
	int def_num = user_array[array_nums::first_element];
	int position = 0;
	if (op_type == array_nums::biggest) {
		for (int i = array_nums::next_element; i < array_size; i++) {
			if (user_array[i] > def_num) {
				def_num = user_array[i];
				position = i;
			}

		}
	}
	else if (op_type == array_nums::lowest) {
		for (int i = array_nums::next_element; i < array_size; i++) {
			if (user_array[i] < def_num) {
				def_num = user_array[i];
				position = i;
			}

		}
	}
	else {
		cout << "Bad operation type!!\n";
		exit(true);
	}
	return position;

}

void main() {
	int* arr = new int[array_nums::array_size];
	int* arr_copy = new int[array_nums::array_size];
	
	int biggest_pancake_eater = 0;
	int lowest_pancake_eater = 0;

	memset(arr, array_nums::undef_input, array_nums::array_size);
	memset(arr_copy, array_nums::undef_input, array_nums::array_size);
	
	cout << "Enter cakes count for each person\n";

	for (int i = array_nums::first_element; i < array_nums::array_size; i++) {
		cout << i + 1 << ") Person ate: ";
		cin >> arr[i];
		if (isbadinput(cin)) {
			i--; // if bad input simply try to re-enter number;
		}
	}
	for (int i = 0; i < array_nums::array_size; i++) {
		arr_copy[i] = arr[i];
	}
	biggest_pancake_eater = Find_Num(arr, array_nums::array_size);
	lowest_pancake_eater = Find_Num(arr, array_nums::array_size, array_nums::lowest);
	sort(arr, arr + array_nums::array_size, greater<int>());
	system("cls");
	Print_Pancake_Eaters(arr, arr_copy,-1);
	cout << "\n Best and worse pancake eater!!\n";
	cout << biggest_pancake_eater + 1 << ") Person ate most of cakes: " << arr_copy[biggest_pancake_eater] << " !!!\n";
	cout << lowest_pancake_eater + 1 << ") Person ate less of cakes: " << arr_copy[lowest_pancake_eater] << " !!!\n";
	
	memset(arr, array_nums::undef_input, array_nums::array_size);
	memset(arr_copy, array_nums::undef_input, array_nums::array_size);
	
	delete[]arr;
	delete[]arr_copy;
}
