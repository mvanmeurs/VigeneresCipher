//
// Created by CSchumacker on 4/1/2020.
//

#include <iostream>
#include <vector>
#include <stdexcept>

#ifndef VIGENERES_CIPHER_MENU_H
#define VIGENERES_CIPHER_MENU_H

using namespace std;

class Menu {
public:
    Menu();

private:
    void printOptions() const;
    static bool isLegal(const string&);
    static void generateKey(const string& basicString);
    static bool isValidFileName(const string&);
    vector<string> extractOperations(const string&);
    static void checkCommand(const string&);
};


#endif //VIGENERES_CIPHER_MENU_H
