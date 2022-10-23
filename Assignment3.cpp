// Assignment3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"BinarySearchTree.h"

using std::cout;
using std::cin;
using std::endl;

int mainMenu();

int main()
{
    BinarySearchTree BST;
    bool shouldExit = false;
    while (!shouldExit)
    {
        int OperationOption = mainMenu();
        if (OperationOption == 7)
            return 0;
        switch (OperationOption)
        {           
            case 1:
            {
                int key;
                cout << "\n Enter key to search for:";
                cin >> key;
                BST.searchNode(key);
                break;
            }
            case 2:
            {
                int key;
                cout << "\n Enter key to insert:";
                cin >> key;
                BST.insertNode(key);
                break;
            }
            break;
            case 3:
            {
                int key;
                cout << "\n Enter key to delete:";
                cin >> key;
                BST.deleteNode(key);
                break;
            }
            break;
            case 4:
            {
                BST.printBST(BST.head);
            }
            break;
            case 5:
            {
                BST.printSortedKeys(BST.head);
            }
            break;
            case 6:
            {
                BST.mostExpensivePath();
            }
            cin.clear();
            cin.ignore(123, '\n');
        }
    }
}

int mainMenu()
{
    bool operationValid = false;
    while (!operationValid)
    {
        int OperationOption;
        cout << "\nOperation Options :\n";
        cout << "1. Search for node\n";
        cout << "2. Insert new node\n";
        cout << "3. Delete node\n";
        cout << "4. Display all nodes\n";
        cout << "5. Print keys from highest to lowest \n";
        cout << "6. Print most expensive path cost from root to leaf node\n";
        cout << "7. Exit\n";

        cout << "Enter your operation option :";
        cin >> OperationOption;
        if (OperationOption < 1 || OperationOption > 7)
        {
            cout << "\n Invalid Operation Option. Please try again. \n \n";
            cin.clear();
            cin.ignore(123, '\n');
        }
        else
            return OperationOption;
    }
}