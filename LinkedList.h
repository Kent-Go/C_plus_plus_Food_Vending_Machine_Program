#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <iostream>
#include <iomanip>

class LinkedList
{
public:
    // LinkedList constructor declaration
    LinkedList();

    // LinkedList destructor declarations
    ~LinkedList();

    // Add new node into doubly-linked list
    void addNode(Node *newNode);

    // remove existing node from doubly-linked list
    void removeNode(Node *aNode);

    // remove all existing nodes from doubly-linked list
    void clear();

    // Get node based on given food id
    Node* getNode(std::string id) const;

    // display food menu
    void printList() const;

    // generate new foodID
    std::string generateFoodID() const;

    // write all node's food item from doubly-linked list into file
    void writeAllFoods(std::ostream& outfile) const;

private:
    // the beginning of the list
    Node* head;

    // the end of the list
    Node* tail;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


