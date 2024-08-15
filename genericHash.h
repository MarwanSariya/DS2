#include <iostream>
#include <functional>
#include <stdexcept>

template<typename Key, typename Value>
class genericHash {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
        // ~Node(){
        //     delete value;
        //     delete next;
        // }
        ~Node(){
            // delete value;
        };

    };

    Node** table;
    size_t size;
    size_t capacity;

    size_t hash(const Key& key) const {
        return (key) % capacity;
    }

    void resize(size_t newsize) {
        Node** newTable = new Node*[newsize];

        for (size_t i = 0; i < capacity; i++) {
            Node* curr = table[i];
            while (curr != nullptr) {
                Node* next = curr->next;
                size_t newIndex = std::hash<Key>{}(curr->key) % newsize;
                curr->next = newTable[newIndex];
                newTable[newIndex] = curr;
                curr = next;
            }
        }

        auto temp = table;
        table = newTable;
        delete temp;
        capacity = newsize;
    }

public:
    genericHash(size_t initialCapacity = 10) : size(0), capacity(initialCapacity) {
        table = new Node*[initialCapacity];
        for (size_t i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~genericHash() {
        for (size_t i = 0; i < capacity; i++) {
            Node* curr = table[i];
            while (curr != nullptr) {
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
        }
        delete[] table;
    }

    bool insert(const Key& key, const Value& value) {
 

        size_t index = key % capacity;
        Node* newNode = new Node(key, value);

        // std::cout << "inserting key: " << key << std::endl;
        // std::cout << index << "indx" << std::endl;

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* curr = table[index];
            while (curr->next != nullptr) {
                if (curr->key == key) {
                    delete newNode;  // Free the newly created node to avoid memory leak
                    return false;
                }
                curr = curr->next;
            }

            // Handle the case where the matching key is the last node in the list
            if (curr->key == key) {
                delete newNode;
            } else {
                curr->next = newNode;
            }
        }

        size++;
        if (size + 1 >= capacity) {
            resize(capacity * 2);
        }
        return true;
    }

    Value& find(const Key& key) const {

        size_t index = key % capacity;
        Node* curr = table[index];
        // std::cout << "finding key: " << key << std::endl;
        // std::cout << index << "indx" << std::endl;
        while (curr != nullptr) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }

        throw std::out_of_range("Key not found");
    }

    void remove(const Key& key) {
        size_t index = hash(key);
        Node* curr = table[index];
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (curr->key == key) {
                if (prev == nullptr) {
                    table[index] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                size--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

//    void clear() {
//        for (size_t i = 0; i < capacity; i++) {
//            Node* curr = table[i];
//            while (curr != nullptr) {
//                Node* next = curr->next;
//                delete curr;
//                curr = next;
//            }
//            table[i] = nullptr;
//        }
//        size = 0;
//    }

///// my clear
    // void clear() {
    //     for (size_t i = 0; i < capacity; ++i) {
    //         if (table[i] != nullptr) {
    //             Node* current = table[i];
    //             while (current != nullptr) {
    //                 Node* toDelete = current;
    //                 current = current->next;
    //                 toDelete->next = nullptr;  // Avoid recursive deletion by breaking the chain
    //                 delete toDelete;
    //             }
    //         }
    //     }
    // }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    // Value& operator[](const Key& key) {
    //     try {
    //         return find(key);
    //     } catch (const std::out_of_range&) {
    //         insert(key, Value{});
    //         return table[hash(key)]->value;
    //     }
    // }
};
