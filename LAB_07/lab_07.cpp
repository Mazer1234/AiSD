#include <iostream>
#include <vector>
#include "SetContainer.h"

int main(){
    SetContainer A, B, C, D, E;

    for (int i = 1; i <= 4; i++){
        A.insert(i);
    }
    for (int i = 2; i <= 4; i++){
        B.insert(i);
    }
    for (int i = 1; i <= 5; i++){
        C.insert(i);
    }
    for (int i = 1; i <= 6; i++){
        D.insert(i);
    }
    for (int i = 3; i <= 5; i++){
        E.insert(i);
    }

    cout << "A :";
    A.printSet();
    cout << "B :";
    B.printSet();
    cout << "C :";
    C.printSet();
    cout << "D :";
    D.printSet();
    cout << "E :";
    E.printSet();

    SetContainer BC = B.intersection(C);
    std::cout << "B and C: ";
    BC.printSet();

    SetContainer AB_C = A.unionSet(BC);
    std::cout << "A + (B and C): ";
    AB_C.printSet();

    SetContainer AB_C_D = AB_C.difference(D);
    std::cout << "(A + (B and C)) \\ D: ";
    AB_C_D.printSet();

    SetContainer finalResult = AB_C_D.intersection(E);
    std::cout << "Final Result: ";
    finalResult.printSet();


    A.setValues(A.erase(1, 2));
    A.printSet();

    B.setValues(B.subst(C.getValues(), 3));
    B.printSet();

    C.setValues(C.change(E.getValues(), 0));
    C.printSet();
    return 0;
}