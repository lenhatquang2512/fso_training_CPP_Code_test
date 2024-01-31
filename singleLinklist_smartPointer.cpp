/**
 * @file singleLinklist_smartPointer.cpp
 * @author NgDKhanh 
 * @brief single linked list with smart pointer
 * @version 0.1
 * @date 2024-01-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <memory>

#include <iostream>

/**
 * @brief Node class. Each node have data and a pointer which points 
 * to the next node in the list.
 * 
 * @tparam T data type
 */
template<typename T>
class Node
{
public:
    T data;
    std::shared_ptr<Node<T>> next;
    Node(T data_): data{data_}, next{nullptr} {}
    ~Node()
    {
        // if (nullptr != next)
        // {
        //     delete next;
        //     next = nullptr;
        // }        
        std::cout << "Deleting node " << this->data << std::endl;
    }
};

/**
 * @brief Single link list class. Each list contains head pointer
 * which point to the first node of the list.
 * It will look like this:
 * head-|
 *      |-->[node 1]-->[node2]-->...[node n]-->nullpointer
 * 
 * @tparam T data type
 */
template<typename T>
class singleLinklist
{
private:
    std::shared_ptr<Node<T>> head;
public:
    singleLinklist() 
    {
        head = nullptr;
    }
    ~singleLinklist()
    {
        std::cout << "Deleting the list" << std::endl;
    }
    /**
     * @brief Insert a new node at the end of the list.
     * 
     * @param data_ data of new node.
     */
    void insertTail(T data_)
    {
        if (head == nullptr)
        {
            head = new Node(data_);
        }
        else
        {
            std::shared_ptr<Node<T>> temp = head;
            while (nullptr != temp->next)
            {
                temp = temp->next;
            }
            std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(data_);
            temp->next = newNode;
        }
    }

    /**
     * @brief Insert new node at the end of the list.
     * 
     * @param data_ data of the new node.
     */
    void insertHead(T data_)
    {
        if (head == nullptr)
        {
            head = std::make_shared<Node<T>>(data_);
        }
        else
        {
            std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>(data_);
            temp->next = head;
            head = temp;
        }
    }

    /**
     * @brief Insert a new node after node which have data equal to dataFind 
     * parameter.
     * 
     * @param dataFind Data of node that we want to insert a new node after it.
     * @param data_ Data of new node.
     */
    void insertAfter(T dataFind, T data_)
    {
        if (head == nullptr)
        {
            head = std::make_shared<Node<T>>(data_);
        }
        else
        {
            std::shared_ptr<Node<T>> temp = this->findNode(dataFind);
            if (temp == nullptr)
            {
                std::cout << "Cannot find" << std::endl;
            }
            else
            {
                std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(data_);
                newNode->next = temp->next;
                temp->next = newNode;
            }
        }
    }

    /**
     * @brief Insert a new node before node which have data equal to dataFind 
     * parameter.
     * 
     * @param dataFind Data of node that we want to insert a new node before it.
     * @param data_ Data of new node.
     */
    void insertBefore(T dataFind, T data_)
    {
        if (head == nullptr)
        {
            head = std::make_shared<Node<T>>(data_);
        }
        else
        {
            std::shared_ptr<Node<T>> temp = head;
            if (temp->data == dataFind)
            {
                insertHead(data_);
            }
            else
            {
                while (nullptr != temp->next && temp->next->data != dataFind)
                {
                    temp = temp->next;
                }
                if(temp == head || temp->next == nullptr)
                {
                    std::cout << "Cannot find" << std::endl;
                }
                else
                {
                    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(data_);
                    newNode->next = temp->next;
                    temp->next = newNode;
                }
            }
        }
    }

    /**
     * @brief My dummy sorted insert. Need help to optimize this function :)
     * 
     * @param data_ Data of new node.
     * @param func Function pointer / lambda represents comparation.
     */
    void insertSort(T data_, bool (*func)(T a, T b))
    {
        if (head == nullptr)
        {
            head = std::make_shared<Node<T>>(data_);
        }
        else if (nullptr == head->next)
        {
            std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(data_);
            if (func(head->data, data_))
            {
                head->next = newNode;
            }
            else
            {
                newNode->next = head;
                head = newNode;
            }
        }
        else
        {
            std::shared_ptr<Node<T>> temp = head;
            if (func(data_, head->data))
            {
                insertHead(data_);
            }
            else
            {
                while (nullptr != temp->next && func(temp->next->data, data_))
                {
                    temp = temp->next;
                }         
                this->insertAfter(temp->data, data_);
            }
        }
    }

    /**
     * @brief Find node in list by its data value.
     * 
     * @param data_ Data of the node that we want to find.
     * @return Node* Pointer to that node.
     */
    std::shared_ptr<Node<T>> findNode(T data_)
    {
        std::shared_ptr<Node<T>> temp = head;
        while (nullptr != temp && temp->data != data_)
        {
            temp = temp->next;
        }
        if (temp != nullptr)
        {
            return temp;
        }
        return nullptr;
    }


    /**
     * @brief Traverse the list from the head to the tail 
     * of the list. For each node, print out data of that node.
     * 
     */
    void listTraverse()
    {
        if (head == nullptr)
        {
            std::cout << "Null list" << std::endl;
        }
        else
        {
            std::shared_ptr<Node<T>> temp = head;
            while (nullptr != temp)
            {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }
};

template<typename T>
bool smaller(T a, T b)
{
    return (a < b)?true:false;
}

template<typename T>
bool greater(T a, T b)
{
    return (a > b)?true:false;
}



int main(int argc, char const *argv[])
{
    std::shared_ptr<singleLinklist<int>> list = std::make_shared<singleLinklist<int>>();
    
    bool (*func)(int, int) = greater<int>;
    list->insertSort(3, func);
    list->insertSort(4, [](int a, int b)->bool { return (a > b)?true:false; });
    list->insertSort(1, func);
    list->insertSort(5, func);
    list->insertSort(2, [](int a, int b)->bool { return (a > b)?true:false; });
    list->listTraverse();
    return 0;
}
