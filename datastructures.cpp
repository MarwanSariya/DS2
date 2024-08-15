#include "datastructures.h"
#include <iostream>

// Node implementation
Node::Node(int id, int ships) : fleetId(id), numShips(ships), next(nullptr) {}

// LinkedList implementation
LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    clear();
}

bool LinkedList::contains(int fleetId) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->fleetId == fleetId) {
            return true;
        }
        current = current->next;
    }

    return false;
}

void LinkedList::insert(int fleetId, int numShips) {
    if (contains(fleetId)) {
        return; // Fleet already exists
    }
    Node* newNode = new Node(fleetId, numShips);
    newNode->numPirates = 0;
    newNode->next = head;
    head = newNode;
    
}

void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;
}

// Hashtable implementation
Hashtable::Hashtable(int size) : tableSize(size), numofElements(0) {
    table = new LinkedList[size];

}

Hashtable::~Hashtable() {
    delete[] table;
}

int Hashtable::hashFunction(int fleetId) const {
    return fleetId % tableSize;
}

int Hashtable::get_num_ships(int fleetId) const {
    int index = hashFunction(fleetId);
    Node* current = table[index].head;
    while (current != nullptr) {
        if (current->fleetId == fleetId) {
            return current->numShips;
        }
        current = current->next;
    }

    return -1;
}




bool Hashtable::contains(int fleetId) const {
    int index = hashFunction(fleetId);
    return table[index].contains(fleetId);
}

void Hashtable::insert(int fleetId, int numShips) {
    int index = hashFunction(fleetId);
    table[index].insert(fleetId, numShips);
     numofElements++;
     if (numofElements >= tableSize*0.5) {
         expand();
     }
}

// PirateNode implementation
PirateNode::PirateNode(int pId, int fId, int m, int r)
    : pirateId(pId), fleetId(fId), money(m), rank(r), next(nullptr) {}

// PirateLinkedList implementation
PirateLinkedList::PirateLinkedList() : head(nullptr) {}

PirateLinkedList::~PirateLinkedList() {
    clear();
}

bool PirateLinkedList::contains(int pirateId) const {
    PirateNode* current = head;
    while (current != nullptr) {
        if (current->pirateId == pirateId) {
            return true;
        }
        current = current->next;
    }
    return false;
}


void PirateLinkedList::insert(int pirateId, int fleetId, int money, int rank) {
    if (contains(pirateId)) {
        return; // Pirate already exists
    }

    PirateNode* newNode = new PirateNode(pirateId, fleetId, money, rank);
    newNode->next = head;
    head = newNode;


    // Debugging: Print the list and its size
    int size = 0;
    PirateNode* current = head;
    while (current != nullptr) {
        current = current->next;
        size++;
    }
}

bool PirateLinkedList::update_salary(int pirateId, int salary) {
    PirateNode* current = head;
    while (current != nullptr) {
        if (current->pirateId == pirateId) {
            current->money += salary; // Sets money to the new salary
            return true;
        }
        current = current->next;
    }
    return false;
}

void PirateLinkedList::clear() {
    PirateNode* current = head;
    while (current != nullptr) {
        PirateNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;
}

// PirateHashtable implementation
PirateHashtable::PirateHashtable(int size) : tableSize(size) {
    table = new PirateLinkedList[size];
}

int PirateHashtable::getMoney(int pirateId) const {
    int index = hashFunction(pirateId);
    PirateNode* current = table[index].head;

    while (current != nullptr) {
        if (current->pirateId == pirateId) {
            return current->money;
        }
        current = current->next;
    }

    return 0;
}



PirateHashtable::~PirateHashtable() {
    delete[] table;
}

int PirateHashtable::hashFunction(int pirateId) const {
    return pirateId % tableSize;
}

bool PirateHashtable::contains(int pirateId) const {
    int index = hashFunction(pirateId);
    return table[index].contains(pirateId);
}

void PirateHashtable::insert(int pirateId, int fleetId, int money, int rank) {
    int index = hashFunction(pirateId);
    table[index].insert(pirateId, fleetId, money, rank);
    
}

bool PirateHashtable::update_salary(int pirateId, int salary) {
    int index = hashFunction(pirateId);
    return table[index].update_salary(pirateId, salary);
}


int PirateHashtable::getNumPirates(int fleetId) const {
    int index = hashFunction(fleetId);
    PirateLinkedList& list = table[index]; // Use reference to avoid null checks

    int count = 0;
    PirateNode* current = list.head;
    while (current != nullptr) {
        if (current->fleetId == fleetId) {
            count++;
        }
        current = current->next;
    }
    return count;
}


