#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <chrono>
#include <fstream>
#include <random>
#include <numeric>
using namespace std;
using namespace std::chrono;

// Класс последовательности
template <typename T>
class Sequence {
private:
    vector<T> elements;

public:
    Sequence(const vector<T>& elems = {}) : elements(elems) {}

    const vector<T>& getElements() const {
        return elements;
    }

    size_t size() const {
        return elements.size();
    }

    T operator[](size_t index) const {
        if (index >= elements.size()) {
            throw out_of_range("Index out of range");
        }
        return elements[index];
    }

    // Операция замены подпоследовательности
    Sequence<T> SUBST(const Sequence<T>& other, size_t pos) const {
        if (pos > elements.size()) {
            throw out_of_range("Position out of range");
        }
    
        vector<T> newElements = elements;
        
        // Удаляем только столько элементов, сколько есть в заменяющей последовательности
        // size_t erase_count = min(other.size(), elements.size() - pos);
        // newElements.erase(newElements.begin() + pos, newElements.begin() + pos + erase_count);
        
        // Вставляем новую последовательность
        newElements.insert(newElements.begin() + pos, other.getElements().begin(), other.getElements().end());
        
        return Sequence<T>(newElements);
    }

    // Операция удаления подпоследовательности
    Sequence<T> ERASE(size_t start, size_t end) const {
        if (start >= elements.size() || end >= elements.size() || start > end) {
            throw out_of_range("Invalid range");
        }

        vector<T> newElements = elements;
        newElements.erase(newElements.begin() + start, newElements.begin() + end + 1);
        
        return Sequence<T>(newElements);
    }

    Sequence<T> CHANGE(const Sequence<T>& other, size_t pos) const {
        if (pos > elements.size()) {
            throw out_of_range("Position out of range");
        }
    
        vector<T> newElements = elements;
        
        // Удаляем только столько элементов, сколько есть в заменяющей последовательности
        size_t erase_count = min(other.size(), elements.size() - pos);
        newElements.erase(newElements.begin() + pos, newElements.begin() + pos + erase_count);
        
        // Вставляем новую последовательность
        newElements.insert(newElements.begin() + pos, other.getElements().begin(), other.getElements().end());
        
        return Sequence<T>(newElements);
    }

    // Вывод последовательности
    friend ostream& operator<<(ostream& os, const Sequence<T>& seq) {
        os << "<";
        for (size_t i = 0; i < seq.elements.size(); ++i) {
            if (i != 0) os << ", ";
            os << seq.elements[i];
        }
        os << ">";
        return os;
    }
};

// Класс узла 1-2-дерева
template <typename T>
class TreeNode {
public:
    T key;
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
    int height;

