#include <iostream>
#include <vector>
#include <time.h>
#include "barray.h"
#define REPEAT_COUNT 1000000
using namespace std;

bool Set::find_in_arr(char el, int num)
{ // array
    for (int i = 0; i < num; i++)
    {
        if (this->set[i] == el)
        {
            return false;
        }
    }
    return true;
}

void Set::setNum(int num){
    this->num = num;
}

void Set::setName(char name){
    this->name = name;
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
            this->set.push_back(el);
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
    find_bool();
}

void Set::find_bool(){
    for (int i = 1; i <= 26; i++)
    {
        this->bits.push_back(0);
        for (int j = 0; j < num; j++)
        {
            if (this->set[j] == i + 96)
            {
                this->bits[i - 1] = 1;
            }
            else if(this->bits[i-1] != 1)
            {
                this->bits[i - 1] = 0;
            }
        }
    }
}

vector<bool> Set::check_key(vector<bool> b, vector<bool> c, vector<bool> d)
{
    vector<bool> e(26, 0);
    for (int i = 0; i < 26; i++)
    {
        if (this->bits[i] == 1 && b[i] == 1 && c[i] == 1 && d[i] == 1)
        {
            e[i] = 1;
        }
        else
        {
            e[i] = 0;
        }
    }
    return e;
}

void Set::setHead(vector<bool> e){
    this->bits = e;
}

vector<bool> Set::getKey(){
    return this->bits;
}

void Set::print_key()
{
    char a;
    cout << "Finish array of bits: ";
    for (int i = 1; i <= 26; i++)
    {
        if (this->bits[i-1])
        {
            a = i + 96;
            cout << a << " ";
        }
    }
}

void Set::timer(vector<bool> b, vector<bool> c, vector<bool> d){
    int t1 = clock();
    for (int i = 0 ; i < REPEAT_COUNT; i++){
        check_key(b, c, d);
    }
    int t2 = clock();
    double t = double(t2 - t1) / CLOCKS_PER_SEC;
    cout << "Time " << t << "*10(-5) sec" << endl;
}