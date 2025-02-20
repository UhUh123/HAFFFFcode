#define _CRT_SECURE_NO_WARNINGS
#include "haff.h"
#include <iostream>
#include <map>
#include <vector>
using namespace std;

/*
g++ main.cpp haff.cpp -o main
*/

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string filename = "input.txt"; // файл с текстом
    string outputFilename = filename; // файл куда записывается сжатые данные
    string decodedFilename = "output.txt"; // файл с расшифрованным текстом
    vector<unsigned long> freq(256, 0);

    // 1.
    PodschetChastot(filename, freq);

    // 3.
    Node* head = SortChastot(freq);
    // 4. 
    Node* root = MakeHaffTree(head);

    // 5. 
    map<unsigned char, vector<bool>> codesTable;
    vector<bool> code;
    GetCodeForSymbFromTreee(root, code, codesTable);

    // 6.
    string encodedString = SringWithNewCode(filename, codesTable);

    // 7. 
    int tail = 0;
    vector<char> encodedBytes = GenerateTextFromNewCode(encodedString, tail);

    // 8. 
    WriteNewTextInOutFile(filename, tail, encodedBytes);

    // Декодирование
    Decoding(outputFilename, decodedFilename, root);

    return 0;
}