#include "SinglyLinkedList.cpp"
#include <memory>

template <typename T>
class SinglyLinkedList { 

public : 

    struct Node { 
        int data; 
        Node *next; 
    };

    Node *head;
    int length;
    size_t size;

    SinglyLinkedList(); 
    ~SinglyLinkedList(); 

    
    void append(const T& value);
    void push(const T& value);
    void insert(int index, const T& value);
    void remove(int index);
    void clear();
    T pop();

    void print();
    bool isEmpty();
    bool contains(const T& value); 
    T get(int index); 


    int firstIndexOf(const T& value);
    int lastIndexOf(const T& value);
    void remove(const T& value);
    

    
    void set(int index, const T& value); 

    
    void insert(int index, const T& value); 

    

    int firstIndexOf(const T& value);
    int lastIndexOf(const T& value);
    void removeFirst(const T& value);


    /*
         Example iterator usage: 
         SinglyLinkedList::Iterator iter = list.begin();
`         while (iter != list.end()) {
             cout << *iter << endl;
             ++iter;
         }
    */
    class iterator {
        Node *current;
    public:
        iterator(Node *n) : current(n) {}
        iterator operator++() { current = current->next; return *this; }
        bool operator!=(const iterator& it) { return current != it.current; }
        int operator*() { return current->data; }
    };
    
};
