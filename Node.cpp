#include "Node.h"

// Node constructor definiton
Node::Node(){
    // TODO
    data = nullptr;
    next = nullptr;
    prev = nullptr;
};

// Node destructor definiton
Node::~Node(){
    // TODO
    if (data != nullptr) {
        delete data; // delete the FoodItem
    }
};

// printNode method definition
// display node's food data in the specified format
void Node::printNode() const {
    std::cout << std::left << std::setw(5) << data->id << "|";
    std::cout << std::left << std::setw(50) << data->name << "|";
    std::cout << "$" << std::right << std::setw(2) << data->price.dollars << ".";
    std::cout << std::setw(2) << std::setfill('0') << data->price.cents 
        << std::setfill(' ') << std::endl;
}

// writeNode method definition
// write node's food data in the specified format
void Node::writeNode(std::ostream& food_file) const {
    food_file << data->id << "|" 
        << data->name << "|" 
        << data->description << "|" 
        << data->price.dollars << "."
        << std::setw(2) << std::setfill('0') << data->price.cents 
        << std::setfill(' ') << std::endl;
}