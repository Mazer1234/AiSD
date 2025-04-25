#include "SetContainer.h"
#include <iostream>

using namespace std;

void SetContainer::insert(int value){
    root = insertRecursive(this->root, value);
}

Node* SetContainer::insertRecursive(Node* node, int value){
    if (node == nullptr){
        node = new Node();
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        this->values.push_back(value);
        return node;
    }

    if (value < node->value){
        node->left = insertRecursive(node->left, value);
    }else if (value > node->value){
        node->right = insertRecursive(node->right, value);
    }

    return node; // Удаляем этот вызов, так как он добавляет значение в вектор даже если оно уже существует
}

vector<int> SetContainer::erase(int start, int end) {
    vector<int> result;
    result.insert(result.end(), this->values.begin(), this->values.begin() + start);
    result.insert(result.end(), this->values.begin() + end + 1, this->values.end());
    return result;
}

vector<int> SetContainer::subst(const vector<int>& B, int pos) {
    vector<int> result;
    result.insert(result.end(), this->values.begin(), this->values.begin() + pos);
    result.insert(result.end(), B.begin(), B.end());
    result.insert(result.end(), this->values.begin() + pos, this->values.end());
    return result;
}

vector<int> SetContainer::change(const vector<int>& B, int pos) {
    if (pos + B.size() > this->values.size()) {
        cerr << "Error: Out of bounds" << endl;
        return this->values;
    }
    
    vector<int> result = this->values;
    copy(B.begin(), B.end(), result.begin() + pos);
    return result;
}

Node* SetContainer::getRoot(){
    return this->root;
}

bool SetContainer::find(int value) const{
    return findRecursive(root, value);
}

bool SetContainer::findRecursive(Node* node, int value) const{
    if (node == nullptr){
        return false;
    }
    if (value == node->value){
        return true;
    }
    if (value < node->value){
        return findRecursive(node->left, value);
    }else{
        return findRecursive(node->right, value);
    }
}

void SetContainer::remove(int value){
    root = removeRecursive(root, value);
}

Node* SetContainer::removeRecursive(Node* node, int value){
    if (node == nullptr){
        return nullptr;
    }

    if (value < node->value){
        node->left = removeRecursive(node->left, value);
    }else if (value > node->value){
        node->right = removeRecursive(node->right, value);
    }else{
        if (node->left == nullptr && node->right == nullptr){
            delete node;
            return nullptr;
        }else if (node->left == nullptr){
            Node* temp = node->right;
            delete node;
            return temp;
        }else{
            Node* minNode = findMin(node->right);
            node->value = minNode->value;
            node->right = removeRecursive(node->right, minNode->value);
        }
    }
    return node;
}

Node* SetContainer::findMin(Node* node) const{
    while (node->left != nullptr){
        node = node->left;
    }
    return node;
}

vector<int> SetContainer::getValues() const{
    return this->values;
}

SetContainer SetContainer::unionSet(const SetContainer& other) const {
    SetContainer result;
    for (int value : this->values) {
        if (!(this->find(value) && other.find(value))){
            result.insert(value);
        }
    }
    for (int value : other.getValues()) {
        if (!(this->find(value) && other.find(value))){
            result.insert(value);
        }
    }
    return result;
}

SetContainer SetContainer::intersection(const SetContainer& other) const {
    SetContainer result;
    for (int value : this->values) {
        if (other.find(value)) {
            result.insert(value);
        }
    }
    return result;
}

SetContainer SetContainer::difference(const SetContainer& other) const {
    SetContainer result;
    for (int value : this->values) {
        if (!other.find(value)) {
            result.insert(value);
        }
    }
    return result;
}

void SetContainer::printSet(){
    if (this->root == nullptr){
        cout << "Set is empty" << endl;
        return;
    }
    cout << "{";
    for (size_t i = 0; i < this->values.size(); i++){
        cout << " " << values[i];
        if (i < this->values.size() - 1) {
            cout << ",";
        }
    }
    cout << " }" << endl;
}

void SetContainer::setValues(vector<int> values){
    this->values = values;
}