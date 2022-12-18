#include <iostream>
#include <stack>
#include <cassert>
#include <stdexcept>
#include "TransparentStack.h"

int main() {
    TransparentStack* ts = new TransparentStack;
    // Basic Test
    ts->push('a');
    ts->push('b');
    ts->push('c');
    ts->push('d');

    assert(ts->peek_at(2) == 'c');

    delete(ts);

    ts = new TransparentStack;

    // One Entry

    ts->push('j');

    assert(ts->peek_at(0) == 'j');

    try {

        // Invalid Entry

        ts->peek_at(8);
        assert(false);
    }
    catch (invalid_argument e) {
    
    }

    try {

        // Negative Entry

        ts->peek_at(-2);
        assert(false);
    }
    catch (invalid_argument e) {
    
    }



}