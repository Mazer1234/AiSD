#include <iostream>
#include <vector>
#include <typeinfo.h>
#include "list.h"
#define REPEAT_COUNT 1000000
using namespace std;


void Set::create_list_from_array()
{
    Sset *head = nullptr;
    Sset *tail = nullptr;
    for (int i = 0; i < this->num; i++)
    {
        Sset *newnode = new Sset{set[i], nullptr};
        if (head == nullptr)
        {
            head = newnode;
            head->next = tail;
        }
        else
        {
            tail->next = newnode;
        }
        tail = newnode;
    }
    this->head = head;
}

Sset *Set::check_key(Sset *head2, Sset *head3, Sset *head4)
{
    Sset *current1 = this->head;
    Sset *current2 = head2;
    Sset *current3 = head3;
    Sset *current4 = head4;
    Sset *set1_head = nullptr;
    Sset *set1_tail = nullptr;
    Sset *set2_head = nullptr;
    Sset *set2_tail = nullptr;
    Sset *set3_head = nullptr;
    Sset *set3_tail = nullptr;

    while (current1 != nullptr)
    {
        current2 = head2;
        while (current2 != nullptr)
        {
            if (current1->el == current2->el)
            {
                Sset *newNode = new Sset{current1->el, nullptr};
                if (set1_head == nullptr)
                {
                    set1_head = newNode;
                    set1_head->next = set1_tail;
                }
                else
                {
                    set1_tail->next = newNode;
                }
                set1_tail = newNode;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    while (current3 != nullptr)
    {
        current4 = head4;
        while (current4 != nullptr)
        {
            if (current3->el == current4->el)
            {
                Sset *newNode = new Sset{current3->el, nullptr};
                if (set2_head == nullptr)
                {
                    set2_head = newNode;
                    set2_head->next = set2_tail;
                }
                else
                {
                    set2_tail->next = newNode;
                }
                set2_tail = newNode;
            }
            current4 = current4->next;
        }
        current3 = current3->next;
    }
    Sset *current5 = set1_head;
    Sset *current6 = set2_head;
    while (current5 != nullptr)
    {
        current6 = set2_head;
        while (current6 != nullptr)
        {
            if (current5->el == current6->el)
            {
                Sset *newNode = new Sset{current5->el, nullptr};
                if (set3_head == nullptr)
                {
                    set3_head = newNode;
                    set3_head->next = set3_tail;
                }
                else
                {
                    set3_tail->next = newNode;
                }
                set3_tail = newNode;
            }
            current6 = current6->next;
        }
        current5 = current5->next;
    }
    return set3_head;
}

void Set::print_key()
{
    Sset *current = this->head;
    if (current == nullptr)
    {
        cout << "Error, set is empty" << endl;
    }
    else
    {
        cout << "Finish list: ";
        while (current != nullptr)
        {
            cout << current->el << " ";
            current = current->next;
        }
    }
    cout << endl;
} // finish list

void Set::setNum(int num){
    this->num = num;
}

void Set::setName(char name){
    this->name = name;
}

Sset *Set::getKey(){
    return this->head;
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
    create_list_from_array();
}

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

void Set::setHead(Sset *head){
    this->head = head;
}

void Set::timer(Sset *head2, Sset *head3, Sset *head4){
    int t1 = clock();
    for (int i = 0 ; i < REPEAT_COUNT; i++){
        check_key(head2, head3, head4);
    }
    int t2 = clock();
    double t = double(t2 - t1) / CLOCKS_PER_SEC;
    cout << "Time " << t << "*10(-5) sec" << endl;
}