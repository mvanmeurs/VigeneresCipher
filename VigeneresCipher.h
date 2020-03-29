//
// Created by mason on 3/28/2020.
//
#include <iostream>

#ifndef VIGENERES_CIPHER_VIGENERESCIPHER_H
#define VIGENERES_CIPHER_VIGENERESCIPHER_H

const int HEIGHT = 26;
const int WIDTH = 27;
const int UPPERCASE_A = 65;
const int ZERO = 48;

using namespace std;

class VigeneresCipher {
public:
    VigeneresCipher();

private:
    void initTable();
    string table[HEIGHT][WIDTH];
    void printTable();
};


#endif //VIGENERES_CIPHER_VIGENERESCIPHER_H
