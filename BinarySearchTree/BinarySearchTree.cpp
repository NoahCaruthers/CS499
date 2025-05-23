//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Noah Caruthers
// Version     : 2.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Binary Search Tree in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <cstdlib>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};
// Internal structure for tree node
struct Node {
    Bid bid;
    Node* left;
    Node* right;

    // default node constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

	// node constructor with bid
    Node(Bid aBid) :
        Node() {
        bid = aBid;
    }
};
//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};
/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}
/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}
/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(root);
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node;
        root->bid = bid;
    }
    else {
        // add Node root and bid
        addNode(root, bid);
    }
}
/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // remove node root bidID
    this->removeNode(root, bidId);
}
/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (current != nullptr) {
        // if match found, return current bid
        if (current->bid.bidId == bidId) {
            return current->bid;
        }
        // if bid is smaller than current node then traverse left
        if (current->bid.bidId < bidId) {
            current->left;
        }
        // else larger so traverse right
        else {
            current->right;
        }
    }
	// if no match found return empty bid
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // if node is larger then add to left
    if (node->bid.bidId > bid.bidId) {
        if (node == nullptr) {
            node->left = new Node;
            node->left->bid = bid;
        }
        else {
            addNode(node->left, bid);
        }
    }
    // if no left node
        // this node becomes left
    // else recurse down the left node
    else {
        // if no right node
        // this node becomes right
        if (node == nullptr) {
            node->right = new Node;
            node->right->bid = bid;
        }
        // recurse down the left node
        else {
            addNode(node->right, bid);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null pt
    if (node != nullptr) {
        inOrder(node->left); //InOrder not left
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
            << node->bid.fund << endl; //output bidID, title, amount, fund
        inOrder(node->right); //InOder right
    }
}
//added to clear LNK2019 issue, removeNode was not linking to Remove function
Node* BinarySearchTree::removeNode(Node* node, string bidId) {

    if (node == nullptr) {
        return node;
    }

    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = removeNode(node->left, bidId);
    }
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->right = removeNode(node->right, bidId);
    }
    else {
        // no kids
        if (node->left == nullptr && node->right == nullptr) {
			// delete node set node to null
            delete node;
            node = nullptr;
        }
        // one child, left kid
        else if (node->left != nullptr && node->right == nullptr) {
			// delete node set node to left
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        // one child, right kid
        else if (node->left == nullptr && node->right != nullptr) {
			// delete node set node to right
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // two children
        else {
			// smallest node on the right side
            Node* temp = node->right;
			// loop to find the left most node
            while (temp->left != nullptr) {
				// set temp to left
                temp = temp->left;
            }
			// set node to temp
            node->bid = temp->bid;
			// remove the nodes
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
    return node;
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}
/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // push this bid to the end
            bst->Insert(bid);
        }
    }
	// catch and display exception
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}
/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	// remove unwanted char from string
    str.erase(remove(str.begin(), str.end(), ch), str.end());
	// convert string to double
    return atof(str.c_str());
}
/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

	// Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

	// Display a menu with choises for the user
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit Program" << endl;
        cout << "Enter choice: ";
		// get user input
        cin >> choice;

		// switch statement to handle user input
        switch (choice) {

        case 1: //user choice 1

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

		case 2: //user choice 2
            bst->InOrder();
            break;

		case 3: //user choice 3
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			if (!bid.bidId.empty()) { //display bid if found
                displayBid(bid);
            }
            else {
				cout << "Bid Id " << bidKey << " not found." << endl; //display if not found
            }
			//display time to find bid
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

		case 4: //user choice 4
            bst->Remove(bidKey);
            break;

		default: //Default case
            cout << "Please eanter a selection" << endl;

        }
    }
    cout << "Good bye." << endl;

    return 0;
}
