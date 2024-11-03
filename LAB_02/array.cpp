#include "array.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#define REPEAT_COUNT 1000000

bool Set::find_in_arr(char el, int num)
{ // array
    for (int i = 0; i < num; i++)
    {
        if (set[i] == el)
        {
            return false;
        }
    }
    return true;
}

void Set::create_array()
{
    char el;
    int flag;
    cout << "Let's fill " << name << " array!" << endl;
    do
    {
        cout << "Do you want random generation or hand work?(1/0): ";
        cin >> flag;
        if (flag != 0 && flag != 1)
        {
            cout << "Try again" << endl;
        }
    } while (flag != 0 && flag != 1);
    for (int i = 0; i < num; i++)
    {
        if (flag == 0)
        {
            cout << "Enter " << i << " element: ";
            cin >> el;
        }
        else if (flag == 1)
        {
            el = rand() % ('z' - 'a' + 1) + 'a';
            cout << el << endl;
        }
        if (find_in_arr(el, i) && isalpha(el) && isupper(el) == 0)
        {
            set.push_back(el);
        }
        else
        {
            if (!find_in_arr(el, i))
            {
                cout << "This element already stay in set. Please try again" << endl;
            }
            else
            {
                cout << "Please, enter the small latin symbol, try agai." << endl;
            }
            i--;
        }
    }
}

void Set::setName(char name){
    this->name = name;
}

void Set::setNum(int num){
    this->num = num;
}

vector<char> Set::getKey(){
    return this->set;
}

vector<char> Set::check_key(vector<char> b, vector<char> c, vector<char> d)
{
    vector<char> e;
    char e1[num], e2[num];
    int flag = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (this->set[i] == b[j])
            {
                e1[flag] = this->set[i];
                flag++;
            }
        }
    }
    flag = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (c[i] == d[j])
            {
                e2[flag] = c[i];
                flag++;
            }
        }
    }
    flag = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (e1[i] == e2[j])
            {
                e.push_back(e1[i]);
                flag++;
            }
        }
    }

    return e;
} // array finish

void Set::print_key()
{
    cout << "Finish array: ";
    for (int i = 0; i < num; i++)
    {
        if (isalpha(set[i]) && set[i] >= 96)
        {
            cout << set[i];
        }
    }
    cout << endl;
}

void Set::setHead(vector<char> a){
    this->set = a;
}
void Set::timer(vector<char> b, vector<char> c, vector<char> d){
    int t1 = clock();
    for (int i = 0 ; i < REPEAT_COUNT; i++){
        check_key(b, c, d);
    }
    int t2 = clock();
    double t = double(t2 - t1) / CLOCKS_PER_SEC;
    cout << "Time " << t << "*10(-5) sec" << endl;
}

Set::~Set(){
    cout << "Set destroyed"<< endl;
}

Set::Set(){
    cout << "Set created" << endl;
}