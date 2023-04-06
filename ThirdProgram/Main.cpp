#include "Interface.h"

//#ifdef __include_Test
    #include "Test.h"
//#endif

enum inputSettings   { inputFromFile = 1, inputFromConsole = 2 , inputRandom = 3};
enum compareSettings { compareAll = 1, compare = 2 , dontCompare = 3};
enum exitSettings    { oldMatrix = 1, newMatrix = 2, closeProgram = 3 };
;

int main() {
    //settings
    int inputSetting   = 0;
    int compareSetting = 0;
    int exitSetting    = 0;

    //flags
    //#ifdef __include_Test
        bool flagErrorExist = true;
    //#endif

    bool flagWriteIfConsoleInput = false;
    bool flagInputNewMatrix      = true;

    //containers
    vector<vector<definedType>> arrOrig;
    vector<vector<definedType>> arrSort;

    //#ifdef __include_Test
        DrawBorder();
        cout << endl << "Program passed all test. All sorting function work correct" << endl;
        DrawSubBorder();
        cout << endl;
        flagErrorExist = ErrorHandler();
        if (flagErrorExist) {
            cout << "Do you still want are run the program? (Yes \"1\" or No \"2\")";
            if (EnterSettingsTwo() == 2) return 0;
        }
        else {
            DrawSubBorder();
            cout << endl << "Program passed all test. All sorting function work correct" << endl ;
            DrawBorder();
        }
    //#endif


    cout << endl << "3.1 Task by Mukhametov D.I. 423 group option 1" << endl << endl
        << "Create class student included fields ( surname, first name, patronymic," << endl
        << "date of birth, address, phone, faculty, course.Create an array of objects." << endl << endl
        << "To realize the possibility of obtaining :" << endl
        << "- a list of students of a given faculty," << endl
        << "- lists of students for each faculty and course," << endl
        << "- a list of students born after a given year." << endl << endl;
	
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
            case(inputFromFile): InputFromFile(arrOrig); break;                                         //Input from file
            case(inputFromConsole): InputFromConsole(arrOrig); flagWriteIfConsoleInput = true; break;   //Input from console
            case(inputRandom): InputRandom(arrOrig); break;                                             //Generate
            default: cout << "Unexpected behavior" << endl; continue;
            }

            if (flagWriteIfConsoleInput) {
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
        case(compareAll): CompareAll(arrOrig, arrSort); break;  //Input from file
        case(compare): Compare(arrOrig, arrSort); break;        //Input from console
        case(dontCompare): break;                               //Nothing 
        default: cout << "Unexpected behavior" << endl; continue;
        }

        if(compareSetting != dontCompare){
            DrawBorder();
            cout << endl << "Do you want are write to console sorted matrix (Yes \"1\" or No \"2\")";
            if (EnterSettingsTwo() == 1) WriteOutputConsole(arrSort);

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