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
