#include <vector>
#include <cstring>
#include <iostream>
#include "SingleLinkedList.h"
using namespace std;

int main() {

    SingleLinkedList<int> list;
    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);
    list.atInsert(0, 0);
    list.show();
    list.atRemove(1);
    list.show();
    cout << "Found: " << list.search(1) << endl;
    return 0;
}