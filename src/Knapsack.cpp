#include "Knapsack.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

Knapsack::Knapsack(int caseindex) {
    ifstream input;
    string prefix = "../data/p";
    string tmp = to_string(caseindex);
    if (caseindex < 10) prefix += '0';
    prefix += tmp;
    char suffix[4] = { 'c', 'p', 'w', 's' };
    for (int i = 0; i < NUM_OF_FILE; i++) {
        string file = prefix + '_' + suffix[i] + ".txt";
        input.open(file);
        if (input.fail()) {
            cout << "File " << file << " does not exist!" << endl;
            exit(0);
        }
        int index = 0;
        switch (suffix[i]) {
        case 'c': input >> c; break;
        case 'p':
            while (input >> item[index++].p);
            num = index - 1;
            break;
        case 'w':
            while (input >> item[index++].w);
            break;
            //case 's':
        default:
            break;
        }
        input.close();
    }
    for (int i = 0; i < num; i++)
        item[i].index = i;
}//构造函数，输入

void Knapsack::printinfo() const {
    cout << "c:" << c << "\tnum:" << num << endl;
    cout << "index:\t";
    for (int i = 0; i < num;i++) {
        cout << item[i].index << " ";
    }
    cout << endl;
    cout << "p:\t";
    for (int i = 0; i < num;i++) {
        cout << item[i].p << " ";
    }
    cout << endl;
    cout << "w:\t";
    for (int i = 0; i < num;i++) {
        cout << item[i].w << " ";
    }
    cout << endl;
}//打印当前背包信息