    TreeNode(T k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Класс 1-2-дерева
template <typename T>
class OneTwoTree {
private:
    shared_ptr<TreeNode<T>> root;

    int getHeight(shared_ptr<TreeNode<T>> node) const {
        return node ? node->height : 0;
    }

    void updateHeight(shared_ptr<TreeNode<T>> node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    shared_ptr<TreeNode<T>> rotateRight(shared_ptr<TreeNode<T>> y) {
        auto x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    shared_ptr<TreeNode<T>> rotateLeft(shared_ptr<TreeNode<T>> x) {
        auto y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    shared_ptr<TreeNode<T>> balance(shared_ptr<TreeNode<T>> node) {
        if (!node) return nullptr;

        updateHeight(node);

        if (getHeight(node->left) - getHeight(node->right) == 2) {
            if (getHeight(node->left->right) > getHeight(node->left->left)) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (getHeight(node->right) - getHeight(node->left) == 2) {
            if (getHeight(node->right->left) > getHeight(node->right->right)) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    shared_ptr<TreeNode<T>> insert(shared_ptr<TreeNode<T>> node, T key) {
        if (!node) return make_shared<TreeNode<T>>(key);

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node; // Дубликаты не допускаются
        }

        return balance(node);
    }

    shared_ptr<TreeNode<T>> erase(shared_ptr<TreeNode<T>> node, T key) {
        if (!node) return nullptr;
        
        if (key < node->key) {
            node->left = erase(node->left, key);
        } else if (key > node->key) {
            node->right = erase(node->right, key);
        } else {
            // Нашли узел для удаления
            if (!node->left || !node->right) {
                return node->left ? node->left : node->right;
            } else {
                // Узел с двумя потомками: находим минимальный в правом поддереве
                auto minNode = node->right;
                while (minNode->left) minNode = minNode->left;
                node->key = minNode->key;
                node->right = erase(node->right, minNode->key);
            }
        }
        return balance(node);
    }

    void inOrderTraversal(shared_ptr<TreeNode<T>> node, vector<T>& result) const {
        if (!node) return;
        inOrderTraversal(node->left, result);
        result.push_back(node->key);
        inOrderTraversal(node->right, result);
    }

public:
    OneTwoTree() : root(nullptr) {}

    void insert(T key) {
        root = insert(root, key);
    }

    void erase(T key) {
        root = erase(root, key);
    }

    bool contains(T key) const {
        auto current = root;
        while (current) {
            if (key == current->key) return true;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    vector<T> toVector() const {
        vector<T> result;
        inOrderTraversal(root, result);
        return result;
    }

    size_t size() const {
        return toVector().size();
    }

    // Операции с последовательностями
    static OneTwoTree<T> merge(const OneTwoTree<T>& a, const OneTwoTree<T>& b) {
        OneTwoTree<T> result;
        auto vecA = a.toVector();
        auto vecB = b.toVector();
        vector<T> merged;
        merge(vecA.begin(), vecA.end(), vecB.begin(), vecB.end(), back_inserter(merged));
        for (const auto& item : merged) {
            result.insert(item);
        }
        return result;
    }

    static OneTwoTree<T> concat(const OneTwoTree<T>& a, const OneTwoTree<T>& b) {
        OneTwoTree<T> result = a;
        auto vecB = b.toVector();
        for (const auto& item : vecB) {
            result.insert(item);
        }
        return result;
    }

    void change(T oldKey, T newKey) {
        if (contains(oldKey) && !contains(newKey)) {
            erase(oldKey);
            insert(newKey);
        } else {
            throw invalid_argument("Невозможно заменить ключ");
        }
    }
};

// Операции с множествами
template <typename T>
OneTwoTree<T> symmetricDifference(const OneTwoTree<T>& a, const OneTwoTree<T>& b) {
    OneTwoTree<T> result;
    auto vecA = a.toVector();
    auto vecB = b.toVector();
    
    auto itA = vecA.begin();
    auto itB = vecB.begin();
    
    while (itA != vecA.end() && itB != vecB.end()) {
        if (*itA < *itB) {
            result.insert(*itA);
            ++itA;
        } else if (*itB < *itA) {
            result.insert(*itB);
            ++itB;
        } else {
            ++itA;
            ++itB;
        }
    }
    
    while (itA != vecA.end()) {
        result.insert(*itA);
        ++itA;
    }
    
    while (itB != vecB.end()) {
        result.insert(*itB);
        ++itB;
    }
    
    return result;
}

template <typename T>
OneTwoTree<T> setUnion(const OneTwoTree<T>& a, const OneTwoTree<T>& b) {
    return OneTwoTree<T>::concat(a, b);
}

template <typename T>
OneTwoTree<T> setIntersection(const OneTwoTree<T>& a, const OneTwoTree<T>& b) {
    OneTwoTree<T> result;
    auto vecA = a.toVector();
    for (const auto& item : vecA) {
        if (b.contains(item)) {
            result.insert(item);
        }
    }
    return result;
}

// Функция для генерации случайного множества заданного размера
OneTwoTree<int> generateRandomSet(int size) {
    OneTwoTree<int> set;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, size * 10); // Диапазон значений больше размера множества
    
    while (set.size() < static_cast<size_t>(size)) {
        set.insert(dis(gen));
    }
    return set;
}

int main() {

    // Пример использования новых операций с последовательностями
    Sequence<int> A({5, 3, 2, 4, 6, 7, 9, 1});
    Sequence<int> B({6, 7, 9});

    // A.SUBST(B, 3) → <5, 3, 2, 6, 7, 9, 4, 6, 7, 9, 1>
    auto result_subst = A.SUBST(B, 3);
    cout << "SUBST result: " << result_subst << endl;

    // A.ERASE(2, 4) → <5, 3, 7, 9, 1>
    auto result_erase = A.ERASE(2, 4);
    cout << "ERASE result: " << result_erase << endl;


    auto result_change = A.CHANGE(B, 3);
    cout << "CHANGE result: " << result_change << endl;
    // Остальной код эксперимента остается без изменений
    ofstream fout("results.txt");
    
    // Параметры эксперимента
    const int min_size = 10;
    const int max_size = 600;
    const int step = 10;
    const int repeats = 10; // Количество повторений для каждого размера
    
    // Заголовок файла результатов
    fout << "Size MeanTime StDev\n";
    
    try {
        for (int size = min_size; size <= max_size; size += step) {
            vector<double> times;
            
            for (int r = 0; r < repeats; ++r) {
                // Генерация случайных множеств
                auto A = generateRandomSet(size);
                auto B = generateRandomSet(size);
                auto C = generateRandomSet(size);
                auto D = generateRandomSet(size);
                auto E = generateRandomSet(size);
                
                // Измерение времени
                auto start = high_resolution_clock::now();
                
                // Цепочка операций
                auto step1 = setUnion(B, C);
                auto step2 = setUnion(step1, D);
                auto step3 = symmetricDifference(A, step2);
                auto step4 = setIntersection(step3, E);
                
                auto end = high_resolution_clock::now();
                double duration = duration_cast<microseconds>(end - start).count();
                times.push_back(duration);
            }
            
            // Расчет статистики
            double sum = accumulate(times.begin(), times.end(), 0.0);
            double mean = sum / times.size();
            
            double sq_sum = inner_product(times.begin(), times.end(), 
                                        times.begin(), 0.0);
            double stdev = sqrt(sq_sum / times.size() - mean * mean);
            
            // Запись результатов
            fout << size << " " << mean << " " << stdev << "\n";
            cout << "Size: " << size << " Mean: " << mean 
                << " ms, StDev: " << stdev << " ms\n";
        }
    } 
    catch (const bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    fout.close();
    cout << "Experiment completed. Results saved to results.txt\n";
    return 0;
}