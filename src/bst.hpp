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
    // Recursive helper function for searching tree
    // param: node and value of node being searched for
    // returns found node
    Node<T> *search_helper(Node<T>* currentNode, T& val);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
    // Helper for calling itself recursively
    // param: Current node being considered for count
    // returns: number of nodes recursed
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
    
    // Store root for iterative loop
    currentNode = root; 
    while (currentNode != NULL) { 
        
        // If left is NULL push and continue with right node
        if (currentNode->get_left() == NULL) { 
            inorderData.push_back(currentNode->get_data()); 
            currentNode = (currentNode->get_right()); 
        } 
        else { 
            // Store previous node for iterative comparison
            prevNode = currentNode->get_left(); 

            // Continue while right or previous exists and also doesn't equal current node
            while (prevNode->get_right() != NULL && prevNode->get_right() != currentNode) 
                prevNode = prevNode->get_right(); 
  
            // If right is NULL store previous's right and current is set to it's left
            if (prevNode->get_right() == NULL) { 
                prevNode->set_right(currentNode); 
                currentNode = currentNode->get_left(); 
            }
            else {
                prevNode->set_right(NULL); 
                inorderData.push_back(currentNode->get_data()); 
                currentNode = currentNode->get_right(); 
            } 
        } 
    }
    
    // Point to int vector where traversal is stored
    *vec = inorderData;

    return vec;
}

template<class T>
std::vector<T> * BST<T>::preorder()
{
    Node<T> *currentNode, *tempNode;
    std::vector<T> *vec = new std::vector<T>;
    std::vector<int> preorderData;

    // Store root for iterative loop
    currentNode = root;

    while (currentNode != NULL) {  

        // If left is NULL store it and get right
        if (currentNode->get_left() == NULL) {  
            preorderData.push_back(currentNode->get_data());
            currentNode = currentNode->get_right();
        }  else {

            // Store left for iterative comparison
            tempNode = currentNode->get_left();

            // Continue while right exists and also doesn't equal currentNode
            while (tempNode->get_right() != NULL && tempNode->get_right() != currentNode) {
                tempNode = tempNode->get_right();
            }
        }

        // Store NULL to previous right pointer and assign current right to current node
        if (tempNode->get_right() == currentNode) {
            tempNode->set_right(NULL);
            currentNode = currentNode->get_right();
        }

        // Add current to vector, set temporary node's right pointer to current and current set to left
        else {
            preorderData.push_back(currentNode->get_data());
            tempNode->set_right(currentNode);
            currentNode = currentNode->get_left();
        }
    }

    // Point to int vector where traversal is stored
    *vec = preorderData;

    return vec;
}


template<class T>
std::vector<T> *BST<T>::postorder()
{
    Node<T> *currentNode, *tempNode;
    std::vector<T> *vec = new std::vector<T>;
    std::vector<int> postorderData;
    std::vector<Node<T>*> tempData;

    // Store root in node
    currentNode = root;
    
    // Add base value to Node vector
    tempData.push_back(currentNode);

    while(!tempData.empty()){

        // Sets the back node's data to tempNode
        tempNode = tempData.back();

        // Removes back node from Node vector
        tempData.pop_back();

        // Add recently created Node vector data to int vector
        postorderData.push_back(tempNode->get_data());

        // If left Node found push it to Node vector
        if(tempNode->get_left() != NULL){
            tempData.push_back(tempNode->get_left());
        }
        
        // If right Node found push it to Node vector
        if(tempNode->get_right() != NULL){
            tempData.push_back(tempNode->get_right());
        }
    }

    // Point to int vector where traversal is stored
    *vec = postorderData;

    return vec;
}

template<class T>
void BST<T>::insert(T new_data)
{
    Node<T> * newNode = NULL;
    Node<T> *tempNode = NULL;
    Node<T> *prevNode = NULL;

    // Store data to be inserted in new node
    newNode = new Node<T>(new_data);

    // Store root for iteration
    tempNode = root;

    while(tempNode != NULL){
        prevNode = tempNode;

        // If current node is smaller than new data head right...
        if(tempNode->get_data() < newNode->get_data()){
            tempNode = tempNode->get_right();

        //...if not turn left
        } else {
            tempNode = tempNode->get_left();
        }
    }

    if (prevNode == NULL){
        root = newNode;
    } else {
        // If predecessor node is smaller than new data set right to new data...
        if (prevNode->get_data() < newNode->get_data()){
            prevNode->set_right(newNode);
        //...if not set left to new node
        } else {
            prevNode->set_left(newNode);
        }
    }
}

template<class T>
Node<T> *BST<T>::search(T val)
{
    // Return Node found from recursive function
    return search_helper(root, val);
}

template<class T>
Node<T> *BST<T>::search_helper(Node<T>* currentNode, T& val)
{
    // If current node doesn't exist return NULL...
    if (currentNode == NULL) {
        return NULL;
    
    // ...else if current node found, return it...
    } else if (currentNode->get_data() == val){
        return currentNode;

    // ...else traverse inorder recursively based on current node size
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

        // If node to be deleted is found...
        if (currentNode->get_data() == val) { 

            // If left and right do not exist...
            if (!currentNode->get_left() && !currentNode->get_right()) {     
                // If tempNode does not exist...  
                if (!tempNode) { 
                    root = NULL;
                }
                // ... else if temp equals current clear left...
                else if (tempNode->get_left() == currentNode) {
                    tempNode->set_left(NULL);
                }
                // .. else clear right
                else {
                    tempNode->set_right(NULL);
                }
            }
            // ... else if left exists and right does not...
            else if (currentNode->get_left() && !currentNode->get_right()) {
                // If tempNode does not exist...
                if (!tempNode) {
                    root = currentNode->get_left();
                }
                // ... else if temp left eqauls current set temp left to current left ...
                else if (tempNode->get_left() == currentNode) {
                    tempNode->set_left(currentNode->get_left());
                }
                // ... else set right to current left
                else {
                    tempNode->set_right(currentNode->get_left());
                }
            }
            // ... else if current left doesn't exist but right does....
            else if (!currentNode->get_left() && currentNode->get_right()) {
                // If temp does not exist
                if (!tempNode) {
                    root = currentNode->get_right();
                }
                // ... else if temp left equals current set temp left to current right...
                else if (tempNode->get_left() == currentNode) {
                    tempNode->set_left(currentNode->get_right());
                }
                // ... else set right to current right
                else {
                    tempNode->set_right(currentNode->get_right());
                }
            }
            // ... else create successor node from current right
            else {
                Node<T> *successorNode = currentNode->get_right();

                // Get successor left until left is empty. Store successor data
                while (successorNode->get_left() != NULL) {
                    successorNode = successorNode->get_left();
                    int successorData = successorNode->get_data();
                    remove(successorNode->get_data());
                    successorNode->set_data(successorData);
                }
            }

            return;
        }
        // ... else if current node is smaller than value to be removed get right...
        else if (currentNode->get_data() < val) {
            tempNode = currentNode;
            currentNode = currentNode->get_right();
        }

        // ... else get left
        else {
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
        // Initiates recursive function
        count = count_helper(root);
    }

    return count;
}

template<class T>
int BST<T>::count_helper(Node<T>* currentNode)
{
    int count = 1; 

    // If left exists add to count and call recursive function
    if (currentNode->get_left() != NULL){
        count += count_helper(currentNode->get_left());
    }
    if (currentNode->get_right() != NULL){
        count += count_helper(currentNode->get_right());
    }

    return count;
}