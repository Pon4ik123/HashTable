#include "DynamicArray.h"
#include "LinkedList.h"
#include <random>

using namespace std;

template <typename K, typename V>
class HashTable {
public:
    int size;
    int arrayLength;
    DynamicArray<List<K, V>>* table;

    HashTable() :arrayLength(10), size(0) {
        table = new DynamicArray<List<K, V>>();
        for(int i = 0; i < arrayLength; i++){
            table->add(*new List<K, V>());
        }
    }

    int hash(string key){
        int length = key.length();
        int hashValue = 0;
        for(int i = 0; i< length;i++){
            hashValue += key[i] * (31^(length-1));
        }
        if(hashValue < 0) hashValue = -hashValue;
        return hashValue % arrayLength;
    }

    void rehash(){
        auto* temp = new DynamicArray<List<K, V>>();
        int tempSize = arrayLength;
        arrayLength *= 2;
        for(int i = 0; i<arrayLength; i++){
            temp->add(*new List<K, V>());
        }
        for (int i = 0; i < tempSize; ++i) {
            auto *oldTable = table->getByIndex(i)->head;
            while(oldTable != nullptr){
                K oldTableKey = oldTable->key;
                V oldTableValue = oldTable->value;
                temp->getByIndex(hash(oldTableKey))->createEnd(oldTableValue, oldTableKey);
                oldTable = oldTable->next;
            }
            table->getByIndex(i)->deleteList();
            //delete table->getByIndex(i);
        }
        delete table;
        table = temp;
    }

    void add(K k, V v){
        if (find(k)){
            table->getByIndex(hash(k))->changeAtKey(k, v);
        } else{
            table->getByIndex(hash(k))->createEnd(v, k);
            size++;
        }
        if(size > arrayLength){
            rehash();
        }
    }

    void show(){
        for (int i = 0; i < arrayLength; ++i) {
            if(table->getByIndex(i)->size > 0){
                cout << i << ": ";
                table->getByIndex(i)->show();
                cout << endl;
            }
        }
        cout << size << " " << arrayLength << endl;
    }

    Node<K,V> * find(K key){
        auto tmp = hash(key);
        return table->getByIndex(tmp)->findByKey(key);
    }

    void clear(){
        for(int i = 0; i<arrayLength; i++){
            table->getByIndex(i)->deleteList();
        }
        table->clearTable();
        size = 0;
        arrayLength = 10;
    }

    void deleteByKey(K key){
        auto tmp = hash(key);
        table->getByIndex(tmp)->findByKeyAndRemove(key);
        size--;
    }

    void stats(){
        int maxSize = 0;
        int minSize = size;
        int sum = 0;
        int notEmp = 0;

        for(int i = 0; i < arrayLength; i++){
            int current = table->getByIndex(i)->getSize();
            if(current > maxSize){
                maxSize = current;
            }
            if(current<minSize && current !=0){
                minSize = current;
            }
            if(current !=0){
                sum+=current;
                notEmp++;
            }
        }
        double mid = sum/notEmp;
        cout << "List min size: "<< minSize << endl;
        cout << "List max size: "<< maxSize << endl;
        cout << "Non-empty list: "<< notEmp << endl;
        cout << "List avg size: "<< mid << endl;
    }
};

string randomKey(int length) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string randomString;
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % characters.size();
        randomString += characters[randomIndex];
    }
    return randomString;
}

int randomValue(){
    random_device rd;
    default_random_engine dfe(rd());
    uniform_int_distribution<int> number(1, 1000);
    return number(dfe);
}

int main(){
    auto* table = new HashTable<string, int>();
    const int MAX_ORDER = 7;
    for ( int o = 1; o <= MAX_ORDER ; o++){
        const int n = pow (10,o );

        clock_t t1 = clock ();
        for ( int i = 0; i < n ; i ++){
            table->add(randomKey(10), randomValue());
        }
        clock_t t2 = clock ();

//        const int m = pow (10,4);
//        t1 = clock ();
//        for ( int i = 0; i < m ; i++){
//            table->find(randomKey(10));
//        }
//        t2 = clock ();

        table->stats();
        table->clear();
    }
    return 0;
}