#ifndef TRANS_STACK
#define TRANS_STACK

#include <iostream>
#include <climits>
#include <stack>
#include <vector>

using namespace std;

class TransparentStack : public stack<char,vector<char>>::stack {

    public:
        char peek_at(int index);

};

#endif