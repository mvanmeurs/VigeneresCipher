//
// Created by CSchumacker on 4/1/2020.
//

#include "Menu.h"
#include <fstream>
#include <cassert>

Menu::Menu() {
    cout << "Welcome to the Vigenere's Cipher Program" << endl;
    printOptions();

    string input;
    getline(cin, input);

    vector<string> operations;

    //check that we have three arguments with no extra spaces in filenames
    do{
        try{
            operations = extractOperations(input);
            while(true){
                try{
                    if(operations[0] != "generatekey" && operations[0] != "generatecipher" && operations[0] != "generateplaintext"){throw 1;}
                    break;
                }catch( int num) {
                    cerr << "Please enter a valid command" << endl;
                    getline(cin, input);
                }
            }
            break;
        }catch( int numspaces) {
            cerr << "Please enter three arguments with a space in between each one." << endl;
            getline(cin, input);
        }
    }while(true);

    cout << operations[0] << operations[1] << operations[2] << endl;
}

void Menu::printOptions() const {
    cout << "\nPlease enter an option:" << endl;
    cout << "Note: filenames can't have spaces in them." << endl;
    cout << "generatekey <keysize> <keyfile_name>" << endl;
    cout << "generatecipher <keyfile_name> <output_filename>" << endl;
    cout << "generateplaintext <keyfile_name> <output_filename>" << endl;
}

bool Menu::isLegal(const string& input) {
    //return input[8] == 'k' || input[8] == 'c' || input[8] == 'p';
    return false;
}

void Menu::generateKey(const string& keyname) {

}

bool Menu::isValidFileName(const string& filename) {
    int index = filename.find_last_of('.');
    return filename.substr(index, 4) != ".txt";
}

vector<string> Menu::extractOperations(const string& input) {
    int numspaces = 0;
    for( unsigned i = 0 ; i < input.size() ; i++){
        if( input.at(i) == ' '){numspaces++;}
    }
    if(numspaces != 2){throw numspaces;}
    vector<string> vector;
    int firstSpace = input.find_first_of(' ');
    vector.push_back(input.substr(0, firstSpace));
    int lastspace = input.find_last_of(' ');
    vector.push_back(input.substr(firstSpace + 1, lastspace - firstSpace - 1));
    vector.push_back(input.substr(lastspace + 1, input.size() - lastspace));
    if(vector.size() != 3){throw 1;}
    if(vector[0].size() == 0 || vector[1].size() == 0 || vector[2].size() == 0){throw 1;}
    return vector;
}

void Menu::checkCommand(const string& command) {
    if(command == "generatekey" || command == "generatecipher" || command == "generateplaintext"){throw 1;}
}
