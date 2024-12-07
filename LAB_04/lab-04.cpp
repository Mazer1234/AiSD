#include <vector>
#include <iostream>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max()/2;

class Graf{
    private:
        int count_of_elem;
        vector<vector<int>> matrix;
        vector<vector<int>> tree_matrix;

        void add_marking(){
            for (int i = 0; i < matrix.size(); i++){
                matrix[i][0] = i;
                matrix[0][i] = i;

            }
        }
    public:
        Graf(int count_of_elem): count_of_elem(count_of_elem){
            matrix.resize(count_of_elem+1, vector<int>(count_of_elem+1));
            add_marking();
        }

        int get_count_of_element(){
            return this->count_of_elem;
        }

        void print_graph_matrix(){
            for (int i = 0; i < matrix.size(); i++){
                for (int j = 0; j < matrix.size(); j++){
                    if (matrix[i][j] == INF) cout << "- ";
                    else cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
        }

        void print_tree_matrix(){
            leonids_algorithm();
            for(int i = 0; i <= count_of_elem; i++){
                for (int j = 0; j <= count_of_elem; j++){
                    cout << tree_matrix[i][j] << " ";
                }
                cout << endl;
            }
        }
        void set_values(int count_of_elem){
            int value = 0;
            for(int i = 1; i < matrix.size(); i++){
                for (int j = i+1; j < matrix.size(); j++){
                    cout << "Enter the number 1 if you want to build a way between " << i << " and " << j << ". 0 to miss: ";
                    cin >> value;
                    cout << endl;
                    if (i == j){
                        continue;
                    }
                    if (value <= 0){
                        matrix[i][j] = 0;
                        matrix[j][i] = 0;
                    }else{
                        matrix[i][j] = 1;
                        matrix[j][i] = 1;
                    }
                }
            }
        }

        void leonids_algorithm(){
            tree_matrix = matrix;
            for(int i = 2; i <= count_of_elem; i++){
                for(int j = 2; j <= count_of_elem; j++){
                    tree_matrix[i][j] = 0;
                }
            }
            for (int i = 1; i <= count_of_elem; i++){
                for (int j = 1; j <= count_of_elem; j++){
                    if(tree_matrix[i][1] == 1){
                        fill_level(i);
                    }
                }
            }
        }

        bool is_vector_null(vector<int> vec){
            for (int i = 1; i <= count_of_elem; i++){
                if (vec[i] != 0){
                    return false;
                }
            }
            return true;
        }

        void fill_level(int row){
            for (int i = 2; i <=count_of_elem; i++){
                if(matrix[row][i] == 1 && is_vector_null(tree_matrix[i])){
                    tree_matrix[row][i] = 1;
                    tree_matrix[i][row] = 1;
                }
            }
        }
};

int main(){
    int count_of_elements;
    cout << "How many elements will be in the graph" << endl;
    cin >> count_of_elements;
    if (count_of_elements <= -1) return -1;
    Graf graph(count_of_elements);
    graph.print_graph_matrix();
    graph.set_values(count_of_elements);
    cout << "--TREE--" << endl;
    graph.print_graph_matrix();
    cout << "----------" << endl;
    cout << "--DEEP CONSTICTING TREE--"<< endl;
    graph.print_tree_matrix();
    return 0;
}