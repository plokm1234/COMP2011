#include <iostream>     /* File: lab10.cpp */
#include <sstream> 
using namespace std;

/* The data type is changed to string */
struct btree_node       // A node in a binary tree
{
    string data;        // To store the recursive call content
    btree_node* left;   // Left sub-tree or called left child
    btree_node* right;  // Right sub-tree or called right child
};

/* The data type is changed to string */
btree_node* create_btree_node(string data) 
{
    btree_node* node = new btree_node;
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

/* This function is exactly the same as in the lecture notes */
void delete_btree(btree_node*& root) // By recursion
{
    if (root == nullptr) return;     // Base case

    delete_btree(root->left);        // Recursion on the left subtree
    delete_btree(root->right);       // Recursion on the right subtree
    delete root;
    root = nullptr;
}

/* This function is exactly the same as in the lecture notes */
void print_btree(const btree_node* root, int depth = 0) 
{
    if (root == nullptr)   // Base case
        return;

    print_btree(root->right, depth+1);// Recursion: right subtree

    for (int j = 0; j < depth; j++)   // Print the node data
        cout << '\t';
    cout << root->data << endl;

    print_btree(root->left, depth+1); // Recursion: left subtree
}


/* TODO:
 * This function is modified, and additional 2nd argument is used to build the
 * function call binary tree 
 */
int fibonacci(int n, btree_node*& root)
{
    ostringstream oss;
    oss << "f(" << n << ")";
    string call = oss.str();
    root = create_btree_node(call); // Create root node

    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    int left_value = fibonacci(n-1, root->left);
    int right_value = fibonacci(n-2, root->right);
    return left_value + right_value;
}


/* TODO:
 * Sample driver program
 */
int main()
{   
    int n;
    btree_node* root = nullptr;        // Root of the call tree to be constructed
    
    cout << "\n\nEnter an integer to compute its Fibonacci number (-ve number to stop): ";
    cin >> n;
    
    while (n >= 0)
    {
        int result = fibonacci(n, root);

        cout << "Fibonacci(" << n << ") = " << result << endl << endl;
        print_btree(root);             // Print the resulting call tree

        delete_btree(root);            // Delete the current call tree
        root = nullptr;                // Reset root to prepare for the next call
        
        cout << "\n\nEnter an integer to compute its Fibonacci number (-ve number to stop): ";
        cin >> n;
    }
    
    return 0;
}