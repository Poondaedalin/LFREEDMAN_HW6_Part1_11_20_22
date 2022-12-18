#include "TransparentStack.h"
#include <stdexcept>
#include <climits>

char TransparentStack::peek_at(int idx) {

    if (idx > static_cast<int>(size()) && idx < 0) {
        throw invalid_argument("Function must take in a valid index! " + to_string(idx) + " is not valid.");
    }

    vector<char> temp;
    char output;
    for (int i = 0; i < idx; i++) {
        temp.push_back(top());
        pop();
    }
        output = top();
        for (char c : temp) {
            push(c);
        }
        return output;
    }