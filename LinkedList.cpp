#include "LinkedList.h"

// LinkedList constructor definition
LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   count = 0;
}

// LinkedList destructor definition
LinkedList::~LinkedList() {
   clear();
}

// Add node to the doubly-linked list in ascending order based on the food item name
void LinkedList::addNode(Node *newNode) {
    // if double-linked list is empty
    if (head == nullptr && tail == nullptr) {
        newNode->next = nullptr;
        newNode->prev = nullptr;
        // head and tail pointers are point to newNode
        head = newNode;
        tail = newNode;
    }
    // if new node's food name come before the head's food name
    else if (newNode->data->name < head->data->name) {
        newNode->prev = nullptr;
        // newNode next pointer points to head
        newNode->next = head;
        // head prev pointer points to newNode
        head->prev = newNode;
        // set head to new node
        head = newNode;
    }
    // if new node's food name come after the tail's food name
    else if (newNode->data->name > tail->data->name) {
        // newNode next pointer points to null
        newNode->next = nullptr;
        //newNode prev pointer points to tail node
        newNode->prev = tail;
        // tail node next pointer points to newNode
        tail->next = newNode;
        // set tail to newNode
        tail = newNode;
    }
    // to add new node between the head and tail
    else {
        Node* current = head;
        // Traverse the list until we find the correct position to insert the new node
        // While loop will stop when we reach the node before the tail or the new node name is less than the current node name
        while (current->next != nullptr && current->next != tail && current->next->data->name < newNode->data->name) {
            current = current->next;
        }
        // set the prev pointer of next node to newNode
        current->next->prev = newNode;
        // newNode next pointer points to next node
        newNode->next = current->next;
        //newNode prev pointer points to current node
        newNode->prev = current;
        // current node next pointer points to newNode
        current->next = newNode;
    }
    // increment node counter
    count++;
}

// Remove node from the doubly-linked list
void LinkedList::removeNode(Node *node) {
    // TODO
    // if there's only 1 node in the doubly-linked list
    if (head == node && tail == node) {
        head = nullptr;
        tail= nullptr;
    }
    // To remove head node
    else if (head == node) {
        node->next->prev = nullptr;
        head = node->next;
    }
    // to remove tail node
    else if (tail == node) {
        node->prev->next = nullptr;
        tail = node->prev;
    }
    // to remove node between the head and tail
    else {
        Node* current = head;
        // Traverse the list until we found the node to be removed
        while (current->next != node) {
            current = current->next;
        }
        // link the current node to the next node of the node to be removed
        current->next = node->next;
        // set the prev pointer of the next node to point to current node
        node->next->prev = current;
    }
    // delete node from doubly-linked list
    delete node;

    // decrement node counter
    count--;
}

// Get node based on given food id
Node* LinkedList::getNode(std::string id) const {
    Node* returnNode = nullptr;

    // if head node's food id matched the given id
    if (head->data->id == id) {
        returnNode = head;
    }
    // if tail node's food id matched the given id
    else if (tail->data->id == id) {
        returnNode = tail;
    }
    else {
        Node* current = head->next;
        // Traverse the linked list until we found the node matched the id or reach the node before the tail
        while(current != nullptr && current != tail && returnNode == nullptr){
            // if node is found, set returnNode to point to the node
            if (current->data->id == id) {
                returnNode = current;
            }
        current = current->next;
        }
    }

    return returnNode;
}

// Function to clear every node in doubly-linked list
void LinkedList::clear(){
    Node* current = head;
    Node* next_node = nullptr;
    
    // Traverse all node in the doubly-linked list
    while (current != nullptr) {
        // get the next node
        next_node = current->next;
        // delete current node from doubly-linked list
        removeNode(current);
        // set current node to next node
        current = next_node;
    }
}

// Display food menu
void LinkedList::printList() const {
    std::cout << "\nFood Menu" << std::endl;
    std::cout << std::string(9, '-') << std::endl;
    std::cout << std::left << std::setw(5) << "ID" << "|";
    std::cout << std::left << std::setw(50) << "Name" << "|";
    std::cout << std::left << std::setw(9) << "Price" << std::endl;
    std::cout << std::string(66, '-') << std::endl;

    Node* current = head;
    // Traverse all node in the doubly-linked list
    while (current != nullptr) {
        // Display the fooditem details to console
        current->printNode();
        // Iterate to next node
        current = current->next;
    }
}

// Generate the new food item id
std::string LinkedList::generateFoodID() const {
    Node* current = head;
    Node* lastIDNode = head;

    //Since the list is sorted alphabetically, the last node in the list won't necessarily have the latest ID.
    //So, we must keep track of the node with the latest ID rather than assuming the last node has it.
    while (current != nullptr) {

        if(current->data->id > lastIDNode->data->id){
            lastIDNode = current;
        }
        current = current->next;
    }

    // Convert the last food item id to number, which is the last 4 characters of the id
    std::string lastID = lastIDNode->data->id;
    std::string last4Chars = lastID.substr(lastID.length() - 4);
    int lastIDNumber = std::stoi(last4Chars) + 1;

    // Concat the lastIDNumber to the string "F" and add 0 until the length of the id is 5
    std::string newID;
    if (lastIDNumber < 10) {
        newID = "F000" + std::to_string(lastIDNumber);
    } else if (lastIDNumber < 100) {
        newID = "F00" + std::to_string(lastIDNumber);
    } else if (lastIDNumber < 1000) {
        newID = "F0" + std::to_string(lastIDNumber);
    }
    return newID;
}

// Write the node's food data into foods.dat file
void LinkedList::writeAllFoods(std::ostream& food_file) const {
    Node* current = head;
    // Traverse all node in the linked list
    while (current != nullptr) {
        // Write the fooditem details into foods.dat
        current->writeNode(food_file);
        // Iterate to next node
        current = current->next;
    }
 }