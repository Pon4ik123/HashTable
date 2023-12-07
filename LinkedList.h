#include <iostream>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

template<typename K, typename V>
class Node {
public:
    V value;
    K key;
    Node *previous;
    Node *next;

    Node() {}

    Node(V v, K k) : value(v), key(k), previous(nullptr), next(nullptr) {}

    ~Node() {}
};

template<typename K, typename V>
class List {
public:
    Node<K, V> *head;
    Node<K, V> *tail;
    int size;

    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() { deleteList(); }

    int getSize() {
        return size;
    }

    void createEnd(V v, K k) {
        auto *temp = new Node<K, V>(v, k);
        if (head == nullptr) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            temp->previous = tail;
            tail = temp;
        }
        size++;
    }

    void deleteHead() {
        if (head != nullptr) {
            if (head->next != nullptr) {
                head->next->previous = nullptr;
                Node<K, V> *temp = head;
                head = head->next;
                delete temp;
            } else {
                delete head;
                head = nullptr;
                tail = nullptr;
            }
            size--;
        }
    }

    void deleteEnd() {
        if (tail != nullptr) {
            if (tail->previous != nullptr) {
                tail->previous->next = nullptr;
                Node<K, V>* temp = tail;
                tail = tail->previous;
                delete temp;
            }
            else {
                delete tail;
                head = nullptr;
                tail = nullptr;
            }
            size--;
        }
    }

    Node<K, V> *findByKey(K k) {
        if(!head){
            return nullptr;
        }
        Node<K, V> *current = head;
        for (int index = 0; current; index++) {
            if (current->key == k) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void findByKeyAndRemove(K key) {
        auto *temp = findByKey(key);
        if (temp) {
            if (this->head == temp && this->tail == temp) {
                this->deleteList();
            }
            else if (this->head == temp) {
                this->deleteHead();
            }
            else if (this->tail == temp) {
                this->deleteEnd();
            }
            else {
                temp->next->previous = temp->previous;
                temp->previous->previous = temp->previous;
                this->size--;
                delete temp;
            }
        }
    }

    void changeAtKey(K target, V val) {
        Node<K, V> *temp = findByKey(target);
        if (temp) {
            temp->value = val;
        }
    }

    void deleteList() {
        while (head) {
            deleteHead();
        }
    }

    void show() {
        Node<K, V> *current = head;
        for (int index = 0; current; index++) {
            cout << current->key << " -> " << current->value << "\t";
            current = current->next;
        }
    }
};