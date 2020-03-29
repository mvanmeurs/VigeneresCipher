//
// Created by mason on 3/28/2020.
//
#include <iostream>

#ifndef VIGENERES_CIPHER_VIGENERESCIPHER_H
#define VIGENERES_CIPHER_VIGENERESCIPHER_H

const int HEIGHT = 26;
const int WIDTH = 27;
const int UPPERCASE_A = 65;
const int LOWERCASE_a = 97;
const int SIZE_OF_ALPHABET = 26;

using namespace std;

class VigeneresCipher {

public:
    VigeneresCipher();
private:
    void initTable();
    void printTable();
    void generateKey(int, string);
    //TODO: pass by reference for generateKey?
    void generateCipherText(string, string, string);
    char getCharacter(char, string);
    string table[HEIGHT][WIDTH];
};


#endif //VIGENERES_CIPHER_VIGENERESCIPHER_H
