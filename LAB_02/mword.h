#include <iostream>
#include <vector>
using namespace std;

class Set{
    private:
    char name;
    int num;
    vector<char> set;
    int word = 0;

    public:
    void setNum(int num);
    void setName(char name);
    void setHead(int arr);
    void create_array();
    int getKey();
    bool find_in_arr(char el, int num);
    void fill_machine_word();
    int check_key(int b, int c, int d);
    void print_key();
    void print_binar_long(int word);
    void timer(int b, int c , int d);
};