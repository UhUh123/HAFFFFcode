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
union BIT2CHAR {
    char symb;
    struct {
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
        unsigned b8 : 1;
    } mbit;
};

void PodschetChastot(const string& filename, vector<unsigned long>& freq);

void Add2List(Node*& head, Node* newNode);

Node* SortChastot(const vector<unsigned long>& freq);

Node* NewUzliForTree(Node* left, Node* right);

Node* MakeHaffTree(Node*& head);

void GetCodeForSymbFromTreee(Node* root, vector<bool>& code, map<unsigned char, vector<bool>>& codesTable);