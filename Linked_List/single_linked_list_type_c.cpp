/**
 * @file single_linked_list_type_c.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node
{
    int data;
    struct Node* next;
    
};
void Insert_Begin(struct Node** head_ref, int new_data){
    struct Node *newnode = new Node();

    // insert data
    newnode->data = new_data;
    newnode->next = (*head_ref);

    // move head to new data
    (*head_ref) = newnode;
}

void Insert_After(struct Node* prev_node, int new_data){
    if (prev_node == NULL)
    {
        cout << "the given previous node cannot be null";
        return ;
    }
    
    struct Node* newnode = new Node();

    // insert data 
    newnode->data = new_data;
    newnode->next = (prev_node)->next;
    prev_node->next = newnode;

}

void Insert_End(struct Node** head_ref, int new_data){
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    newnode->data = new_data;
    newnode->next = NULL;

    if(*head_ref == NULL){
        *head_ref = newnode;
        return;
    }

    while (last->next != NULL) last = last->next;
    last->next = newnode;
    return;
   
    
}

// delete node
   
void deleteNode(struct Node**head_ref, int key){
    struct Node* temp = *head_ref, *prev;
    if (temp != NULL && temp->data == key)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    // Find the key ti be deleted
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;

    }

    // If the key is not present
    if (temp == NULL) return;
    //remove the node
    {
    prev->next = temp->next;
    free(temp);
    }
   }

//Search a node
    bool searchNode(struct Node** head_ref, int key){
        struct Node* current = *head_ref;
        while (current != NULL)
        {
            if (current->data == key)
            {
                current = current->next;
            }
        
            
        }
        return false;
    }
// Sort the linked list
void sortLinkedList(struct Node** head_ref) {
  struct Node *current = *head_ref, *index = NULL;
  int temp;

  if (head_ref == NULL) {
  return;
  } else {
  while (current != NULL) {
    // index points to the node next to current
    index = current->next;

    while (index != NULL) {
    if (current->data > index->data) {
      temp = current->data;
      current->data = index->data;
      index->data = temp;
    }
    index = index->next;
    }
    current = current->next;
  }
  }
}

void Print(struct Node* node){
    while (node != NULL)
    {
        cout << node->data << " ";
        node = node->next;
    }
    
}
    

int main(){
    struct Node* head = NULL;
    Insert_End(&head, 1);
    Insert_Begin(&head, 2);
    Insert_After(head->next, 4);
    Print(head);
}