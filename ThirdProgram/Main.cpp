#include "Interface.h"

enum inputSettings     { inputFromFile = 1, inputFromConsole = 2 , inputRandom = 3};
enum writeMenuSettings { wrirteAndIgnore = 1, writeDontIgnore = 2, dontWrite = 3 };
enum writeModSettings  { dontIgnoring = 0, ignoring = 1 };
enum writeSettings     { toConsole = 0, toFile = 1 };
enum exitSettings      { oldBooks = 1, newBooks = 2, closeProgram = 3 };

int main() {
    //settings
    int inputSetting  = 0;
    int outputSetting = 0;
    int exitSetting   = 0;

    //container 
    vector<vector<definedType>> arrOrig;
    vector<vector<definedType>> arrSort;

    cout << "3.1 Task by Mukhametov D.I. 423 group option 1" << endl << endl
        << "Create class student included fields ( surname, first name, patronymic," << endl
        << "date of birth, address, phone, faculty, course.Create an array of objects." << endl << endl
        << "To realize the possibility of obtaining :" << endl
        << "- a list of students of a given faculty," << endl
        << "- lists of students for each faculty and course," << endl
        << "- a list of students born after a given year." << endl << endl;
	
    while (true) {
        DrawBorder();
        cout << endl << "How do you want to write books to file:" << endl
            << "1.Enter matrix from file" << endl
            << "2.Enter matrix from console" << endl
            << "3.Generate matrix";
        outputSetting = EnterSettingThree();

        DrawSubBorder();
        cout << endl;
        //input
        switch (outputSetting) {
        case(inputFromFile): InputFromFile(arrOrig); break;         //Input from file
        case(inputFromConsole): InputFromConsole(arrOrig); break;   //Input from console
        case(inputRandom): InputRandom(arrOrig); break;             //Generate
        default: cout << "Unexpected behavior" << endl; continue;
        }


        DrawBorder();
        cout << endl << "What to do:" << endl
            << "1.Compare all sorting functions" << endl
            << "2.Compare selected sorting functions";
            
        outputSetting = EnterSettingsTwo();

        //compare sorting functions
        DrawSubBorder();
        cout << endl;
        switch (outputSetting) {
        case(inputFromFile): CompareAll(arrOrig, arrSort); break;         //Input from file
        case(inputFromConsole): Compare(arrOrig, arrSort); break;   //Input from console
        default: cout << "Unexpected behavior" << endl; continue;
        }





        for (auto i = 0; i < arrOrig.size(); ++i) {
            for (auto j = 0; j < arrOrig[0].size(); ++j) {
                cout << arrOrig[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
        for (auto i = 0; i < arrSort.size(); ++i) {
            for (auto j = 0; j < arrSort[0].size(); ++j) {
                cout << arrSort[i][j] << " ";
            }
            cout << endl;
        }
    }


	return 0; 
}