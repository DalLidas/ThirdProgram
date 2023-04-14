#include "Interface.h"

void DrawBorder(ostream& outputStream) {
    outputStream << "===================================================================================";
}
void DrawSubBorder(ostream& outputStream) {
    outputStream << "-----------------------------------------------------------------------------------";
}

int EnterSettingsTwo() {
    int  setting = 0;
    cout << endl << ": ";
    cin >> setting;

    while (true) {
        if (setting == 1 || setting == 2) {
            break;
        }
        cout << ": ";

        while (!(cin >> setting))
        {
            cin.clear();
            cin.ignore(INT32_MAX, '\n');
            cout << "Invalid input. Try again" << endl
                << "Enter \"1\" or \"2\": ";
        }
    }
    return setting;
}
int EnterSettingThree() {
    int setting = 0;
    cout << endl << ": ";
    cin >> setting;

    while (true) {
        if (setting == 1 || setting == 2 || setting == 3) {
            break;
        }
        cout << ": ";

        while (!(cin >> setting))
        {
            cin.clear();
            cin.ignore(INT32_MAX, '\n');
            cout << "Invalid input. Try again" << endl
                << "Enter \"1\" or \"2\" or \"3\": ";
        }
    }
    return setting;
}

string EnterFilePath() {
    string filePath = " ";
    static const regex reg("((/./)?(con))|((/./)?(con\\.))|((/./)?(con\\.)(.*))");

    while (true) {
        cout << "Enter file path: ";
        cin >> filePath;

        if (!regex_match(filePath.c_str(), reg)) {
            break;
        }
        cout << "You enter reserved by system file name. Try again" << endl;
    }

    return filePath.c_str();
}

void InputFromFile(vector<vector<definedType>>& arrOrig) {
    int m = 0, n = 0;

    vector<definedType> subArr;
    definedType variable;

    while (true) {
        string filePath = " ";
        filePath = EnterFilePath();
        ifstream inputStream(filePath.c_str());
        if (!inputStream.is_open()) {
            cout << "File with this name don't exist. Try again" << endl;
            continue;
        }
        else {
            if (!(inputStream >> m || m < 0)) {
                cout << "Invalid data from file( incorrect value of 'm' ) " << endl;
                continue;
            }
            if (!(inputStream >> n || n < 0)) {
                cout << "Invalid data from file( incorrect value of 'n' ) " << endl;
                continue;
            }

            for (auto i = 0; i < m; ++i) {
                for (auto j = 0; j < n; ++j) {
                    if (inputStream >> variable) {
                        subArr.push_back(variable);
                    }
                    else {
                        cout << "Invalid data from file( incorrect matrix value ) " << endl;
                        arrOrig.clear();
                        continue;
                    }
                }
                arrOrig.push_back(subArr);
                subArr.clear();
            }

            inputStream.close();
            break;
        }
    }
}

void InputFromConsole(vector<vector<definedType>>& arrOrig) {
    int m = 0, n = 0;

    vector<definedType> subArr;
    definedType variable;
    
    cout << "Enter m";
    m = EnterNum<int>();

    cout << "Enter n";
    n = EnterNum<int>();

    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            cout << "arr[" << i << "][" << j << "] = ";
            variable = EnterNum<int>();
            subArr.push_back(variable);
        }
        arrOrig.push_back(subArr);
        subArr.clear();
    }
}

void InputRandom(vector<vector<definedType>>& arrOrig) {
    srand(static_cast<unsigned int>(time(NULL)));
    int m = 0, n = 0;

    vector<definedType> subArr;

    cout << "Enter m";
    m = EnterNum<int>();

    cout << "Enter n";
    n = EnterNum<int>();

    for (auto i = 0; i < m; ++i) {
        subArr.resize(n);
        generate(subArr.begin(), subArr.end(), rand);
        arrOrig.push_back(subArr);
        subArr.clear();
    }
}

void CompareAll(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort) {
    vector<vector<definedType>> subArrSort;

    bool flagFullInfo = false;
    bool flagWriteInfo = false;

    ofstream outputStream;

    /////////////////////////////////////////////////////////////////////////
    //  It is necessary to sort the rows of the matrix in ascending order  //
    /////////////////////////////////////////////////////////////////////////

    cout << "Do you want are full information about sorting (Yes \"1\" or No \"2\")";
    if (EnterSettingsTwo() == 1) flagFullInfo = true;
    DrawSubBorder();

    cout << endl << "Do you want write to file info about sorting (Yes \"1\" or No \"2\")";
    if (EnterSettingsTwo() == 1) flagWriteInfo = true;

    //Open stream to write info to file
    if (flagWriteInfo) { 
        while (true) {
            string filePath = " ";
            filePath = EnterFilePath();

            ifstream test(filePath.c_str());
            if (test.is_open()) {
                cout << "File already exist. You still want a write on it? (Yes \"1\" or No \"2\")";
                if (EnterSettingsTwo() == 2) continue;
            }
            test.close();

            outputStream.open(filePath.c_str(), ios::app);
            if (!outputStream.is_open()) {
                cout << "File with this name don't exist. Try again" << endl;
                continue;
            }
            else {
                break;
            }
        }
    }
   

    subArrSort = arrOrig;
    if (flagWriteInfo) SortHandler<BubbleSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
    else SortHandler<BubbleSort<definedType>>(subArrSort, flagFullInfo);
    arrSort = subArrSort;

    subArrSort = arrOrig;
    if (flagWriteInfo) SortHandler<SelectionSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
    else SortHandler<SelectionSort<definedType>>(subArrSort, flagFullInfo);

    subArrSort = arrOrig;
    if (flagWriteInfo) SortHandler<InsertionSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
    else SortHandler<InsertionSort<definedType>>(subArrSort, flagFullInfo);

    subArrSort = arrOrig;
    if (flagWriteInfo) SortHandler<ShellSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
    else SortHandler<ShellSort<definedType>>(subArrSort, flagFullInfo);

    subArrSort = arrOrig;
    if (flagWriteInfo) SortHandler<QuickSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
    else SortHandler<QuickSort<definedType>>(subArrSort, flagFullInfo);

    if (flagWriteInfo) outputStream.close();
}

