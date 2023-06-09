#include "Interface.h"
#include "Test.h"


enum inputSettings   { inputFromFile = 1, inputFromConsole = 2, inputRandom  = 3};
enum compareSettings { compareAll    = 1, compare          = 2, dontCompare  = 3};
enum exitSettings    { oldMatrix     = 1, newMatrix        = 2, closeProgram = 3};

int main() {
    //settings
    int inputSetting   = 0;
    int compareSetting = 0;
    int exitSetting    = 0;

    //flags
    bool flagErrorExist          = true;
    bool flagInputNewMatrix      = true;

    //containers
    vector<vector<definedType>> arrOrig;
    vector<vector<definedType>> arrSort;

    
    flagErrorExist = ErrorHandler();
    if (flagErrorExist) {
        cout << " Do you still want are run the program? (Yes \"1\" or No \"2\")";
        if (EnterSettingsTwo() == 2) return 0;
    }
    else {
        DrawBorder();
        cout << endl << "Program passed all test. All sorting function work correct" << endl ;
        DrawBorder();
    }

    cout << endl << "3 Task by Mukhametov D.I. 423 group option 15" << endl << endl
        << "It is necessary to create a program for sorting an array of data by methods : bubble, selection, insertion," << endl
        << "Shell and quick sorting.Display unordered(once) and ordered(for each of the methods) arrays of data." << endl
        << "Make a comparative table of the effectiveness of the methods, in which it is necessary" << endl
        << "to specify the number of comparisons and permutations of variables in each sorting method." << endl
        << "An unordered matrix of N rows and M columns is set and filled in once(from the keyboard," << endl
        << "from a file, or with random numbers), then it is used for each of the sorting methods." << endl << endl
        << "Implement an abstract ISort base class containing a pure virtual Sort method and" << endl
        << "the necessary counters from which to inherit subclasses for implementing sorts." << endl << endl
        << "Arrange each row of the matrix in ascending order." << endl ;
 
    while (true) {
        if (flagInputNewMatrix) {
            DrawBorder();
            cout << endl << "How do you want enter matrix:" << endl
                << "1.Enter matrix from file" << endl
                << "2.Enter matrix from console" << endl
                << "3.Generate matrix";
            inputSetting = EnterSettingThree();
            DrawSubBorder();
            cout << endl;

            //input
            switch (inputSetting) {
            case(inputFromFile): InputFromFile(arrOrig); break;         //Input from file
            case(inputFromConsole): InputFromConsole(arrOrig); break;   //Input from console
            case(inputRandom): InputRandom(arrOrig); break;             //Generate
            default: cout << "Unexpected behavior" << endl; continue;
            }

            if (inputSetting == inputFromFile || inputSetting == inputRandom) {
                DrawSubBorder();
                cout << endl;
                WriteOutputConsole(arrOrig);
            }
            if (inputSetting == inputFromConsole || inputSetting == inputRandom){
                DrawBorder();
                cout << endl << "Do you want are write to file entered matrix (Yes \"1\" or No \"2\")";
                if (EnterSettingsTwo() == 1) WriteOutputFile(arrOrig);
            }

            
        }
   

        DrawBorder();
        cout << endl << "What to do:" << endl
            << "1.Compare all sorting functions" << endl
            << "2.Compare selected sorting functions" << endl
            << "3.Don't compare";
        compareSetting = EnterSettingThree();
        if (compareSetting != dontCompare) {
            DrawSubBorder();
            cout << endl;
        }

        //compare sorting functions
        switch (compareSetting) {
        case(compareAll): CompareAll(arrOrig, arrSort); break;  //Compare all sorting function
        case(compare): Compare(arrOrig, arrSort); break;        //Chose sorting function
        case(dontCompare): break;                               //Dont compare 
        default: cout << "Unexpected behavior" << endl; continue;
        }

        if(compareSetting != dontCompare){
            DrawSubBorder();
            cout << endl << "Do you want are write to file sorted matrix (Yes \"1\" or No \"2\")";
            if (EnterSettingsTwo() == 1) WriteOutputFile(arrSort);
        }

        
        DrawBorder();
        cout << endl << "What to do next:" << endl
            << "1.Use old matrix on next cycle" << endl
            << "2.Enter new matrix" << endl
            << "3.Close program";
        exitSetting = EnterSettingThree();

        //ending
        switch (exitSetting) {
        case(oldMatrix): flagInputNewMatrix = false; arrSort.clear(); break;                 //use old students on next cycle
        case(newMatrix): flagInputNewMatrix = true; arrOrig.clear(); arrSort.clear(); break; //enter new students 
        case(closeProgram): return 0;                                                        //closeProgram
        default: cout << "Unexpected behavior" << endl; continue;
        }
    }
}