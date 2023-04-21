#pragma once

#include "Classes.h"

template <typename T> bool IsInBetween(const T& num, const T& start, const T& end) {
    return start < num && num <= end;
}

void DrawBorder(ostream& outputStream = cout);
void DrawSubBorder(ostream& outputStream = cout);

int EnterSettingsTwo();
int EnterSettingThree();
string EnterFilePath();

template <typename type = int>
type EnterNum(const string& msg) {
    type item{};

    while (cout << msg && !(cin >> item)) {
        cin.clear();
        cin.ignore(INT32_MAX, '\n');
        cout << endl << "Invalide input. Try again" << endl;
    }

    return item;
}

void WriteOutputConsole(const vector<vector<definedType>>& arr, ostream& output = cout);

void WriteOutputFile(const vector<vector<definedType>>& arr);

void InputFromFile(vector<vector<definedType>>& arrOrig);

void InputFromConsole(vector<vector<definedType>>& arrOrig);

void InputRandom(vector<vector<definedType>>& arrOrig);

void CompareAll(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort);

void Compare(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort);

template <class sortFunction>
void SortHandler(vector<vector<definedType>>& subArrSort, bool flagFullInfo, stringstream& stats, stringstream& result) {
    sortFunction function{};

    int numOfCompares = 0;
    int numOfSwaps = 0;
    int executionTime = 0;
    
    stats << endl;
    if (flagFullInfo) {
        stats << function.Name() << endl;
        DrawSubBorder(stats);
        stats << endl;
    }

    for (auto i = 0; i < subArrSort.size(); ++i) {
        function.Sort(subArrSort[i]);
        numOfCompares += function.GetNumOfCompares();
        numOfSwaps += function.GetNumOfOperations();
        executionTime += function.GetTime();
        
        if (flagFullInfo) {
            stats << "arr[" << i+1 << "] { " << function.Info() << " }" << endl;
        }
        function.Clear();
    }
    
    stats << function.Name() << " { Num of compares : " << numOfCompares << " || "
        << "Num of swaps: " << numOfSwaps << " || "
        << "Execution time: " << executionTime << " }" << endl;
    DrawBorder(stats);


    result << endl << function.Name() << endl;
    DrawSubBorder(result);
    result << endl;
    WriteOutputConsole(subArrSort, result);
    DrawSubBorder(result);
}
