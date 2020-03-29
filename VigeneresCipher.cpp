//
// Created by mason on 3/28/2020.
//

#include <iostream>
#include "VigeneresCipher.h"

VigeneresCipher::VigeneresCipher() {
    initTable();
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

    printTable();

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
