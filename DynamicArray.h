#include <iostream>

using namespace std;

template <typename T>
class DynamicArray {
public:
    T* array;
    int size;
    int capacity;

    DynamicArray() : size(0), capacity(1){
        array = new T[capacity];
    }
    ~DynamicArray() {
        delete[] array;
        array = nullptr;
        size = 0;
        capacity = 0;
    }

    void add(T data) {
        if (capacity == 0) {
            capacity++;
            array = new T[capacity];
        }
        else if (size == capacity) {
            capacity *= 2;
            T* temp = new T[capacity];
            for (int i = 0; i < size; i++) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }
        array[size] = data;
        size++;
    }

    T* getByIndex(int index) {
        if (index >= 0 && index < size) {
            return &array[index];
        }
        else {
            return nullptr;
        }
    }

    void clearTable() {
        capacity = 1;
        size = 0;
    }
};