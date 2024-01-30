/**
 * @file share_ptr3.cpp
 * @author your name (you@domain.com)
 * @brief Implementing a Linked List Using std::shared_ptr
 * @version 0.1
 * @date 2024-01-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <memory>
using namespace std;
//define a singly linked list node
struct Node
{
    int data;
    shared_ptr<Node> next;

    Node(int val): data{val}, next{NULL} {}
};

class Linked_List
{
private:
    shared_ptr<Node> head;
public:
    Linked_List(/* args */);

    //insert a new node at the end of the linked list
    void insert(int val){
        shared_ptr<Node> newNode = make_shared<Node> (val);
        if (!head)
        {
            head = newNode;
        }
        else {
            shared_ptr<Node> current = head;
            while (current ->next)
            {
                current = current->next;
            }
            current->next = newNode;
            
        }
        
    }

    //Delete a node with a given value from the linked list

    void del(int val){
        
        if (!head)
        {
            return;
        }
        if (head->data == val)
        {
            head = head->next;
            return;
        }
        shared_ptr<Node> current = head;
        while (current->next && current->next->data != val)
        {
            current = current->next;
        }
        if (current->next && current->next->data == val)
        {
            current->next = current->next->next;
        }
    }
    void Print(){
        shared_ptr<Node> current = head;
        while (current)
        {
            cout << current->data << " -> " ;
            current = current->next;
        }
        cout << "NULL" << endl;
        
    }

    ~Linked_List();
};

Linked_List::Linked_List(/* args */) : head(NULL)
{

}

Linked_List::~Linked_List()
{
}

int main(){
    Linked_List linked_list;

    //Insert nodes into the linked list
    linked_list.insert(1);
    linked_list.insert(2);
    linked_list.insert(3);

    //  Print the linked list
    cout << "Linked list: ";
    linked_list.Print();

    // Delete a node and print the update linked list
    linked_list.del(2);
    cout << "Linked list after deleting 2: ";
    linked_list.Print(); 
}