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
    generateCipherText("key.txt", "ciphertext.txt", "plaintext.txt");
    generatePlainText("key.txt", "plaintextgenerated.txt", "ciphertext.txt");
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

void VigeneresCipher::generateCipherText(string keyname,string outputname, string inputname) {
    vector <string> keyvalues;
    ofstream fout(outputname.c_str());
    assert(fout.is_open());
    ifstream keyname_fin(keyname);
    assert(keyname_fin.is_open());
    ifstream inputname_fin(inputname);
    assert(inputname_fin.is_open());
    string keytext;
    string cipherText;
    string plaintext;
    getline(keyname_fin, keytext);
    getline(inputname_fin, plaintext);

    //Parse the string into a vector
    unsigned beginning = 0;
    unsigned counter = 1;
    for( unsigned i = 0 ; i < keytext.size() ; i++) {
        if (keytext.at(i) == ',') {
            keyvalues.push_back(keytext.substr(beginning, counter - 1));
            beginning = i + 1;
            counter = 0;
        }
        counter++;
    }
    keyvalues.push_back(keytext.substr(beginning, keytext.size()));

    for( unsigned i  = 0 ; i < plaintext.size() ; i++){
        if ( plaintext.at(i) != ' '){
            cipherText += getCipherCharacter(plaintext.at(i), keyvalues.at(i % keyvalues.size()));
        }
        else{
            cipherText += ' ';
        }
    }

    fout << cipherText << flush;

    keyname_fin.close();
    fout.close();
}

char VigeneresCipher::getCipherCharacter(char input, string keyvalue) {
    //cout << "input: " << input << endl << "keyvalue: " << stoi(keyvalue) << endl;
    for ( unsigned column = 1 ; column < WIDTH ; column++){
        //cout << table[stoi(keyvalue) + 1][column] << " " << (char)tolower(input) << endl;
        if( table[stoi(keyvalue) + 1][column][0] == (char)tolower(input)){
            //cout << table[stoi(keyvalue) + 1][column] << " " << to_string(tolower(input)) << endl;
            //to access the first item in the array to return a char
            return table[0][column + 1][0];
        }
    }
    return '~';
}

void VigeneresCipher::generatePlainText(string keyname,string outputname, string inputname) {
    vector <string> keyvalues;
    ofstream fout(outputname.c_str());
    assert(fout.is_open());
    ifstream keyname_fin(keyname);
    assert(keyname_fin.is_open());
    ifstream inputname_fin(inputname);
    assert(inputname_fin.is_open());
    string keytext;
    string cipherText;
    string plaintext;
    getline(keyname_fin, keytext);
    getline(inputname_fin, cipherText);

    //Parse the string into a vector
    unsigned beginning = 0;
    unsigned counter = 1;
    for( unsigned i = 0 ; i < keytext.size() ; i++) {
        if (keytext.at(i) == ',') {
            keyvalues.push_back(keytext.substr(beginning, counter - 1));
            beginning = i + 1;
            counter = 0;
        }
        counter++;
    }
    keyvalues.push_back(keytext.substr(beginning, keytext.size()));

    cout << keyvalues[0] << endl;
    cout << cipherText << endl;

    for( unsigned i  = 0 ; i < cipherText.size() ; i++){
        if ( cipherText.at(i) != ' '){
            plaintext += getPlainTextCharacter(cipherText.at(i), keyvalues.at(i % keyvalues.size()));
            cout << "____________________________________________" << endl;
        }
        else{
            plaintext += ' ';
        }
    }

    fout << plaintext << flush;

    keyname_fin.close();
    fout.close();
}

char VigeneresCipher::getPlainTextCharacter(char input, string keyvalue) {
    return toupper(table[stoi(keyvalue)][((int)tolower(input)) + 1 - LOWERCASE_a][0]);
}
