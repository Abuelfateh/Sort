#include <iostream>
using namespace std;

int arr_size;

// display array content
void display(int arr[]) {
	for (int i = 0; i < arr_size; i++)
		cout << (i == 0 ? "" : " ") << arr[i];
	cout << endl;
}

void BubbleSort(int arr[], int len) {
	int i, tmp;
	bool swap;
	// to be able to access the next element of the array, (the last element)
	len--;
	// in bubble sort we have to loop at least once on a sorted array,
	// so using do while is recomended for this case
	cout << "Bubble Sort steps: " << endl;
	do {
		swap = false;
		for (i = 0; i < len; i++) {
			if (arr[i] > arr[i + 1]) {
				swap = true;
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
		display(arr);
	} while (swap);
}

void SelectionSort(int arr[], int len) {
	int i, j, tmp,
		// used to hold the minimum value index, to perform one swap at a time
		index;
	cout << "Selection Sort steps: " << endl;
	for (i = 0; i < len; i++) {
		index = i;
		for (j = i + 1; j < len; j++) {
			if (arr[index] > arr[j])
				index = j;
		}
		// perform the swap only once if there exists a value less than the current value
		if (index != i) {
			tmp = arr[i];
			arr[i] = arr[index];
			arr[index] = tmp;
		}
		display(arr);
	}
}

void InsertionSort(int arr[], int len) {
	int i, j, tmp;
	cout << "Insertion Sort steps: " << endl;
	// start with i = 1 to be able to access the previous element (at position 0)
	// this implementation shifts all elements to the right to provide an empty cell at the position
	// needed to perform the swap, and in the outer loop it perform the swap,
	// it seems to be faster, as it perform only one assign operation in the inner loop instead of the
	// traditional swap (3 assign operation) as noted in 
	// https://en.wikipedia.org/wiki/Insertion_sort
	for (i = 1; i < len; i++) {
		tmp = arr[i];
		for (j = i - 1; j >= 0 && arr[j] > tmp; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = tmp;
		display(arr);
	}
}

// helper function to be used with merge sort to merge two halfs of the array
void _msMerge(int arr[], int l, int m, int r) {
	int i, j, k,
		*L, *R,
		lLen = m - l + 1,
		rLen = r - m;
	// create Left and Right temporary arrays
	L = new int[lLen];
	R = new int[rLen];
	// copy the data from the original array to the new arrays
	for (i = 0; i < lLen; i++)
		L[i] = arr[l + i];
	// here we add one as the middle position is part of the left array
	for (j = 0; j < rLen; j++)
		R[j] = arr[m + j + 1];

	// set the control variables
	i = 0;
	j = 0;
	k = l; // the l variable will refere to 0 in the original array (in first call)

	// first we will loop on both L & R
	while (i < lLen && j < rLen) {
		if (L[i] < R[j])
			arr[k++] = L[i++];
		else {
			arr[k++] = R[j++];
			// split_inversion += lLen - i;
		}
	}

	// check if there is a remaining elements in the left array
	while (i < lLen)
		arr[k++] = L[i++];

	// check remaining elements in the right array
	while (j < rLen)
		arr[k++] = R[j++];

	// clean up the reserved temporary arrays
	delete[] L;
	delete[] R;
}

// helper function to divide the array in merge sort
void _msDivide(int arr[], int l, int r) {
	if (l < r) {
		// calculate the middle position
		int m = (l + r) >> 1;
		// divide the left half recursively
		_msDivide(arr, l, m);
		// divide the right half recursively
		_msDivide(arr, m + 1, r);
		// merge the two halfs
		_msMerge(arr, l, m, r);
		display(arr);
	}
}

// this method is the main method to use merge sort
// it make the call of merge sort more convenient to the user
// as the user will just pass the array and its length
void MergeSort(int arr[], int len) {
	cout << "Merge Sort steps: " << endl;
	// passing the first position as (l) and the last position as (r)
	_msDivide(arr, 0, len - 1);
}

int main() {
	int fn = 0, *arr;


	do {
		system("cls");
		// get the array size and values from the user
		cout << "Please enter the size of the array: ";
		cin >> arr_size;
		arr = new int[arr_size];
		system("cls");
		cout << "Please enter the array values:" << endl;
		for (int i = 0; i < arr_size; i++)
			cin >> arr[i];

		system("cls");
		cout << "Unsorted array" << endl;
		display(arr);

		cout << "\nPlease select the sorting algorithm:\n"
			<< "\t1. Bubble Sort\n"
			<< "\t2. Selection Sort\n"
			<< "\t3. Insertion Sort\n"
			<< "\t4. Merge Sort\n\n"
			<< "any thing else to Quit ";

		cin >> fn;
		switch (fn) {
			case 1:
				BubbleSort(arr, arr_size);
				break;
			case 2:
				SelectionSort(arr, arr_size);
				break;
			case 3:
				InsertionSort(arr, arr_size);
				break;
			case 4:
				MergeSort(arr, arr_size);
				break;
			default:
				fn = 0;
				break;
		}

		if (fn) {
			cout << endl << "Sorted array" << endl;
			display(arr);
			fn = 0;
			cout << endl << endl << "Enter 1 to try another array: ";
			cin >> fn;
		}

		delete[] arr;
	} while (fn);


	cout << endl;
	system("pause");
	return 0;
}
