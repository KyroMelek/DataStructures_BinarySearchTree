//
//  BinarySearchTree.hpp
//  Assignment3
//
//  Created by Kyrolos Melek

#pragma once
class BinarySearchTree
{
public:
    struct node
    {
        int _key;
        node* leftChild = nullptr;
        node* rightChild = nullptr;
    };
    node* head = nullptr;

    //Constructors
    BinarySearchTree();
    ~BinarySearchTree();

    //Public Methods
    //Searches for node by data
    node** searchNode(int data);
    //Inserts Node into BST
    void insertNode(int data);
    //Deletes node from BST by data
    void deleteNode(int data);
    //Prints all Nodes in BST
    void printBST(node* root);
    //Print out keys in sorted order (H->L)
    void printSortedKeys(node* root);
    //Return most expensive cost from root to leaf node
    int mostExpensivePath();
};