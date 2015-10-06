#include <iostream>

#include "AVLTree.h"

using namespace std;

int main() {
    AVLTree t;

    int value;
    for(value = 0; value < 20; value++) {
        t.Insert(value); t.Print();
    }
    /*t.Insert(1); t.Print();
    t.Insert(0); t.Print();
    t.Insert(4); t.Print();
    t.Insert(3); t.Print();
    t.Insert(5); t.Print();
    t.Insert(2); t.Print();*/

    return 0;
}
