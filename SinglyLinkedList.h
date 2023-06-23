#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <memory>
#include <iostream>

template <typename T>
class SinglyLinkedList {

private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::unique_ptr<Node> head;

    std::unique_ptr<Node> iter_to_index(int index);

public:
    size_t length;

    SinglyLinkedList();
    ~SinglyLinkedList();

    template <size_t N>
    SinglyLinkedList(const T (&values)[N]);

    SinglyLinkedList<T>& append(const T& value);
    SinglyLinkedList<T>& push(const T& value);
    SinglyLinkedList<T>& insert(int index, const T& value);
    SinglyLinkedList<T>& remove(int index);
    SinglyLinkedList<T>& clear();
    T pop(int index);
    void print();
    bool isEmpty();
    bool contains(const T& value);
    T get(int index);
    std::unique_ptr<Node> getNode(int index);
    int firstIndexOf(const T& value);
    int lastIndexOf(const T& value);
    SinglyLinkedList<T>& removeAll(const T& value);
    SinglyLinkedList<T>& set(int index, const T& value);

    SinglyLinkedList<T>& operator+=(const T& value);
    SinglyLinkedList<T>& operator+(const T &value);
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
};

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator+=(const T& value) {
    append(value);
    return *this;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator+(const T& value){
    append(value);
    return *this;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
    clear();
    for (int i = 0; i < other.length; ++i) {
        append(other.get(i));
    }
    return *this;
}

template<typename T>
std::unique_ptr<typename SinglyLinkedList<T>::Node> SinglyLinkedList<T>::iter_to_index(int index) {

    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::unique_ptr<Node> current = head;

    for (int i = 0; i <= index; ++i) {
        current = current->next;
    }
    return current;
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), length(0) {}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template<typename T>
template<size_t N>
SinglyLinkedList<T>::SinglyLinkedList(const T (&values)[N]) : head(nullptr), length(0) {
    for (int i = 0; i < N; ++i) {
        append(values[i]);
    }
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::append(const T& value) {
    std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
    std::unique_ptr<Node> current = head;
    for (int i = 0; i < length; ++i) {
        current = current->next;
    }
    current->next = std::move(new_node);
    ++length;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::push(const T& value) {
    std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
    new_node->next = std::move(head);
    head = std::move(new_node);
    ++length;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::insert(int index, const T& value) {


    std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
    std::unique_ptr<Node> current_node = iter_to_index(index);
    new_node->next = std::move(current_node->next);
    current_node->next = std::move(new_node);
    ++length;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::remove(int index) {


    std::unique_ptr<Node> node_before = iter_to_index(index - 1);
    std::unique_ptr<Node> node_to_remove = std::move(node_before->next);
    node_before->next = std::move(node_to_remove->next);
    --length;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::clear() {
    head->next = nullptr; // std::unique_ptr handles deallocations automatically once the other nodes go out of scope
}

template<typename T>
T SinglyLinkedList<T>::pop(int index) {


    std::unique_ptr<Node> node_before = iter_to_index(index - 1);
    std::unique_ptr<Node> node_to_remove = std::move(node_before->next);
    node_before->next = std::move(node_to_remove->next);
    --length;
    return node_to_remove->data;
}

template<typename T>
void SinglyLinkedList<T>::print() {
    std::unique_ptr<Node> current = head;
    for (int i = 0; i < length; ++i) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() {
    return (length == 0);
}

template<typename T>
bool SinglyLinkedList<T>::contains(const T& value) {
    std::unique_ptr<Node> current = head;
    for (int i = 0; i < length; ++i) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
T SinglyLinkedList<T>::get(int index) {


    std::unique_ptr<Node> node_at_index = iter_to_index(index);
    return node_at_index->data;
}

template<typename T>
std::unique_ptr<typename SinglyLinkedList<T>::Node> SinglyLinkedList<T>::getNode(int index) {


    std::unique_ptr<Node> node_at_index = iter_to_index(index);
    return node_at_index;
}

template<typename T>
int SinglyLinkedList<T>::firstIndexOf(const T& value) {
    std::unique_ptr<Node> current = head;

    for (int i = 0; i < length; ++i) {
        if (current->data == value) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

template<typename T>
int SinglyLinkedList<T>::lastIndexOf(const T& value) {
    std::unique_ptr<Node> current = head;
    int last_index = -1;

    for (int i = 0; i < length; ++i) {
        if (current->data == value) {
            last_index = i;
        }
        current = current->next;
    }
    return last_index;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::removeAll(const T& value) {
    std::unique_ptr<Node> current = head;
    std::unique_ptr<Node> prev = nullptr;

    for (int i = 0; i < length; ++i) {
        if (current->data == value) {
            if (prev == nullptr) {
                head = std::move(current->next);
            } else {
                prev->next = std::move(current->next);
            }
            --length;
        } else {
            prev = current;
        }
        current = current->next;
    }
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::set(int index, const T& value) {


    std::unique_ptr<Node> node_at_index = iter_to_index(index);
    node_at_index->data = value;
}

#endif  // SINGLYLINKEDLIST_H
