#include <iostream>
#include<memory>
#include <algorithm>
#include <functional>
using namespace std;

enum array_nums {
	first_element = 0,
	next_element,
	array_size = 10,
	biggest,
	lowest
};

 int Find_Num(int* user_array, int array_size,  const int op_type = array_nums::biggest) {
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
		exit(1);
	}
	return position;

}

void main() {
	int* arr = new int[array_nums::array_size];
	int* arr_copy = new int[array_nums::array_size];
	int* arr_numeric = new int[array_nums::array_size];
	int biggest_pancake_eater = 0;
	int lowest_pancake_eater = 0;

	memset(arr, -1, array_nums::array_size);
	memset(arr_copy, -1, array_nums::array_size);
	memset(arr_numeric, -1, array_nums::array_size);

	cout << "Enter cakes count for each person\n";

	for (int i = array_nums::first_element; i < array_nums::array_size; i++) {
		cout << i + 1 << ") Person ate: ";
		cin >> arr[i];
	}
	for (int i = 0; i < array_nums::array_size; i++) {
		arr_copy[i] = arr[i];
	}
	biggest_pancake_eater = Find_Num(arr, array_nums::array_size);
	lowest_pancake_eater = Find_Num(arr, array_nums::array_size, array_nums::lowest);
	sort(arr, arr + array_nums::array_size, greater<int>());
	bool next = false;
	system("cls");
	cout << "List of pancake eaters!!!!: \n";
	for (int i = 0; i < array_nums::array_size; i++) {
		for (int j = 0; j < array_nums::array_size; j++) {
			if (arr[i] == arr_copy[j]) {
				for (int p = 0; p < array_nums::array_size; p++) {
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
				cout << j+1 << ") Person ate: " << arr[i] << " cakes!!\n";
				break;
			}

		}
	}
	cout << "\n Best and worse pancake eater!!\n";
	cout << biggest_pancake_eater + 1 << ") Person ate most of cakes: " << arr_copy[biggest_pancake_eater] << " !!!\n";
	cout << lowest_pancake_eater + 1 << ") Person ate less of cakes: " << arr_copy[lowest_pancake_eater] << " !!!\n";
	
	memset(arr, -1, array_nums::array_size);
	memset(arr_copy, -1, array_nums::array_size);
	memset(arr_numeric, -1, array_nums::array_size);

	delete[]arr;
	delete[]arr_copy;
	delete[]arr_numeric;
}
