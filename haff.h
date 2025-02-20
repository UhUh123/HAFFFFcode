#ifndef HAFFH
#define HAFFH

#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <sstream>
#include <cstdint>
#include <map>
using namespace std;

struct Node {
    unsigned char symb;
    bool isSymb;             
    unsigned int freq;       
    vector<bool> code;  
    int level;               
    Node* left, * right, * next;              

    Node(unsigned char s, unsigned int f, bool isSymb = true)
        : symb(s), freq(f), isSymb(isSymb), level(0), left(nullptr), right(nullptr), next(nullptr) {
    }
};
