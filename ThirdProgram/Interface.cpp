#include "Interface.h"

void DrawBorder() {
    cout << "===================================================================================";
}
void DrawSubBorder() {
    cout << "-----------------------------------------------------------------------------------";
}

int EnterSettingsTwo() {
    int  setting = 0;
    cout << endl << "=>";
    cin >> setting;

    while (true) {
        if (setting == 1 || setting == 2) {
            break;
        }
        cout << "=>";

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
    cout << endl << "=>";
    cin >> setting;

    while (true) {
        if (setting == 1 || setting == 2 || setting == 3) {
            break;
        }
        cout << "=>";

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

//void WriteOutput(vector<book*>* books, bool flagIgnoreHaritage, bool flagWriteTo) {
//    if (flagWriteTo) {
//        while (true) {
//            string filePath = " ";
//            filePath = EnterFilePath();
//
//            ifstream test(filePath.c_str());
//            if (test.is_open()) {
//                cout << "File already exist. You still want a write on it? (Yes \"1\" or No \"2\"): ";
//                if (EnterSettingsTwo() == 2) {
//                    continue;
//                }
//            }
//
//            ofstream outputStream(filePath.c_str());
//            if (!outputStream.is_open()) {
//                cout << "File with this name don't exist. Try again" << endl;
//                continue;
//            }
//            else {
//                for (size_t i = 0; i < books->size(); ++i) {
//                    if (flagIgnoreHaritage) {
//                        outputStream << books->at(i)->Get();
//                    }
//                    else {
//                        if (dynamic_cast<techBook*>(books->at(i))){
//                            outputStream << dynamic_cast<techBook*>(books->at(i))->Get();
//                        }
//                        else {
//                            outputStream << books->at(i)->Get();
//                        }
//                    }
//                }
//                break;
//            }
//        }
//    }
//    else{
//        for (size_t i = 0; i < books->size(); ++i) {
//            if (flagIgnoreHaritage) {
//                cout << books->at(i)->Get();
//            }
//            else {
//                if (dynamic_cast<techBook*>(books->at(i))){
//                    cout << dynamic_cast<techBook*>(books->at(i))->Get();
//                }
//                else {
//                    cout << books->at(i)->Get();
//                }
//            }
//        }
//    }
//    
//}

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
            if (!(inputStream >> m)) {
                cout << "Invalid data from file( incorrect value of 'm' ) " << endl;
                continue;
            }
            if (!(inputStream >> n)) {
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
    
    cout << "Enter m: ";
    m = EnterNum<int>();

    cout << "Enter n: ";
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
    srand(time(NULL));
    int m = 0, n = 0;

    vector<definedType> subArr;

    cout << "Enter m: ";
    m = EnterNum<int>();

    cout << "Enter n: ";
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

    /////////////////////////////////////////////////////////////////////////
    //  It is necessary to sort the rows of the matrix in ascending order  //
    /////////////////////////////////////////////////////////////////////////

    cout << "Do you want are full information about sorting (Yes \"1\" or No \"2\")";
    if (EnterSettingsTwo() == 1) flagFullInfo = true;

    subArrSort = arrOrig;
    SortHandler<BubbleSort<definedType>>(subArrSort, flagFullInfo);
    arrSort = subArrSort;

    subArrSort = arrOrig;
    SortHandler<SelectionSort<definedType>>(subArrSort, flagFullInfo);

    subArrSort = arrOrig;
    SortHandler<InsertionSort<definedType>>(subArrSort, flagFullInfo);

    subArrSort = arrOrig;
    SortHandler<ShellSort<definedType>>(subArrSort, flagFullInfo);

    subArrSort = arrOrig;
    SortHandler<QuickSort<definedType>>(subArrSort, flagFullInfo);
}

void Compare(const vector<vector<definedType>>& arrOrig, vector<vector<definedType>>& arrSort) { ; }

