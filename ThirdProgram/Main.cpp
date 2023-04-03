#include "Classes.h"

int main() {
	srand(time(NULL));

	vector <double> arr;

	//BubbleSort<double> s;
	//SelectionSort<double> s;
	//InsertionSort<double> s;
	//ShellSort<double> s;
	QuickSort<double> s;

	for (int i = 0; i < 11; ++i ) {
		arr.push_back(rand()%100/10.);
	}

	s.Info();
	cout << "==========================" << endl;
	for (auto i = 0; i < arr.size(); ++i) {
		cout << arr[i] << endl;
	}
	cout << "==========================" << endl;
	s.Sort(arr);
	
	for (auto i = 0; i < arr.size(); ++i) {
		cout << arr[i] << endl;
	}
	cout << "==========================" << endl;
	s.Info();

	return 0; 
}