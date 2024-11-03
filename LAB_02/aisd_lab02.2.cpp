#include "array.h"
//#include "list.h"
//#include "barray.h"
//#include "mword.h"
#include <iostream>
#include <algorithm>
#define REPEAT_COUNT 1000000;

int main(){
    Set A, B, C, D , E;
    vector<int> num{0, 0, 0, 0};
    int num1, num2, num3, num4;

    for(int i=0; i < 4; i++){
        cout << "Enter count of elements in " << i << ":";
        cin >> num[i];
    }
    sort(begin(num), end(num));
    num1 = num[3];
    num2 = num[2];
    num3 = num[1];
    num4 = num[0];
    cout << "------------\nARRAY" << endl;
    A.setName('A');
    A.setNum(num1);
    A.create_array();
    B.setName('B');
    B.setNum(num2);
    B.create_array();
    C.setName('C');
    C.setNum(num3);
    C.create_array();
    D.setName('D');
    D.setNum(num4);
    D.create_array();

    E.setName('E');
    E.setNum(num1);

    E.setHead(A.check_key(B.getKey(), C.getKey(), D.getKey()));
    cout << "-------" << endl;
    A.print_key();
    B.print_key();
    C.print_key();
    D.print_key();
    E.print_key();
    A.timer(B.getKey(), C.getKey(), D.getKey());

    return 0;
}