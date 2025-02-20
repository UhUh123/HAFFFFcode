#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <sstream>
#include <cstdint>
#include <map>
#include "haff.h"

using namespace std;

const int BIT8 = 8;

/*
    ШАГ 1:
*/

void PodschetChastot(const string& filename, vector<unsigned long>& freq) {
    ifstream fr(filename, ios::binary);
    if (!fr.is_open()) {
        cout << "не удалось открыть файл: " << filename << endl;
        return;
    }

    fr.seekg(0, ios::end);
    streamoff length = fr.tellg();
    fr.seekg(0, ios::beg);

    for (streamoff i = 0; i < length; ++i) {
        unsigned char c = fr.get(); 
        if (fr.good()) {
            freq[c]++;
        }
    }

    fr.close();
}
