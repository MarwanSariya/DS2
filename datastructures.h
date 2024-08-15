#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#define N1 1000 // pirates
#define M 100   // fleets

#include <stdexcept>

class Node
{
public:
    int fleetId;
    int numShips;
    int numPirates;
    Node *next;

    Node(int id, int ships);

    void increase_num_pirates(int fleetId)
    {
        Node *current = this;
        while (current != nullptr)
        {
            if (current->fleetId == fleetId)
            {
                current->numPirates += 1;
                return;
            }
            current = current->next;
        }
    }
};

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    bool contains(int fleetId) const;
    void insert(int fleetId, int numShips);
    void clear();
    Node *head;
};

class Hashtable
{
public:
    Hashtable(int size);
    ~Hashtable();

    bool contains(int fleetId) const;
    int get_num_ships(int fleetId) const;
    void insert(int fleetId, int numShips);
    int hashFunction(int fleetId) const;

    LinkedList *table;
    int tableSize;
    int numofElements;

    void expand()
    {
        int newSize = tableSize * 2;                    // Double the table size
        LinkedList *newTable = new LinkedList[newSize]; // Allocate new table

        for (int i = 0; i < tableSize; i++)
        {
            Node *current = table[i].head;
            while (current != nullptr)
            {
                int newIndex = current->fleetId % newSize; // Rehash the fleetId for new table
                Node *next = current->next;                // Store the next node

                // Move current node to new table
                current->next = newTable[newIndex].head;
                newTable[newIndex].head = current;

                current = next; // Move to the next node
            }

            if (table[i].head != nullptr)
            {
                table[i].head = nullptr;
            }
        }

        delete[] table;      // Delete the old table
        table = newTable;    // Update to the new table
        tableSize = newSize; // Update the table size
    }

    Node *find(int fleetId) const
    {
        Node *current = table[hashFunction(fleetId)].head;
        while (current != nullptr)
        {
            if (current->fleetId == fleetId)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

private:
};

class PirateNode
{
public:
    int pirateId;
    int fleetId;
    int money;
    int rank;
    PirateNode *next;

    PirateNode(int pirateId, int fleetId, int money, int rank);
};

class PirateLinkedList
{
public:
    PirateLinkedList();
    ~PirateLinkedList();
    PirateNode *head;
    bool contains(int pirateId) const;
    void insert(int pirateId, int fleetId, int money, int rank);
    bool update_salary(int pirateId, int salary);
    void clear();

private:
};

class PirateHashtable
{
public:
    PirateHashtable(int size);
    ~PirateHashtable();
    int tableSize;
    int getMoney(int pirateId) const;
    bool contains(int pirateId) const;
    void insert(int pirateId, int fleetId, int money, int rank);
    bool update_salary(int pirateId, int salary);
    PirateLinkedList *table;
    int hashFunction(int pirateId) const;
    int getNumPirates(int fleetId) const;

    PirateNode &operator[](int pirateId)
    {
        int index = hashFunction(pirateId);
        PirateNode *current = table[index].head;
        while (current != nullptr)
        {
            if (current->pirateId == pirateId)
            {
                return *current;
            }
            current = current->next;
        }

        throw std::invalid_argument("Pirate not found");
    }

private:
};

#endif
// DATASTRUCTURES_H