#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <memory>
#include <iostream>

enum cmp { LESS, GREATER, EQUAL };

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

        std::shared_ptr<Node> operator=(const std::shared_ptr<Node> other) {
            data = (other->data);
            next = (other->next);
            return *this;
        }
    };

    std::shared_ptr<Node> head;

    std::shared_ptr<Node> iter_to_index(int index);
    SinglyLinkedList<T>& merge(SinglyLinkedList<T>& left, SinglyLinkedList<T>& right);

public:
    size_t length;

    SinglyLinkedList<T>() : head(std::make_shared<Node>(T())), length(0) {}
    ~SinglyLinkedList();

    template <size_t N>
    SinglyLinkedList(T (&values)[N]) : head(std::make_shared<Node>(T())), length(0) {
        for (int i = 0; i < N; ++i) {
            append(values[i]);
        }
    }

    SinglyLinkedList<T>& append(const T& value);
    SinglyLinkedList<T>& push(const T& value);
    SinglyLinkedList<T>& insert(int index, T& value);
    SinglyLinkedList<T>& remove(int index);
    SinglyLinkedList<T>& clear();
    T pop(int index);
    void print();
    bool isEmpty();
    bool contains(const T& value);
    T get(int index);
    std::shared_ptr<Node> getNode(int index);
    int firstIndexOf(const T& value);
    int lastIndexOf(const T& value);
    SinglyLinkedList<T>& removeAll(const T& value);
    SinglyLinkedList<T>& set(int index, T& value);

    SinglyLinkedList<T>& operator+=(const T& value);
    SinglyLinkedList<T>& operator+(const T& value);
    SinglyLinkedList<T>& operator=(SinglyLinkedList<T>& other);

    SinglyLinkedList<T>& merge_sort();
};

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator+=(const T& value) {
    append(value);
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator+(const T& value) {
    append(value);
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>& other) {
    clear();
    for (int i = 0; i < other.length; ++i) {
        append(other.get(i));
    }
    return *this;
}

template <typename T>
std::shared_ptr<typename SinglyLinkedList<T>::Node> SinglyLinkedList<T>::iter_to_index(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    std::shared_ptr<Node> current = head;

    for (int i = 0; i <= index; ++i)
    {
        current = current->next;
        }
        return current;
    
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::append(const T& value) {

    if (length == 0) {
        head->next = std::make_shared<Node>(value);
        ++length;
        return *this;
    }

    std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
    iter_to_index(length-1)->next = new_node;
    ++length;
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::push(const T& value) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
    new_node->next = head->next;
    head->next = new_node;
    ++length;
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::insert(int index, T& value) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
    std::shared_ptr<Node> current_node = iter_to_index(index);
    new_node->next = current_node->next;
    current_node->next = new_node;
    ++length;
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::remove(int index) {
    std::shared_ptr<Node> before_node_to_remove = iter_to_index(index-1);
    std::shared_ptr<Node> node_to_remove = std::move(before_node_to_remove->next);
    before_node_to_remove->next = std::move(node_to_remove->next); //std::shared_ptr handles deallocations automatically once the node goes out of scope
    --length;
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::clear() {
    head=std::make_shared<Node>(T()); //reset head to a new empty node - std::shared_ptr handles deallocations automatically once the other nodes go out of scope
    length = 0;
    return *this;
}

template <typename T>
T SinglyLinkedList<T>::pop(int index) {
    std::shared_ptr<Node> node_before = iter_to_index(index - 1);
    std::shared_ptr<Node> node_to_remove = node_before->next;
    node_before->next = node_to_remove->next; // std::shared_ptr handles deallocations automatically once the other nodes go out of scope
    --length;
    return node_to_remove->data;
}

template <typename T>
void SinglyLinkedList<T>::print() {
    std::shared_ptr<Node> current = head;
    for (int i = 0; i < length; ++i) {
        current = current->next;
        std::cout << current->data << " ";
    }
    std::cout << std::endl;
}

template <typename T>
bool SinglyLinkedList<T>::isEmpty() {
    return (length == 0);
}

template <typename T>
bool SinglyLinkedList<T>::contains(const T& value) {
    std::shared_ptr<Node> current = head;
    for (int i = 0; i < length; ++i) {
        current = current->next;
        if (current->data == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
T SinglyLinkedList<T>::get(int index) {
    std::shared_ptr<Node> node_at_index = iter_to_index(index);
    return node_at_index->data;
}

template <typename T>
std::shared_ptr<typename SinglyLinkedList<T>::Node> SinglyLinkedList<T>::getNode(int index) {
    std::shared_ptr<Node> node_at_index = iter_to_index(index);
    return node_at_index;
}

template <typename T>
int SinglyLinkedList<T>::firstIndexOf(const T& value) {
    std::shared_ptr<Node> current = head;
    for (int i = 0; i < length; ++i) {
        current = current->next;
        if (current->data == value) {
            return i;
        }
    }
    return -1;
}

template <typename T>
int SinglyLinkedList<T>::lastIndexOf(const T& value) {
    for (int i = length - 1; i >= 0; --i) {
        if (get(i) == value) {
            return i;
        }
    }
    return -1;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::removeAll(const T& value) {
    for (int i = 0; i < length; ++i) {
        if (get(i) == value) {
            remove(i);
            --i;
        }
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::set(int index, T& value) {
    std::shared_ptr<Node> node_at_index = iter_to_index(index);
    node_at_index->data = value;
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::merge(SinglyLinkedList<T>& left, SinglyLinkedList<T>& right) {
    std::shared_ptr<Node> left_current = left.head->next;
    std::shared_ptr<Node> right_current = right.head->next;

    clear();

    while (left_current != nullptr && right_current != nullptr) {
        if (left_current->data < right_current->data) {
            append(left_current->data);
            left_current = left_current->next;
        } else {
            append(right_current->data);
            right_current = right_current->next;
        }
    }

    while (left_current != nullptr) {
        append(left_current->data);
        left_current = left_current->next;
    }

    while (right_current != nullptr) {
        append(right_current->data);
        right_current = right_current->next;
    }

    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::merge_sort() {
    if (length > 1) {

        SinglyLinkedList<T> left;
        SinglyLinkedList<T> right;

        std::shared_ptr<Node> current = head->next;
        for (int i = 0; i < length; i++) {
            if (i < length / 2) {
                left.append(current->data);
            } else {
                right.append(current->data);
            }
            current = current->next;
        }

        left.merge_sort();
        right.merge_sort();

        merge(left, right);
    }
    return *this;
}
#endif