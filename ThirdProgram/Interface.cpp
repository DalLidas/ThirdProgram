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
            if (!(inputStream >> m || m < 1)) {
                cout << "Invalid data from file( incorrect value of 'rows' ) " << endl;
                continue;
            }
            if (!(inputStream >> n || n < 2)) {
                cout << "Invalid data from file( incorrect value of 'collums' ) " << endl;
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

    while (m <= 0) m = EnterNum<int>("Enter rows ( rows > 0 ): ");
    while (n <= 1) n = EnterNum<int>("Enter collums ( collums > 1 ): ");


    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            variable = EnterNum<int>("arr[" + to_string(i+1) + "][" + to_string(j+1) + "] = ");
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

    while (m <= 0) m = EnterNum<int>("Enter rows ( rows > 0 ): ");
    while (n <= 1) n = EnterNum<int>("Enter collums ( collums > 1 ): ");

    for (auto i = 0; i < m; ++i) {
        subArr.resize(n);
        generate(subArr.begin(), subArr.end(), []() -> definedType {return(rand() % 1000 / 10. - 50); });
        arrOrig.push_back(subArr);
        subArr.clear();
    }
}

void CompareAll(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort) {
    vector<vector<definedType>> subArrSort;

    bool flagFullInfo = false;

    ofstream outputStream{};
    stringstream stats{};
    stringstream results{};

    DrawBorder(stats);

    /////////////////////////////////////////////////////////////////////////
    //  It is necessary to sort the rows of the matrix in ascending order  //
    /////////////////////////////////////////////////////////////////////////

    cout << "Do you want full information about sorting (Yes \"1\" or No \"2\")";
    if (EnterSettingsTwo() == 1) flagFullInfo = true;
    DrawBorder();
    cout << endl;
    DrawSubBorder();

    subArrSort = arrOrig;
    SortHandler<BubbleSort<definedType>>(subArrSort, flagFullInfo, stats, results);
    arrSort = subArrSort;

    subArrSort = arrOrig;
    SortHandler<SelectionSort<definedType>>(subArrSort, flagFullInfo, stats, results);

    subArrSort = arrOrig;
    SortHandler<InsertionSort<definedType>>(subArrSort, flagFullInfo, stats, results);
    
    subArrSort = arrOrig;
    SortHandler<ShellSort<definedType>>(subArrSort, flagFullInfo, stats, results);
  
    subArrSort = arrOrig;
    SortHandler<QuickSort<definedType>>(subArrSort, flagFullInfo, stats, results);

    cout << results.str() << endl;
    if (!flagFullInfo)
        cout << setw(16) << "Name of sorting"
        << setw(5) << " | "
        << setw(16) << "Num of compares"
        << setw(5) << " | "
        << setw(16) << "Num of swaps"
        << setw(5) << " | "
        << setw(16) << "Execution time"
        << setw(5) << " | " << endl;
    cout << stats.str();

    cout << endl << "Do you want write to file info about sorting (Yes \"1\" or No \"2\")";

    //Open stream to write info to file
    if (EnterSettingsTwo() == 1) {
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

        DrawSubBorder(outputStream);
        outputStream << results.str() << endl;
        if (!flagFullInfo)
            outputStream << setw(16) << "Name of sorting"
            << setw(5) << " | "
            << setw(16) << "Num of compares"
            << setw(5) << " | "
            << setw(16) << "Num of swaps"
            << setw(5) << " | "
            << setw(16) << "Execution time"
            << setw(5) << " | " << endl;
        outputStream << stats.str();

        outputStream.close();
    }

}

void Compare(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort) {
    vector<vector<definedType>> subArrSort;
    vector<int> sortingOrder;
    int numOfSortFunc = 0;
    int sortFunc = 0;

    bool flagFullInfo = false;

    ofstream outputStream;
    stringstream stats{};
    stringstream results{};

    DrawBorder(stats);

    cout << "Do you want full information about sorting (Yes \"1\" or No \"2\")";
    if (EnterSettingsTwo() == 1) flagFullInfo = true;
    DrawSubBorder();

    cout <<endl << "How many sort functions you want to use: ";
    while (!IsInBetween<int>(numOfSortFunc = EnterNum<int>(""), 0, INT_MAX));

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
        while (!IsInBetween<int>(sortFunc = EnterNum<int>(("sorting function[" + to_string(i + 1) + "] type: ")), 0, numOfSortFunctions));

        sortingOrder.push_back(sortFunc);
    }

    DrawBorder();
    cout << endl;    
    DrawSubBorder();

    for (auto i = 0; i < numOfSortFunc; ++i) {
        switch (sortingOrder[i]) {
        case(1):
            subArrSort = arrOrig;
            SortHandler<BubbleSort<definedType>>(subArrSort, flagFullInfo, stats, results);
            break;
        case(2):
            subArrSort = arrOrig;
            SortHandler<SelectionSort<definedType>>(subArrSort, flagFullInfo, stats, results);
            break;
        case(3):
            subArrSort = arrOrig;
            SortHandler<InsertionSort<definedType>>(subArrSort, flagFullInfo, stats, results);
            break;
        case(4):
            subArrSort = arrOrig;
            SortHandler<ShellSort<definedType>>(subArrSort, flagFullInfo, stats, results);
            break;
        case(5):
            subArrSort = arrOrig;
            SortHandler<QuickSort<definedType>>(subArrSort, flagFullInfo, stats, results);
            break;
        }
    }

    arrSort = subArrSort;
    cout << results.str() << endl;
    if (!flagFullInfo)
        cout << setw(16) << "Name of sorting"
        << setw(5) << " | "
        << setw(16) << "Num of compares"
        << setw(5) << " | "
        << setw(16) << "Num of swaps"
        << setw(5) << " | "
        << setw(16) << "Execution time"
        << setw(5) << " | " << endl;
    cout << stats.str();

    cout << endl << "Do you want write to file info about sorting (Yes \"1\" or No \"2\")";

    //Open stream to write info to file
    if (EnterSettingsTwo() == 1) {
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

        DrawSubBorder(outputStream);
        outputStream << results.str() << endl;
        if(!flagFullInfo)
            outputStream << setw(16) << "Name of sorting"
            << setw(5) << " | "
            << setw(16) << "Num of compares"
            << setw(5) << " | "
            << setw(16) << "Num of swaps"
            << setw(5) << " | "
            << setw(16) << "Execution time"
            << setw(5) << " | " << endl;
        outputStream << stats.str();

        outputStream.close();
    }
}

void WriteOutputConsole(const vector<vector<definedType>>& arr, ostream& output){
    for (auto i = 0; i < arr.size(); ++i) {
        for (auto j = 0; j < arr[0].size(); ++j) {
            output << " | " << setw(consoleOutputNumBuffer) << arr[i][j];
        }
        output << " | "  << endl;
    }
}

void WriteOutputFile(const vector<vector<definedType>>& arr) {
    while (true) {
        string filePath = " ";
        filePath = EnterFilePath();

        ifstream test(filePath.c_str());
        if (test.is_open()) {
            cout << "File already exist. You still want write on it? (Yes \"1\" or No \"2\")";
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

