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
/*
    ШАГ 2:
*/

void Add2List(Node*& head, Node* newNode) {
    if (!head || newNode->freq < head->freq) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next && current->next->freq <= newNode->freq) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

/*
    ШАГ 3:
*/

Node* SortChastot(const vector<unsigned long>& freq) {
    Node* head = nullptr;

    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            Add2List(head, new Node(static_cast<unsigned char>(i), freq[i]));
        }
    }
    return head;
}

/*
    ШАГ 4:
*/

Node* NewUzliForTree(Node* left, Node* right) {
    Node* res = new Node(0, left->freq + right->freq, false);
    res->left = left;
    res->right = right;
    res->next = nullptr;
    return res;
}

Node* MakeHaffTree(Node*& head) {
    while (head && head->next) {
        Node* left = head;
        Node* right = head->next;

        head = head->next->next;
        Add2List(head, NewUzliForTree(left, right));
    }
    return head;
}

/*
    ШАГ 5:
*/

void GetCodeForSymbFromTreee(Node* root, vector<bool>& code, map<unsigned char, vector<bool>>& codesTable) {
    if (!root) return;

    if (root->isSymb) {
        codesTable[root->symb] = code;
    }

    if (root->left) {
        code.push_back(0);
        GetCodeForSymbFromTreee(root->left, code, codesTable);
        code.pop_back();
    }

    if (root->right) {
        code.push_back(1);
        GetCodeForSymbFromTreee(root->right, code, codesTable);
        code.pop_back();
    }
}
/*
    ШАГ 6:
*/

string SringWithNewCode(const string& filename, const map<unsigned char, vector<bool>>& codesTable) {
    ifstream fr(filename, ios::binary);
    string encodedString;
    unsigned char c;

    while (fr.read(reinterpret_cast<char*>(&c), sizeof(c))) {
        if (codesTable.find(c) != codesTable.end()) {
            const vector<bool>& code = codesTable.find(c)->second;
            for (unsigned long i = 0; i < code.size(); ++i) {
                encodedString.push_back('0' + code[i]);
            }
        }
    }
    fr.close();
    return encodedString;
}

/*
    ШАГ 7:
*/

vector<char> GenerateTextFromNewCode(const string& bitString, int& tail) {
    int count = bitString.length() / BIT8;
    tail = bitString.length() % BIT8;
    int len = count + (tail > 0);

    vector<char> res(len);
    BIT2CHAR symb;

    for (int i = 0; i < count; ++i) {
        symb.mbit.b1 = bitString[i * BIT8 + 0] - '0';
        symb.mbit.b2 = bitString[i * BIT8 + 1] - '0';
        symb.mbit.b3 = bitString[i * BIT8 + 2] - '0';
        symb.mbit.b4 = bitString[i * BIT8 + 3] - '0';
        symb.mbit.b5 = bitString[i * BIT8 + 4] - '0';
        symb.mbit.b6 = bitString[i * BIT8 + 5] - '0';
        symb.mbit.b7 = bitString[i * BIT8 + 6] - '0';
        symb.mbit.b8 = bitString[i * BIT8 + 7] - '0';
        res[i] = symb.symb;
    }

    if (tail > 0) {
        symb.symb = 0;
        for (int i = 0; i < tail; ++i) {
            symb.symb = symb.symb || (bitString[count * BIT8 + i] - '0') << i;
        }
        res[count] = symb.symb;
    }

    return res;
}

/*
    ШАГ 8:
*/

void WriteNewTextInOutFile(const string& outputFilename, int tail, const vector<char>& encodedBytes) {
    ofstream outFile(outputFilename, ios::binary);
    if (!outFile.is_open()) {
        cout << "Не удалось открыть файл для записи:" << outputFilename << endl;
        return;
    }

    char tailChar = static_cast<char>(tail);
    outFile.write(&tailChar, sizeof(tailChar));

    outFile.write(encodedBytes.data(), encodedBytes.size());
    outFile.close();

    cout << "Запись файла успешна: " << outputFilename << endl;
}

