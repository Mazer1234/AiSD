#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

class Set{
    private:
    char name;
    int num;
    vector<char> set;
    TimePoint start_timer, end_timer;

    public:
    void setName(char name);
    void setNum(int num);
    vector<char> getKey();
    bool find_in_arr(char el, int num);
    void create_array();
    vector<char> check_key(vector<char> b, vector<char> c, vector<char> d);
    void print_key();
    void setHead(vector<char> a);
    void timer(vector<char> b, vector<char> c, vector<char> d);
};