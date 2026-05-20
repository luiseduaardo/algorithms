#pragma once

#include <iostream>
#define spc " "
#define endl "\n"

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    Node* get_last() {
        return tail;
    }

    Node* get_first() {
        return head;
    }

    // search an element with value x and returns it
    Node* search(T x) {
        Node* cur = head;

        while (cur != nullptr && cur->value != x) {
            cur = cur->next;
        }

        return cur;
    }

    // insert an element with value of x to the end of the linked list
    void insert(T x) {
        Node* newnode = new Node;
        newnode->value = x;
        newnode->next = nullptr;

        if (head == nullptr) {
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
    }

    // delete the first occurance of an element x
    void remove(T x) {
        Node* todie = search(x);

        if (todie == nullptr) { return; }

        if (todie->prev != nullptr) {
            todie->prev->next = todie->next;
        } else {
            head = todie->next;
        }

        if (todie->next != nullptr) {
            todie->next->prev = todie->prev;
        } else {
            tail = todie->prev;
        }

        delete todie;
    }

    Node* remove_node(Node* n) {
        if (!n) return nullptr;

        Node* prev = n->prev;
        Node* next = n->next;

        if (prev) prev->next = next;
        else head = next;

        if (next) next->prev = prev;
        else tail = prev;

        delete n;
        return prev;
    }

    void remove_last() {
        if (tail == nullptr) return;

        Node* todie = tail;

        if (tail->prev != nullptr) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }

        delete todie;
    }

    void print_list() {
        Node* cur = head;

        while (cur) {
            cout << cur->value << spc;
            cur = cur->next;
        }

        cout << endl;
    }
};