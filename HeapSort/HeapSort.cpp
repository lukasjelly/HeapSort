#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<int> vector_random;
vector<int> vector_reversed;
vector<int> vector_sorted;


void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

class Heap {
private:
	vector<int> data;
	int last;
	int insertComparisons;
	int deleteComparisons;
public:
	Heap();
	~Heap() {}
	void InsertHeap(int newthing);
	int Delete();
	void PrintHeapArray();
	int InsertComparisons() { return insertComparisons; }
	int DeleteComparisons() { return deleteComparisons; }
};

Heap::Heap() {
	last = -1;
	insertComparisons = 0;
	deleteComparisons = 0;
}

void Heap::InsertHeap(int newthing) {
	data.push_back(newthing);
	data[last + 1] = newthing; //add new element to the last index in array
	last = last + 1; //update to reflect new insertion
	if (last == 0) { return; } //only 1 element in the heap
	int childIndex = last;
	int parentIndex = 0;
	bool swapping = true;
	while (swapping) { //fix heap to maintain correct topography: largest element in the root
		swapping = false;
		if (childIndex % 2 == 0) { parentIndex = childIndex / 2 - 1; } //parent is to the right
		else parentIndex = childIndex / 2; //parent is to the left
		if (parentIndex >= 0) { //parent is not root of tree
			insertComparisons++;
			if (data[childIndex] > data[parentIndex]) { //if data in child index is greater than data in parent index, need to swap
				swap(data[childIndex], data[parentIndex]);
				swapping = true; //repeat loop to test heap again
				childIndex = parentIndex; //child is now the parent index
			}
		}
	}
}

int Heap::Delete() {
	int deletedValue = data[0];
	data[0] = data[last];
	data[last] = -1;
	last = last - 1;
	//printf("\n");
	//PrintHeapArray();
	int parindex = 0;
	int leftindex = parindex * 2 + 1;//left child
	int rightindex = parindex * 2 + 2;//right child
	bool swapping = true;
	if (data[parindex] > data[leftindex] && data[parindex] > data[rightindex] && last > 0) { //heap is already heapified and there is at least 1 child
		if (rightindex <= last) { //right child exists, 2 comparisons
			deleteComparisons = deleteComparisons + 2;
			//printf("comparison + 2\n");
		}
		else {//only left child
			deleteComparisons++;
			//printf("comparison + 1\n");
		}
	}
	while ((data[parindex] < data[leftindex] || data[parindex] < data[rightindex]) && swapping == true) {
		swapping = false;
		if (data[rightindex] < data[leftindex]) {//follow left whcih is bigger
			swap(data[leftindex], data[parindex]);
			parindex = leftindex;
			swapping = true;
		}
		else {//else follow right
			swap(data[rightindex], data[parindex]);
			parindex = rightindex;
			swapping = true;
		}

		if (rightindex <= last) { //right child exists, 2 comparisons
			deleteComparisons = deleteComparisons + 2;
			//printf("comparison + 2\n");
		}
		else {//only left child
			deleteComparisons++;
			//printf("comparison + 1\n");
		}

		leftindex = parindex * 2 + 1;
		rightindex = parindex * 2 + 2;


		if (leftindex > last) break;
		else {

			if (rightindex > last) {
				deleteComparisons++;
				//printf("comparison + 1\n");
				if (data[parindex] < data[leftindex]) swap(data[parindex], data[leftindex]);
				break;
			}
		}
	}

	if (rightindex <= last) {
		if (data[parindex] > data[leftindex] && data[parindex] > data[rightindex] && last > 0) { //heap is already heapified and there is at least 1 child
			if (rightindex <= last) { //right child exists, 2 comparisons
				deleteComparisons = deleteComparisons + 2;
				//printf("comparison + 2\n");
			}
			else {//only left child
				deleteComparisons++;
				//printf("comparison + 1\n");
			}
		}
	}


	//printf("Comparisons=%d\n", deleteComparisons);
	//PrintHeapArray();
	return deletedValue;
}


void Heap::PrintHeapArray() {
	for (int i = 0; i <= last; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}


void heapsort(vector<int>& sortingvector, int number_of_elements, char* filename) {
	Heap myHeap;

	for (int i = 0; i < number_of_elements; i++) {
		myHeap.InsertHeap(sortingvector[i]);
	}

	printf("Heap before sorting: %s\n", filename);
	myHeap.PrintHeapArray();

	printf("InsertHeap: %d comparisons\n", myHeap.InsertComparisons());

	for (int i = number_of_elements - 1; i >= 0; i--) {
		sortingvector[i] = myHeap.Delete();
	}

	printf("DeleteRoot: %d comparisons\n", myHeap.DeleteComparisons());

	printf("Vector after sorting:\n");
	for (int i = 0; i < number_of_elements; i++) {
		printf("%d ", sortingvector[i]);
	}
	printf("\n");
}




int main(int argc, char** argv) {//get filename from arguments
	char expression[100];
	int number;
	ifstream input_file_random;
	ifstream input_file_reversed;
	ifstream input_file_sorted;
	if (argc == 4) {
		input_file_random.open(argv[1]);
		input_file_reversed.open(argv[2]);
		input_file_sorted.open(argv[3]);
	}
	else { printf("The program needs 3 filenames, in this order: random, reversed and sorted.\n"); exit(0); }
	int number_of_elements_random = 0;
	while (input_file_random >> number) {
		sscanf(expression, "%d", &number);
		/*Comment out this printout, this is just to check that the file can be read */
		//printf("%d ",number );	
		vector_random.push_back(number);
		number_of_elements_random++;
	}
	/*Comment out this printout, this is just to check that the array was copied */
	//printf("File %s:\n", argv[1]);
	for (int count = 0; count < number_of_elements_random; count++) {
		//printf("%d ", vector_random[count]);
	}
	//printf("\n");
	/*end printout*/

	int number_of_elements_reversed = 0;
	while (input_file_reversed >> number) {
		sscanf(expression, "%d", &number);
		/*Comment out this printout, this is just to check that the file can be read */
//		printf("%d ",number );	
		vector_reversed.push_back(number);
		number_of_elements_reversed++;
	}
	/*Comment out this printout, this is just to check that the array was copied */
	//printf("File %s:\n", argv[2]);
	for (int count = 0; count < number_of_elements_reversed; count++) {
		//printf("%d ", vector_reversed[count]);
	}
	//printf("\n");
	/*end printout*/


	int number_of_elements_sorted = 0;
	while (input_file_sorted >> number) {
		sscanf(expression, "%d", &number);
		/*Comment out this printout, this is just to check that the file can be read */
//		printf("%d ",number );	
		vector_sorted.push_back(number);
		number_of_elements_sorted++;
	}
	/*Comment out this printout, this is just to check that the array was copied */
	//printf("File %s:\n", argv[3]);
	for (int count = 0; count < number_of_elements_sorted; count++) {
		//printf("%d ", vector_sorted[count]);
	}
	//printf("\n\n");
	/*end printout*/


	/* Implement or call your Heap sort here, the Heap class with methods should be copied/implemented before main() */
	heapsort(vector_random, number_of_elements_random, argv[1]);
	cout << endl;
	heapsort(vector_reversed, number_of_elements_reversed, argv[2]);
	cout << endl;
	heapsort(vector_sorted, number_of_elements_sorted, argv[3]);

}
