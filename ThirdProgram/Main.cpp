#include "Classes.h"

int main() {

	vector <double> s{ 6.23, 2.23, 2.01 }; //3,4,8,9,1,5

	BubbleSort<double> sorting;

	sorting.Info();
	cout << "==========================" << endl;
	for (auto i = 0; i < s.size(); ++i) {
		cout << s[i] << endl;
	}
	cout << "==========================" << endl;
	sorting.Sort(s);
	
	for (auto i = 0; i < s.size(); ++i) {
		cout << s[i] << endl;
	}
	cout << "==========================" << endl;
	sorting.Info();

	return 0; 
}