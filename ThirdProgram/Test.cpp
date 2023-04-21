#include "Test.h"


bool ErrorHandler() {
	try {
        TestingBubbleSort();
        TestingSelectionSort();
		TestingInsertionSort();
        TestingShellSort();
        TestingQuickSort();
	}
	catch(const int& numOfFailedTest){
        switch (numOfFailedTest){
        case(1):
            cout << "Test of bubble sort is Failed" << endl;
            break;
        case(2):
            cout << "Test of selection sort is Failed" << endl;
            break;
        case(3):
            cout << "Test of insertion sort is Failed" << endl;
            break;
        case(4):
            cout << "Test of shell sort is Failed" << endl;
            break;
        case(5):
            cout << "Test of quick sort is Failed" << endl;
            break;
        default:
            cout << "Undefined error" << endl;
            break;
        }

		return true;
	}
    return false;
}

bool TestingBubbleSort() {
    BubbleSort<definedType> function;

    vector<vector<definedType>> arrOrig;
    vector<vector<definedType>> arrSort1;
    vector<vector<definedType>> arrSort2;
    vector<definedType> subArr;

    for (auto i = 0; i < mForTest; ++i) {
        subArr.resize(nForTest);
        generate(subArr.begin(), subArr.end(), []() -> definedType {return(rand() % 1000 / 10. - 50); });
        arrOrig.push_back(subArr);
        subArr.clear();
    }

    arrSort1 = arrOrig;
    for (auto i = 0; i < arrSort1.size(); ++i) {
        function.Sort(arrSort1[i]);
    }

    arrSort2 = arrOrig;
    for (auto i = 0; i < arrSort2.size(); ++i) {
        sort(arrSort2[i].begin(), arrSort2[i].end());
    }

    if (arrSort1 == arrSort2) {
        return true;
    }
    else {
        throw (1);
    }
}
bool TestingSelectionSort() {
    SelectionSort<definedType> function;

    vector<vector<definedType>> arrOrig;
    vector<vector<definedType>> arrSort1;
    vector<vector<definedType>> arrSort2;
    vector<definedType> subArr;

    for (auto i = 0; i < mForTest; ++i) {
        subArr.resize(nForTest);
        generate(subArr.begin(), subArr.end(), []() -> definedType {return(rand() % 1000 / 10. - 50); });
        arrOrig.push_back(subArr);
        subArr.clear();
    }

    arrSort1 = arrOrig;
    for (auto i = 0; i < arrSort1.size(); ++i) {
        function.Sort(arrSort1[i]);
    }

    arrSort2 = arrOrig;
    for (auto i = 0; i < arrSort2.size(); ++i) {
        sort(arrSort2[i].begin(), arrSort2[i].end());
    }

    if (arrSort1 == arrSort2) {
        return true;
    }
    else {
        throw (2);
    }
}
bool TestingInsertionSort() {
    InsertionSort<definedType> function;

    vector<vector<definedType>> arrOrig;
    vector<vector<definedType>> arrSort1;
    vector<vector<definedType>> arrSort2;
    vector<definedType> subArr;

    for (auto i = 0; i < mForTest; ++i) {
        subArr.resize(nForTest);
        generate(subArr.begin(), subArr.end(), []() -> definedType {return(rand() % 1000 / 10. - 50); });
        arrOrig.push_back(subArr);
        subArr.clear();
    }

    arrSort1 = arrOrig;
    for (auto i = 0; i < arrSort1.size(); ++i) {
        function.Sort(arrSort1[i]);
    }

    arrSort2 = arrOrig;
    for (auto i = 0; i < arrSort2.size(); ++i) {
        sort(arrSort2[i].begin(), arrSort2[i].end());
    }

    if (arrSort1 == arrSort2) {
        return true;
    }
    else {
        throw (3);
    }
}
bool TestingShellSort() {
    ShellSort<definedType> function;

    vector<vector<definedType>> arrOrig;
    vector<vector<definedType>> arrSort1;
    vector<vector<definedType>> arrSort2;
    vector<definedType> subArr;

    for (auto i = 0; i < mForTest; ++i) {
        subArr.resize(nForTest);
        generate(subArr.begin(), subArr.end(), []() -> definedType {return(rand() % 1000 / 10. - 50); });
        arrOrig.push_back(subArr);
        subArr.clear();
    }

    arrSort1 = arrOrig;
    for (auto i = 0; i < arrSort1.size(); ++i) {
        function.Sort(arrSort1[i]);
    }

    arrSort2 = arrOrig;
    for (auto i = 0; i < arrSort2.size(); ++i) {
        sort(arrSort2[i].begin(), arrSort2[i].end());
    }

    if (arrSort1 == arrSort2) {
        return true;
    }
    else {
        throw (4);
    }
}  
bool TestingQuickSort() {
    QuickSort<definedType> function;

    vector<vector<definedType>> arrOrig;
    vector<vector<definedType>> arrSort1;
    vector<vector<definedType>> arrSort2;
    vector<definedType> subArr;

    for (auto i = 0; i < mForTest; ++i) {
        subArr.resize(nForTest);
        generate(subArr.begin(), subArr.end(), []() -> definedType {return(rand() % 1000 / 10. - 50); });
        arrOrig.push_back(subArr);
        subArr.clear();
    }

    arrSort1 = arrOrig;
    for (auto i = 0; i < arrSort1.size(); ++i) {
        function.Sort(arrSort1[i]);
    }

    arrSort2 = arrOrig;
    for (auto i = 0; i < arrSort2.size(); ++i) {
        sort(arrSort2[i].begin(), arrSort2[i].end());
    }

    if (arrSort1 == arrSort2) {
        return true;
    }
    else {
        throw (5);
    }
}
