#include <iostream>
#include "mword.h"
#include <vector>
#define REPEAT_COUNT 1000000
using namespace std;

void Set::setName(char name){
    this->name = name;
}

void Set::setNum(int num){
    this->num = num;
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
    fill_machine_word();
}

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

void Set::setHead(int arr){
    this->word = arr;
}

void Set::fill_machine_word()
{
    bool flag;
    for (int i = 0; i < this->num; i++)
    {
        for (int j = 0; j < sizeof(int) * 8; j++)
        {
            int result = int(this->set[i] - 96) & (1 << j);
            if (result)
            {
                this->word |= 1 << int(this->set[i] - 97);
            }
        }
    }
}

void Set::print_binar_long(int word)
{
    for (int i = (sizeof(int) * 8 - 1); i >= 0; i--)
    {
        int u1 = 1 << i;
        cout << ((word & u1) ? '1' : '0');
    }
    cout << endl;
}

int Set::getKey(){
    return this->word;
}

int Set::check_key(int b, int c, int d)
{
    int e = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < sizeof(int)*8; j++){
        int result = (1 << j);
        if ((word & result) && (result & c) && (result & b) && (result & d))
        {
            e |= word & result;
        }
        }
    }
    return e;
}

void Set::print_key()
{
    cout << "Words " << this->name << ": ";
    for (int i = 0; i < 26; i++)
    {
        if (this->word >> i & 1)
        {
            char a = i + 97;
            cout << a << " ";
        }
    }
    cout << endl;
}

void Set::timer(int b, int c , int d){
    int t1 = clock();
    for (int i = 0 ; i < REPEAT_COUNT; i++){
        check_key(b, c, d);
    }
    int t2 = clock();
    double t = double(t2 - t1) / CLOCKS_PER_SEC;
    cout << "Time " << t << "*10(-5) sec" << endl;
}