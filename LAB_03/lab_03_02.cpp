#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

struct Node{
    int value;
    Node* rson;
    Node* lson;
    int pred;
    string name;

    Node(int val) : value(val), rson(nullptr), lson(nullptr), name("") {}
};

void search_pred(Node* root, int count){
    root->pred = count;
    if (root->lson) search_pred(root->lson, count+1);
    if (root->rson) search_pred(root->rson, count+1);
}
void fill_levels(Node *node, vector<vector<string>>& levels, int depth, int pos, int width){
    if (node == nullptr) return;    

    //levels[depth][pos] = node->name;
    levels[depth][pos] = to_string(node->pred);
    int offset = width/2;
    if (offset > 0){
        fill_levels(node->lson, levels, depth+1, pos - offset, offset);
        fill_levels(node->rson, levels, depth+1, pos + offset, offset);
    }
}

void print_tree(Node *root){
    int depth = 5;
    int width = (1 << depth) - 1;
    vector<vector<string>> levels(depth, vector<string>(width, "-"));
    fill_levels(root, levels, 0, (width-1)/2, (width - 1)/2);

    for(int i = depth-1; i >= 0; i--){
        for(int j = 0; j < width; j++){
            cout << setw(3) << levels[i][j];
        }
        cout << endl;
    }
}

// void print_pred(Node* root){
//     cout << root->name << " : " << root->pred << " ancestors." << endl;
//     if (root->lson) print_pred(root -> lson);
//     if (root->rson) print_pred(root->rson);
// }

Node* insert(Node* root, int value){
    if (root == nullptr) return new Node(value);

    if (value < root->value){
        root->lson = insert(root->lson, value);
    }
    if (value > root->value){
        root->rson = insert(root->rson, value);
    }

    return root;
}

Node* MakeTree(Node* root, int node_count){
    int root_value;
    root_value = rand()%100;
    root = new Node(root_value);
    for(int i = 0; i < node_count; i++){
        int value = rand()%100;
        root = insert(root, value);
    }
    return root;
}

void enter_name_by_level(Node* root){
    if (root == nullptr) return;

    std::queue<Node*> q;
    std::stack<Node*> s;

    q.push(root);
    s.push(root);
    
    char current_name = 'A';

    while(!q.empty()){
        Node* node = q.front();
        q.pop();

        s.push(node);

        if (node->lson) q.push(node->lson);
        if (node->rson) q.push(node->rson);

    }

    while(!s.empty()){
        Node* node = s.top();
        s.pop();

        node->name = string(1, current_name++);
    }
}

int main(){
    srand(time(0));
    int count_node = 5 + rand()%10;

    Node* root = nullptr;
    root = MakeTree(root, count_node);
    search_pred(root, 0);
    enter_name_by_level(root);
    print_tree(root);
    return 0;
}