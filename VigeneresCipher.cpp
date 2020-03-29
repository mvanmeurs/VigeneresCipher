//
// Created by mason on 3/28/2020.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <iterator>
#include "VigeneresCipher.h"

VigeneresCipher::VigeneresCipher() {
    initTable();
    //generateKey(4, "key.txt");
    generateCipherText("key.txt", "cipher.txt");
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
        fout << (rand()%26) + 1;
        if( i < length -1){fout << ",";}
    }
    fout.close();
}

void VigeneresCipher::generateCipherText(string keyname,string outputname) {
    vector <string> keyvalues;
    ofstream fout(outputname.c_str());
    assert(fout.is_open());
    ifstream fin(keyname);
    assert(fin.is_open());
    string keytext;
    getline(fin, keytext);

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
    cout << keyvalues.at(0) << endl;
    cout << keyvalues.at(1) << endl;
    cout << keyvalues.at(2) << endl;
    cout << keyvalues.at(3) << endl;

    fin.close();
    fout.close();
}
