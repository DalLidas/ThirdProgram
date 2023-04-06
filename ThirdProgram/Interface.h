#pragma once

#include "Classes.h"

template <typename T> bool IsInBetween(const T& num, const T& start, const T& end) {
    return start < num && num <= end;
}

void DrawBorder();
void DrawSubBorder();

int EnterSettingsTwo();
int EnterSettingThree();
string EnterFilePath();
template <typename T> T EnterNum() {
    T num = 0;
    cout << ": ";

    while (!(cin >> num)) {
        cin.clear();
        cin.ignore(INT32_MAX, '\n');
        cout << "Invalid input. Try again" << ": ";
    }

    return num;
}

void InputFromFile(vector<vector<definedType>>& arrOrig);

void InputFromConsole(vector<vector<definedType>>& arrOrig);

void InputRandom(vector<vector<definedType>>& arrOrig);

void CompareAll(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort);

void Compare(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort);

template <class sortFunction>
void SortHandler(vector<vector<definedType>>& subArrSort, bool flagFullInfo) {
    sortFunction function;

    int numOfCompares = 0;
    int numOfSwaps = 0;
    int executionTime = 0;

    DrawBorder();
    cout << endl;
    for (auto i = 0; i < subArrSort.size(); ++i) {
        function.Sort(subArrSort[i]);
        numOfCompares += function.GetNumOfCompares();
        numOfSwaps += function.GetNumOfOperations();
        executionTime += function.GetTime();
        if (flagFullInfo) {
            cout << "arr[" << i << "] { ";
            function.Info();
            cout << " }" << endl;
        }
    }

    cout << function .Name() << ": arr { Num of compares : " << numOfCompares << " || "
        << "Num of swaps: " << numOfSwaps << " || "
        << "Execution time: " << executionTime << " }" << endl;
}

void WriteOutputConsole(const vector<vector<definedType>>& arr);

void WriteOutputFile(const vector<vector<definedType>>& arr);