void Compare(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort) {
    vector<vector<definedType>> subArrSort;
    vector<int> sortingOrder;
    int numOfSortFunc = 0;
    int sortFunc = 0;

    bool flagFullInfo = false;
    bool flagWriteInfo = false;

    ofstream outputStream;

    cout << "Do you want are full information about sorting (Yes \"1\" or No \"2\")";
    if (EnterSettingsTwo() == 1) flagFullInfo = true;
    DrawSubBorder();

    cout << endl << "Do you want write to file info about sort (Yes \"1\" or No \"2\")";
    if (EnterSettingsTwo() == 1) flagWriteInfo = true;
    DrawSubBorder();
    cout << endl;

    //Open stream to write info to file
    if (flagWriteInfo) {
        while (true) {
            string filePath = " ";
            filePath = EnterFilePath();

            ifstream test(filePath.c_str());
            if (test.is_open()) {
                cout << "File already exist. You still want a write on it? (Yes \"1\" or No \"2\")";
                if (EnterSettingsTwo() == 2) continue;
            }
            test.close();

            outputStream.open(filePath.c_str(), ios::app);
            if (!outputStream.is_open()) {
                cout << "File with this name don't exist. Try again" << endl;
                continue;
            }
            else {
                break;
            }
        }
    }

    cout << endl << "How many sort functions you want to use";
    while (!IsInBetween<int>(numOfSortFunc = EnterNum<int>(), 0, INT_MAX));

    DrawSubBorder();
    cout << endl << "Set the type of sorting order:" << endl
        << "1.BubbleSort" << endl
        << "2.SelectionSort" << endl
        << "3.InsertionSort" << endl
        << "4.ShellSort" << endl
        << "5.QuickSort" << endl;
    DrawSubBorder();
    cout << endl;

    for (auto i = 0; i < numOfSortFunc; ++i) {
        cout << "sorting function[" << i << "] type";
        while (!IsInBetween<int>(sortFunc = EnterNum<int>(), 0, numOfSortFunctions));

        sortingOrder.push_back(sortFunc);
    }

    for (auto i = 0; i < numOfSortFunc; ++i) {
        switch (sortingOrder[i]) {
        case(1):
            subArrSort = arrOrig;
            if (flagWriteInfo) SortHandler<BubbleSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
            else SortHandler<BubbleSort<definedType>>(subArrSort, flagFullInfo);
            break;
        case(2):
            subArrSort = arrOrig;
            if (flagWriteInfo) SortHandler<SelectionSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
            else SortHandler<SelectionSort<definedType>>(subArrSort, flagFullInfo);
            break;
        case(3):
            subArrSort = arrOrig;
            if (flagWriteInfo) SortHandler<InsertionSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
            else SortHandler<InsertionSort<definedType>>(subArrSort, flagFullInfo);
            break;
        case(4):
            subArrSort = arrOrig;
            if (flagWriteInfo) SortHandler<ShellSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
            else SortHandler<ShellSort<definedType>>(subArrSort, flagFullInfo);
            break;
        case(5):
            subArrSort = arrOrig;
            if (flagWriteInfo) SortHandler<QuickSort<definedType>>(subArrSort, flagFullInfo, true, outputStream);
            else SortHandler<QuickSort<definedType>>(subArrSort, flagFullInfo);
            break;
        }

        if (i == 0) arrSort = subArrSort;
    }
}

void WriteOutputConsole(const vector<vector<definedType>>& arr){
    for (auto i = 0; i < arr.size(); ++i) {
        for (auto j = 0; j < arr[0].size(); ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void WriteOutputFile(const vector<vector<definedType>>& arr) {
    while (true) {
        string filePath = " ";
        filePath = EnterFilePath();

        ifstream test(filePath.c_str());
        if (test.is_open()) {
            cout << "File already exist. You still want a write on it? (Yes \"1\" or No \"2\")";
            if (EnterSettingsTwo() == 2) continue;
        }
        test.close();

        ofstream outputStream(filePath.c_str());
        if (!outputStream.is_open()) {
            cout << "File with this name don't exist. Try again" << endl;
            continue;
        }
        else {
            outputStream << arr.size() << " " << arr[0].size() << endl;
            for (auto i = 0; i < arr.size(); ++i) {
                for (auto j = 0; j < arr[0].size(); ++j) {
                    outputStream << arr[i][j] << " ";
                }
                outputStream << endl;
            }
            outputStream.close();
            break;
        }
    }
}

