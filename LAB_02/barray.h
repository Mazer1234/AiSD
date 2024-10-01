#include <iostream>
#include <vector>
using namespace std;

class Set{
    private:
    char name;
    int num;
    vector<bool> bits;
    vector<char> set;

    public:
    bool find_in_arr(char el, int num);
    void setNum(int num);
    void setName(char name);
    void setHead(vector<bool> e);
    vector<bool> getKey();
    void create_array();
    void find_bool();
    void print_key();
    vector<bool> check_key(vector<bool> b, vector<bool> c, vector<bool> d);
    void timer(vector<bool> b, vector<bool> c, vector<bool> d);
};