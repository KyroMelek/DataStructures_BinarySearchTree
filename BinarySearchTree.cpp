//
//  BinarySearchTree.cpp
//  Assignment3
//
//  Created by Kyrolos Melek
//

#include "BinarySearchTree.h"
#include<iostream>
#include<iomanip>
#include <queue>
#include<cmath>
#include <list>


using std::cout;
using std::cin;
using std::endl;
using std::queue;
using std::vector;
using std::list;

/// <summary>
/// Inserts node into BST
/// </summary>
/// <param name="key"></param>
void BinarySearchTree::insertNode(int key)
{
    node* iteratorNode = head;
    node* previousNode = head;
    //If empty tree
    if (head == nullptr)
    {
        head = new node;
        head->_key = key;
        cout << key << " inserted as head node\n";
        return;
    }

    //Find the node previous the node we want to insert
    while (iteratorNode != nullptr)
    {
        if (key > iteratorNode->_key)
        {
            previousNode = iteratorNode;
            iteratorNode = iteratorNode->rightChild;
        }
        else if (key < iteratorNode->_key)
        {
            previousNode = iteratorNode;
            iteratorNode = iteratorNode->leftChild;
        }
        else if (key == iteratorNode->_key)
        {
            cout << "Key already in tree\n";
            return;
        }
    }

    iteratorNode = new node{ key, nullptr, nullptr };

    //Correctly place node as left or right child of previous node
    if (key > previousNode->_key)
        previousNode->rightChild = iteratorNode;
    else
        previousNode->leftChild = iteratorNode;

    cout << key << " inserted successfully\n";

}

/// <summary>
/// Searches a tree for a node by its key
/// </summary>
/// <param name="key"></param>
/// <returns>
/// A pointer to an array where the first element is the parent of the desired node and the second is the desired node. If searched node is the head, parent node = nullptr
/// </returns>
BinarySearchTree::node** BinarySearchTree::searchNode(int key)
{
    static node* resultNodes[2] = { nullptr, nullptr };
    node* iteratorNode = head;
    node* previousNode = head;
    //If empty tree
    if (head == nullptr)
    {
        cout << "Node " << key << " not found, tree is empty\n";
        return resultNodes;
    }
    else if (head->_key == key)
    {
        resultNodes[1] = head;
        cout << "Key found in tree, it is the head node\n";
        return resultNodes;
    }

    //Find the node previous the node we want to insert
    while (iteratorNode != nullptr)
    {
        if (key > iteratorNode->_key)
        {
            previousNode = iteratorNode;
            iteratorNode = iteratorNode->rightChild;
        }
        else if (key < iteratorNode->_key)
        {
            previousNode = iteratorNode;
            iteratorNode = iteratorNode->leftChild;
        }
        else if (key == iteratorNode->_key)
        {
            cout << "Key found in tree\n";
            resultNodes[0] = previousNode;
            resultNodes[1] = iteratorNode;
            return resultNodes;
        }
    }

    cout << "Node " << key << " not found\n";
    return resultNodes;

}

/// <summary>
/// Deletes node from BST if it exists, using In-Order successor
/// </summary>
/// <param name="key"></param>
void BinarySearchTree::deleteNode(int key)
{
    node** result = searchNode(key);
    //Node to delete is not in the tree
    if (result[1] == nullptr)
    {
        return;
    }
    else
    {
        //Determines if the node we are trying to delete the left or right child of its parent node
        bool isLeftChild = false;
        if (result[0] != nullptr)
        {
            if (result[0]->leftChild == result[1])
                isLeftChild = true;
        }

        //Deleting a leaf node
        if (result[1]->leftChild == nullptr && result[1]->rightChild == nullptr)
        {
            //Deleting head with no children (BST has just the one head node)
            if (result[0] == nullptr)
            {
                result[1] = nullptr;
                head = nullptr;
            }
            else if (isLeftChild)            
                result[0]->leftChild = nullptr;
            else 
                result[0]->rightChild = nullptr;
            cout << key << " deleted successfully\n";
            delete result[1];
        }
        //Node to delete has only one child
        else if (result[1]->leftChild == nullptr || result[1]->rightChild == nullptr)
        {
            if (result[1]->leftChild != nullptr)
            {
                //Check if there is no parent, ie we are deleting the head node
                if (result[0] == nullptr)
                    head = result[1]->leftChild;                        
                else if (isLeftChild)
                    result[0]->leftChild = result[1]->leftChild;
                else
                    result[0]->rightChild = result[1]->leftChild;
            }
            else
            {
                //Check if there is no parent, ie we are deleting the head node
                if (result[0] == nullptr)
                    head = result[1]->rightChild;
                else if (isLeftChild)
                    result[0]->leftChild = result[1]->rightChild;
                else
                    result[0]->rightChild = result[1]->rightChild;
            }
            cout << key << " deleted successfully\n";
            delete result[1];
        }
        //Node to delete has two children
        //Using In-Order successor (smallest of right subtree)
        else
        {
            //Find the smallest node of the right subtree
            node* iteratorNode = result[1]->rightChild;    
            node* parentNode = result[1];
            while (iteratorNode->leftChild != nullptr)
            {
                parentNode = iteratorNode;
                iteratorNode = iteratorNode->leftChild;
            }
            result[1]->_key = iteratorNode->_key;

            if (iteratorNode->rightChild != nullptr)
            {
                if (parentNode->leftChild == iteratorNode)
                    parentNode->leftChild = iteratorNode->rightChild;
                else
                    parentNode->rightChild = iteratorNode->rightChild;
            }
            else if (parentNode->rightChild == iteratorNode)
                parentNode->rightChild = nullptr;
            else if(parentNode->leftChild == iteratorNode)
                parentNode->leftChild= nullptr;

            cout << key << " deleted successfully\n";
            delete iteratorNode;
        }
    }
}

