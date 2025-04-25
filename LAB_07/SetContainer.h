#include <vector>

using namespace std;

struct Node{
    int value;
    Node* left;
    Node* right;
};

class SetContainer{
    private:
        Node* root;
        Node* insertRecursive(Node* node, int value);
        bool findRecursive(Node* node, int value) const;
        Node* removeRecursive(Node* node, int value);
        Node* findMin(Node* node) const;
        vector<int> values;
    public:
        SetContainer() : root(nullptr){}

        void insert(int value);
        bool find(int value) const;
        void remove(int value);
        SetContainer unionSet(const SetContainer& other) const;
        SetContainer intersection(const SetContainer& other) const;
        SetContainer difference(const SetContainer& other) const;
        Node* getRoot();
        void printSet();
        vector<int> getValues() const;
        vector<int> erase(int start, int end);
        void setValues(vector<int> values);
        vector<int> subst(const vector<int>& B, int pos);
        vector<int> change( const vector<int>& B, int pos);
};