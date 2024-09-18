#include <iostream>
#define MAXLEN 100
using namespace std;

struct Set          //list
{
    char el;
    Set *next;
    Set(char e, Set *n = nullptr) : el(e), next(n) {}
    ~Set() { delete next; }
};

void print_set(Set* set){
        Set* current = set;
        cout << "Finish set: ";
        if(set == nullptr){
            cout << "Error, set is empty" << endl;
        }else{
        while (current != nullptr){
            cout << current->el << " ";
            current = current->next;
        }
        }
        cout << endl;
    }

bool find_in_set(Set *head, char s)
{
    Set *current = head;
    while (current != nullptr)
    {
        if (current->el == s)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

Set *createSetByIntput(char *arr[])
{
    Set *head = nullptr;
    Set *tail = nullptr;
    int i = 1;

    char el;

    while (cin >> el && el != 'x')
    {
        if (isalpha(el) && isupper(el) == 0){
        Set *newNode = new Set(el);
        if (head == nullptr)
        {
            head = newNode;
            head->next = tail;
            arr[0] = el;
        }
        else if (!find_in_set(head, el))
        {
            tail->next = newNode;
            arr[i] = el;
            i++ //Здесь проблема
        }
        else
        {
            continue;
        }
        tail = newNode;
        }
    }

    return head;
}

Set* check_sets(Set *head1, Set *head2)
{
    Set *current1 = head1;
    Set *current2 = head2;
    Set *set_head = nullptr;
    Set *set_tail = nullptr;

    while (current1 != nullptr)
    {
        current2 = head2;
        while (current2 != nullptr)
        {
            if (current1->el == current2->el)
            {
                Set *newNode = new Set(current1->el);
                if (set_head == nullptr)
                {
                    set_head = newNode;
                    set_head->next = set_tail;
                }
                else if (!find_in_set(set_head, current1->el))
                {
                    set_tail->next = newNode;

                }else{
                    continue;
                }
                set_tail = newNode;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
        return set_head;
    }           // finish list


char* create_arr(Set* set){         //arr
        Set* current = set;
        char arr[MAXLEN];
        int i=0;
        if(set == nullptr){
            cout << "Error, set is empty" << endl;
        }else{
        while (current != nullptr){
            arr[i] = current->el;
            current = current->next;
            i++;
        }
        }
        return arr;
    }
void print_arr(char arr[MAXLEN]){
    int i = 0;
        cout << "Finish array: ";
        if(!isalpha(arr[0])){
            cout << "Error, set is empty" << endl;
        }else{
        while (isalpha(arr[i])){
            cout << arr[i] << " ";
            i++;
        }
        }
        cout << endl;
    }

char* check_arrs(char Aar[MAXLEN], char Bar[MAXLEN], char Car[MAXLEN], char Dar[MAXLEN]){
        char arr[MAXLEN];
        int i = 0, j = 0, k = 0, l = 0, a = 0;
        while(isalpha(Aar[i])){
            j = 0;
            while(isalpha(Bar[j])){
                k = 0;
                while(isalpha(Car[k])){
                    l = 0;
                    while(isalpha(Dar[l])){
                        if (Aar[i] == Bar[j] == Car[k] == Dar[l]){
                            arr[a] = Aar[i];
                            a++;
                        }
                        l++;
                    }
                    k++;
                }
                j++;
            }
            i++;
        }
    return arr;
}

    int main()
    {
        char *Bar, *Aar, *Car, *Dar, *Ear;
        Set *B, *A, *C, *D, *E, *A1, *A2; // A - final set
        cout << "Let's fill the A set. If you want to finish, press x" << endl;
        A = createSetByIntput();
        cout << "Let's fill the B set. If you want to finish, press x" << endl;
        B = createSetByIntput();
        cout << "Let's fill the C set. If you want to finish, press x" << endl;
        C = createSetByIntput();
        cout << "Let's fill the D set. If you want to finish, press x" << endl;
        D = createSetByIntput();
        cout << "Let's check sets" << endl;
        A1 = check_sets(A, B);
        A2 = check_sets(C, D);
        E = check_sets(A1, A2);
        print_set(E);
        Bar = create_arr(B);
        Aar = create_arr(A);
        Car = create_arr(C);
        Dar = create_arr(D);
        Ear = check_arrs(Aar, Bar, Car, Dar);
        print_arr(Ear);
        return 0;
    }