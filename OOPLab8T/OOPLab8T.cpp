#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

template<typename T>
void findMax(const T* arr, int size, T& maxVal, int& count) {
    if (size == 0) {
        maxVal = T();
        count = 0;
        return;
    }
    maxVal = arr[0];
    count = 1;
    for (int i = 1; i < size; ++i) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            count = 1;
        }
        else if (arr[i] == maxVal) {
            count++;
        }
    }
}
template<>
void findMax(const char* * arr, int size, const char*& maxVal, int& count) { //для char
    if (size == 0) {
        maxVal = nullptr;
        count = 0;
        return;
    }
    maxVal = arr[0];
    count = 1;
    for (int i = 1; i < size; ++i) {
        if (strcmp(arr[i], maxVal) > 0) {
            maxVal = arr[i];
            count = 1;
        }
        else if (strcmp(arr[i], maxVal) == 0) {
            count++;
        }
    }
}

int main() {
    int intArray[] = { 1, 2, 3, 3, 2, 1, 3 };
    int maxInt, intCount;
    findMax(intArray, 7, maxInt, intCount);
    cout << "Максимальне значення у масиві: " << maxInt << ", кількість: " << intCount << endl;

    return 0;
}










#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

template<typename T>
void shellSort(T arr[], int size) {
    for (int step = size / 2; step > 0; step /= 2) {
        for (int i = step; i < size; ++i) {
            T temp = arr[i];
            int j;
            for (j = i; j >= step && arr[j - step] > temp; j -= step) {
                arr[j] = arr[j - step];
            }
            arr[j] = temp;
        }
    }
}

void shellSort(char* arr[], int size) {
    for (int step = size / 2; step > 0; step /= 2) {
        for (int i = step; i < size; ++i) {
            char* temp = arr[i];
            int j;
            for (j = i; j >= step && strcmp(arr[j - step], temp) > 0; j -= gap) {
                arr[j] = arr[j - step];
            }
            arr[j] = temp;
        }
    }
}


int main() {

    return 0;
}









#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

template<typename T>
class StackNode {
public:
    T data;
    StackNode* next;

    StackNode(T val) : data(val), next(nullptr) {}
};

template<typename T>
class Stack {
private:
    StackNode<T>* top;
    int size;
public:
    Stack() : top(nullptr), size(0) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T val) {
        StackNode<T>* newNode = new StackNode<T>(val);
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop() {
        if (isEmpty()) {
            cerr << "Стек порожній. Неможливо видалити елемент." << endl;
            return;
        }
        StackNode<T>* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    T peek() const {
        if (isEmpty()) {
            cerr << "Стек порожній." << endl;
            return T();
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int getSize() const {
        return size;
    }
};

int main() {
    Stack<int> Stack;
    Stack.push(1);
    Stack.push(2);
    Stack.push(3);
    cout << "Верхній елемент стеку: " << Stack.peek() << endl;
    Stack.pop();
    cout << "Верхній елемент стеку: " << Stack.peek() << endl;
    return 0;
}










#ifndef UNTITLED1_SINGLELINKEDLIST_H
#define UNTITLED1_SINGLELINKEDLIST_H
#include "SingleNode.h"
#include <iostream>
using namespace std;
using namespace single_Node;

template <typename T>
class SingleLinkedList {
private:
    unique_ptr<Node<T>> head;
    int size;
public:
    SingleLinkedList() :head{ nullptr }, size{ 0 } {};

    void unshift(T data);
    void push(T data);
    void shift();
    void pop();

    void at(int index);
    void atInsert(int index, T data);
    void atRemove(int index);

    int search(T value);

    bool isEmpty();

    void show() const;
};

template<typename T>
int SingleLinkedList<T>::search(T value) {
    Node<T>* current = head.get();
    int index = 0;
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->next.get();
        index++;
    }
    return -1;
}

template<typename T>
bool SingleLinkedList<T>::isEmpty() {
    if (!head) {
        return true;
    }
    return false;
}

template<typename T>
void SingleLinkedList<T>::atRemove(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    Node<T>* current = head.get();
    for (int i = 0; i < index; i++) {
        current = current->next.get();
    }
    current->next = move(current->next->next);
    --size;
}

template<typename T>
void SingleLinkedList<T>::atInsert(int index, T data) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    Node<T>* current = head.get();
    unique_ptr<Node<T>> newNode = make_unique<Node<T>>(data);
    if (index == 0) {
        unshift(data);
        return;
    }
    else if (index == size - 1) {
        push(data);
        return;
    }
    for (int i = 0; i < index; i++) {
        current = current->next.get();
    }
    newNode->next = move(current->next);
    current->next = move(newNode);
    size++;

}

template<typename T>
void SingleLinkedList<T>::at(int index) {
    Node<T>* current = head.get();
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    for (int i = 0; i < index; i++) {
        current = current->next.get();
    }
    cout << "Data at index " << index << " : " << current->data << endl;
}

template<typename T>
void SingleLinkedList<T>::pop() {
    if (!head) {
        throw out_of_range("List empty");
    }
    if (size == 1) {
        head.reset();
        size--;
        return;
    }
    Node<T>* current = head.get();
    while (current->next->next) {
        current = current->next.get();
    }
    current->next.reset();
    size--;
}

template<typename T>
void SingleLinkedList<T>::shift() {
    if (!head) {
        throw out_of_range("List empty");
    }
    head = move(head->next);
    size--;
}

template<typename T>
void SingleLinkedList<T>::show() const {
    Node<T>* current = head.get();
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next.get();
    }
    cout << endl;
}

template<typename T>
void SingleLinkedList<T>::unshift(T data) {
    unique_ptr<Node<T>> newNode = make_unique<Node<T>>(data);
    newNode->next = move(head);
    head = move(newNode);
    size++;
}

template<typename T>
void SingleLinkedList<T>::push(T data) {
    unique_ptr<Node<T>> newNode = make_unique<Node<T>>(data);
    Node<T>* current = head.get();
    if (!current) {
        head = move(newNode);
        size++;
        return;
    }
    while (current->next) {
        current = current->next.get();
    }
    current->next = move(newNode);
    size++;
}

#endif //UNTITLED1_SINGLELINKEDLIST_H






#ifndef UNTITLED1_SINGLENODE_H
#define UNTITLED1_SINGLENODE_H
#include <memory>
namespace single_Node {
    template <typename T>
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        explicit Node(T newData)
            :data{ newData }, next{ nullptr } {};
    };
}
#endif //UNTITLED1_SINGLENODE_H

#include <vector>
#include <cstring>
#include <iostream>
#include "SingleLinkedList.h"
using namespace std;

int main() {

    SingleLinkedList<int> list;
    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);
    list.atInsert(0, 0);
    list.show();
    list.atRemove(1);
    list.show();
    cout << "Found: " << list.search(1) << endl;
    return 0;
}
