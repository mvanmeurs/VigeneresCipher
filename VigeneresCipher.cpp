//
// Created by mason on 3/28/2020.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "VigeneresCipher.h"

VigeneresCipher::VigeneresCipher() {
    initTable();
    //generateKey(4, "key.txt");
    //generateCipherText("key.txt", "ciphertext.txt", "plaintext.txt");
    //generatePlainText("key.txt", "plaintextgenerated.txt", "ciphertext.txt");
    generateText("key.txt", "ciphertext.txt", "plaintext.txt", 1);
    generateText("key.txt", "plaintextdecrypted.txt", "ciphertext.txt", 0);
}

void VigeneresCipher::initTable() {
    table[0][0] = "~";
    for( int column = 1 ; column < WIDTH ; column++){
        table[0][column] = (char)(column + UPPERCASE_A - 1);
    }
    for( int row = 1 ; row < HEIGHT ; row++){
        table[row][0] = to_string(row);
    }
    int index = 1;
    for (int row = 1 ; row < HEIGHT ; row++){
        for (int column = 1 ; column < WIDTH ; column++){
            table[row][column] = (char)((index%SIZE_OF_ALPHABET) + LOWERCASE_a);
            index++;
        }
        index++;
    }
    //printTable();
}

void VigeneresCipher::printTable() {
    cout << "The Matrix is:" << endl;
    for (int row = 0 ; row < HEIGHT ; row++){
        if(row < 10){cout << " "; }
        for (int column = 0 ; column < WIDTH ; column++){
            cout << table[row][column] << " ";
        }
        cout << endl;
    }
}

void VigeneresCipher::generateKey(int length, string name) {
    srand((unsigned) time(0));
    ofstream fout(name.c_str());
    assert(fout.is_open());
    for(unsigned i = 0 ; i<length ; i++){
        fout << (rand()%SIZE_OF_ALPHABET) + 1;
        if( i < length -1){fout << ",";}
    }
    fout.close();
}

void VigeneresCipher::generateText(string keyname, string outputname, string inputname, bool isGenerateCipherText) {
    vector <string> keyvalues;

    ofstream outputname_fout(outputname.c_str());
    assert(outputname_fout.is_open());
    ifstream keyname_fin(keyname);
    assert(keyname_fin.is_open());
    ifstream inputname_fin(inputname);
    assert(inputname_fin.is_open());

    string key_text;
    string input_text;
    string output_text;

    getline(keyname_fin, key_text);
    getline(inputname_fin, input_text);

    keyname_fin.close();
    inputname_fin.close();

    //Parse the string into a vector
    unsigned beginning = 0;
    unsigned counter = 1;
    for( unsigned i = 0 ; i < key_text.size() ; i++) {
        if (key_text.at(i) == ',') {
            keyvalues.push_back(key_text.substr(beginning, counter - 1));
            beginning = i + 1;
            counter = 0;
        }
        counter++;
    }
    keyvalues.push_back(key_text.substr(beginning, key_text.size()));

    //we iterate through the input text
    for( unsigned i  = 0 ; i < input_text.size() ; i++){
        //check if it's a space or not
        if ( input_text.at(i) != ' '){
            //if we are generating cipher text, then we append the cipher character to the output text
            if( isGenerateCipherText){
                output_text += getCipherCharacter((char)toupper(input_text.at(i)), keyvalues.at(i % keyvalues.size()));
            }
            else{
                output_text += getPlainTextCharacter((char)toupper(input_text.at(i)), keyvalues.at(i % keyvalues.size()));
            }
        }
        else{
            output_text += ' ';
        }
    }

    outputname_fout << output_text << flush;
    outputname_fout.close();
}

char VigeneresCipher::getCipherCharacter(char input, const string& keyvalue) {
    int index = -stoi(keyvalue) + (int)input - UPPERCASE_A;
    while(index < 0){
        index += SIZE_OF_ALPHABET;
    }
    return (char)(index + UPPERCASE_A);
}

char VigeneresCipher::getPlainTextCharacter(char input, const string& keyvalue) {
    return (char) ( (stoi(keyvalue) + (int)input - UPPERCASE_A) % SIZE_OF_ALPHABET ) + UPPERCASE_A;
}

