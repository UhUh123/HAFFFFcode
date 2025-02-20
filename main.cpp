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
