/*
 * Author: KhanhND52
 * Date: 26/1/2024
 *
 */

#include <iostream>

int max(int a, int b)
{
    return (a > b)?a:b;
}

template<typename T>
class binarySearchTree
{
public:
    T data;
    binarySearchTree* left;
    binarySearchTree* right;

    binarySearchTree(T data_) :
    data{data_}, left{nullptr}, right{nullptr} {};
    ~binarySearchTree()
    {   
        if (left != nullptr)
        {
            std::cout <<  "del " << this->left->data << std::endl;
            delete left;
        }

        if (right != nullptr)
        {
            std::cout <<  "del " <<  this->right->data << std::endl;
            delete right;
        }
    };

    void insert(T data_)
    {
        if (data_ < this->data)
        {
            if (this->left != nullptr)
            {
                std::cout << "left" << std::endl;
                this->left->insert(data_);
            }
            else
            {
                std::cout << "left here" << std::endl;
                left = new binarySearchTree<T>(data_); 
            }
        }
        else 
        {
            if (this->right != nullptr)
            {
                std::cout << "right" << std::endl;
                this->right->insert(data_);
            }
            else
            {
                std::cout << "right here" << std::endl;
                right = new binarySearchTree<T>(data_); 
            }
        }
    }

    void deepTranverse()
    {
        if (this->left != nullptr)
        {
            this->left->deepTranverse();
        }

        std::cout << this->data << std::endl;
        
        if (this->right != nullptr)
        {
            this->right->deepTranverse();
        }     
    }

    int height()
    {
        if (this == nullptr)
        {
            return 0;
        }
           
        int leftHeight = this->height();
        int rightHeight = this->height();
        
    }

    void breadthTranverse()
    {
        if (this != nullptr)
        {
            // std::cout << this->data << std::endl;
            if (this->left != nullptr)
            {
               std::cout << this->left->data << std::endl;
            }
            if (this->right != nullptr)
            {
                std::cout << this->right->data << std::endl;
            }
            if (this->left != nullptr) this->left->breadthTranverse();
            if (this->right != nullptr) this->right->breadthTranverse();
        }
        
    }
};

int main(int argc, char const *argv[])
{
    binarySearchTree<int>* a = new binarySearchTree<int>{10};
    a->insert(5);
    a->insert(12);
    a->insert(6);
    a->insert(3);
    a->insert(13);
    a->insert(11);
    a->insert(7);
    a->insert(2);
    a->insert(4);
    a->breadthTranverse();
    delete a;
    return 0;
}