/// <summary>
/// Prints out nodes in a tree format (Level order traversal)
/// </summary>
void BinarySearchTree::printBST(node* root)
{
    if (root == nullptr)
        return;

    queue<node*> level;
    level.push(root);
    level.push(nullptr);    

    queue<queue<node*>> LevelOrder;

    queue<node*> row;
    row.push(root);
    LevelOrder.push(row);
    queue<node*> nextRow;
    row = nextRow;
    while (!level.empty())
    {
        node* element = level.front();
        level.pop();        
        if (element == nullptr)
        {
            //cout << endl;
            LevelOrder.push(row);
            queue<node*> nextRow;
            row = nextRow;
            if (!level.empty())
            {
                level.push(nullptr);
                continue;
            }                
            else
                break;
        }
        //else
            //cout << element->_key;
        
        if (element->leftChild != nullptr)
        {
            level.push(element->leftChild);
            row.push(element->leftChild);
        }
        else
            row.push(nullptr);

        if (element->rightChild != nullptr)
        {
            level.push(element->rightChild);
            row.push(element->rightChild);
        }            
        else
            row.push(nullptr);
    }

    cout << "\n -------------------------------------------\n";
    int height = LevelOrder.size() - 1;
    int maxNumElementsOnBase = pow(2, height);
    int maxNumOfSubtreesOnBase = pow(2, height - 1);

    float leadingWhiteSpace = ( (maxNumOfSubtreesOnBase - 1) * 4 + (maxNumElementsOnBase) ) / 2;

    while (!LevelOrder.empty())
    {
        queue<node*> rowLevel = LevelOrder.front();
        LevelOrder.pop();

        for (int i = 0; i < leadingWhiteSpace; i++)
            cout << ' ';

        while (!rowLevel.empty())
        {
            if (rowLevel.front() == nullptr)
                cout << "   ";
            else
                cout << rowLevel.front()->_key;

            rowLevel.pop();    
            for (int i = 0; i < leadingWhiteSpace * 2; i++)
                cout << ' ';
        }

        leadingWhiteSpace = floor(leadingWhiteSpace / 2);

        cout << endl;        
    }
}

/// <summary>
/// Prints out keys of binary tree in sorted order from highest to lowest 
/// </summary>
/// RNL
void BinarySearchTree::printSortedKeys(node* root)
{
    if (root == nullptr)    
        return;    
    //Recursive Case
    printSortedKeys(root->rightChild);
    cout << root->_key << " ";
    printSortedKeys(root->leftChild);        
}

/// <summary>
/// Used by most expensive cost method.
/// Determines, through a pre order traversal, all path costs from root to leaf node
/// </summary>
/// <param name="root"></param>
/// <param name="runningSum"></param>
/// <param name="pathCost"></param>
/// <returns></returns>
bool preOrderTraversal(BinarySearchTree::node* root, int &runningSum, vector<int> &pathCosts)
{
    //Base Case
    if (root == nullptr)
        return false;
    //Recursive Case
    runningSum += root->_key;
    bool leftChild = preOrderTraversal(root->leftChild, runningSum, pathCosts);
    bool rightChild = preOrderTraversal(root->rightChild, runningSum, pathCosts);
    //If leaf node, push the path cost onto vector containing all path costs
    if(!leftChild && !rightChild)
        pathCosts.push_back(runningSum);
    runningSum -= root->_key;

}

/// <summary>
/// Finds the most expensive path cost from root to leaf node and displays it
/// </summary>
/// <returns></returns>
int BinarySearchTree::mostExpensivePath()
{
    vector<int> pathCosts;
    static int runningSum = 0;

    preOrderTraversal(head, runningSum, pathCosts);

    int maxCost = 0;
    for (int cost : pathCosts)
    {
        if (cost > maxCost)
            maxCost = cost;
        //cout << cost << " ";
    }

    cout << "\nThe max path cost from the root to a leaf node is: " << maxCost << endl;

    return 0;
}

BinarySearchTree::BinarySearchTree()
{

}

BinarySearchTree::~BinarySearchTree()
{

}
