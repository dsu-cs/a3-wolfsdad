#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include <vector>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);

    std::vector<int> inorder_helper(Node<T>* currentNode);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);

    std::vector<int> postorder_helper(Node<T>* currentNode);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);

    std::vector<T> *preorder_helper(Node<T>* currentNode);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // TODO: Add comments
    Node<T> *search_helper(Node<T>* currentNode, T& val);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
    //TODO: Add comments
    int count_helper(Node<T>* currentNode);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
std::vector<T> *BST<T>::inorder()
{
    Node<T> *currentNode, *prevNode; 
    std::vector<T> *vec = new std::vector<T>;
    std::vector<int> inorderData;
  
    currentNode = root; 
    while (currentNode != NULL) { 
  
        if (currentNode->get_left() == NULL) { 
            inorderData.push_back(currentNode->get_data()); 
            currentNode = (currentNode->get_right()); 
        } 
        else { 
  
            prevNode = currentNode->get_left(); 
            while (prevNode->get_right() != NULL && prevNode->get_right() != currentNode) 
                prevNode = prevNode->get_right(); 
  
            if (prevNode->get_right() == NULL) { 
                prevNode->set_right(currentNode); 
                currentNode = currentNode->get_left(); 
            } 

            else { 
                prevNode->get_right() == NULL; 
                inorderData.push_back(currentNode->get_data()); 
                currentNode = currentNode->get_right(); 
            } 
        } 
    }
    
    *vec = inorderData;
    return vec;

    // inorderData = inorder_helper(root);
    // *vec = inorderData;
    // return vec;
}

// template<class T>
// std::vector<int> BST<T>::inorder_helper(Node<T>* currentNode){
//     std::vector<int> inorderData;

//         if (currentNode != NULL){
//             inorder_helper(currentNode->get_left());
//             inorderData.push_back(currentNode->get_data());
//             inorder_helper(currentNode->get_right());
//         }

//     return inorderData; 
// }

template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    std::vector<int> preorderData;

    Node<T> *currentNode, *tempNode; 
    
    currentNode = root;
    // while (currentNode != NULL) {  
    //     
    //     if (currentNode->get_left() == NULL) {  
    //         preorderData.push_back(currentNode->get_data());
    //         currentNode = currentNode->get_right();  
    //     }  
    //     else {  
    //         
    //         tempNode = currentNode->get_left();  
    //         while (tempNode->get_right() && tempNode->get_right() != currentNode) {
    //             tempNode = tempNode->get_right();  

    //              
    //             if (tempNode->get_right() == currentNode) {  
    //                 tempNode->set_right(NULL);  
    //                 currentNode = currentNode->get_right();  
    //             }  

    //             
    //             else {  
    //                 preorderData.push_back(currentNode->get_data());  
    //                 tempNode->set_right(currentNode);  
    //                 currentNode = currentNode->get_left();  
    //             }  
    //         }
    //     }  
    // }   

    // Base Case 
    if (currentNode == NULL) {
        *vec = preorderData;
        return vec; 
    } else {
        preorderData.push_back(currentNode->get_data()); 
    
        while (preorderData.empty() == false) 
        { 
             
            if (currentNode->get_right() != NULL) {
                tempNode = currentNode->get_right();
                preorderData.push_back(tempNode->get_data()); 
            }
            if (currentNode->get_left() != NULL) {
                tempNode = currentNode->get_left();
                preorderData.push_back(tempNode->get_data()); 
            }
        } 
    }
    
    
    *vec = preorderData;
    return vec;
}


template<class T>
std::vector<T> *BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    return vec;
}

// template<class T>
// std::vector<int> BST<T>::postorder_helper(Node<T>* currentNode) {
//     std::vector<int> postorderData;

//     if (currentNode != NULL) {
//         postorderData = inorder_helper(currentNode->get_left()); 
    
//         
//         postorderData = inorder_helper(currentNode->get_right()); 
    
//         postorderData.push_back(currentNode->get_data());

//         return postorderData;
//     }
// }

template<class T>
void BST<T>::insert(T new_data)
{
    Node<T> * newNode = NULL;

    newNode = new Node<T>(new_data);

    Node<T> *tempNode = NULL;
    Node<T> *prevNode = NULL;

    tempNode = root;

    while(tempNode != NULL){
        prevNode = tempNode;
        if(tempNode->get_data() < newNode->get_data()){
            tempNode = tempNode->get_right();
        } else {
            tempNode = tempNode->get_left();
        }
    }

    if (prevNode == NULL){
        root = newNode;
    } else {
        if (prevNode->get_data() < newNode->get_data()){
            prevNode->set_right(newNode);
        } else {
            prevNode->set_left(newNode);
        }
    }
}

template<class T>
Node<T> *BST<T>::search(T val)
{
    return search_helper(root, val);
}

template<class T>
Node<T> *BST<T>::search_helper(Node<T>* currentNode, T& val)
{
    if (currentNode == NULL) {
        return NULL;
    } else if (currentNode->get_data() == val){
        return currentNode;
    } else {
        if (currentNode->get_data() > val) {
            return search_helper(currentNode->get_left(), val);
        } else {
            return search_helper(currentNode->get_right(), val);
        }
    }
}

template<class T>
void BST<T>::remove(T val)
{
    Node<T> *tempNode = NULL;
    Node<T> *currentNode = root;

    while (currentNode != NULL) { 
        if (currentNode->get_data() == val) { 
            if (!currentNode->get_left() && !currentNode->get_right()) {       
                if (!tempNode) { 
                    root = NULL;
                }
                else if (tempNode->get_left() == currentNode) {
                    tempNode->set_left(NULL);
                }
                else {
                    tempNode->set_right(NULL);
                }
            }
            else if (currentNode->get_left() && !currentNode->get_right()) {
                if (!tempNode) {
                root = currentNode->get_left();
                }
                else if (tempNode->get_left() == currentNode) {
                tempNode->set_left(currentNode->get_left());
                }
                else {
                tempNode->set_right(currentNode->get_left());
                }
            }
            else if (!currentNode->get_left() && currentNode->get_right()) {
                if (!tempNode) {
               root = currentNode->get_right();
                }
                else if (tempNode->get_left() == currentNode) {
               tempNode->set_left(currentNode->get_right());
                }
                else {
               tempNode->set_right(currentNode->get_right());
                }
            }
            else {
                Node<T> *successorNode = currentNode->get_right();
                while (successorNode->get_left() != NULL) {
                    successorNode = successorNode->get_left();
                    int successorData = successorNode->get_data();
                    remove(successorNode->get_data());
                    successorNode->set_data(successorData);
                }
            }
            return;
        }
        else if (currentNode->get_data() < val) { // Search right
            tempNode = currentNode;
            currentNode = currentNode->get_right();
        }
        else {                     // Search left
            tempNode = currentNode;
            currentNode = currentNode->get_left();
        }
    }
    return;
}

template<class T>
int BST<T>::get_size()
{
    int count = 0;
    if (root != NULL){
        count = count_helper(root);
    }
    return count;
}

template<class T>
int BST<T>::count_helper(Node<T>* currentNode)
{
    int count = 1; 

    if (currentNode->get_left() != NULL){
        count += count_helper(currentNode->get_left());
    }

    if (currentNode->get_right() != NULL){
        count += count_helper(currentNode->get_right());
    }

    return count;
}

