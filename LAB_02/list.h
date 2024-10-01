#include <iostream>
#include <vector>
using namespace std;

struct Sset // list
    {
    char el;
    Sset *next;
    };

class Set{
    
    private:
    char name;
    int num;
    Sset *head;
    vector<char> set;

    public:
    void create_list_from_array();
    Sset *check_key(Sset *head2, Sset *head3, Sset *head4);
    void print_key();
    void setNum(int num);
    void setName(char name);
    void setHead(Sset *head);
    Sset* getKey();
    void create_array();
    bool find_in_arr(char el, int num);
    void timer(Sset *head2, Sset *head3, Sset *head4);
};