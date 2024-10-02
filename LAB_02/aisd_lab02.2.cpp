#include "array.h"
//#include "list.h"
//#include "barray.h"
//#include "mword.h"
#include <iostream>
#define REPEAT_COUNT 1000000;

int main(){
    Set A, B, C, D , E;
    int num;

    cout << "How much elements will be in the sets: ";
    cin >> num;

    cout << "------------\nARRAY" << endl;
    A.setName('A');
    A.setNum(num);
    A.create_array();
    B.setName('B');
    B.setNum(num);
    B.create_array();
    C.setName('C');
    C.setNum(num);
    C.create_array();
    D.setName('D');
    D.setNum(num);
    D.create_array();

    E.setName('E');
    E.setNum(num);

    E.setHead(A.check_key(B.getKey(), C.getKey(), D.getKey()));
    E.print_key();
    A.timer(B.getKey(), C.getKey(), D.getKey());

    return 0;
}