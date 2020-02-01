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


/* TODO: Rewrite the recursive fibonacci function so that it will also build
 * the recursive function call binary tree at the same time.
 * In our solution, there will be another formal parameter used to build the
 * tree.
 */
int fibonacci(int n,btree_node* &a)
{   
    /* COMPLETE THIS FUNCTION */
    
    a=create_btree_node("f1");
    if(n==0){
        //while(a->left!=nullptr){a=a->left;}//a=create_btree_node("f0");
        cout<<n<<"c";
        return n;
    }
    else if (n==1){
        //while(a->right!=nullptr){a=a->right;}a=create_btree_node("f1");
        cout<<n<<"a";
        return n;
    }
    
        cout<<n<<"s";
        return (fibonacci(n-1,a->left)+fibonacci(n-2,a->right));
    
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
       int result = fibonacci(n, root);

        cout << "Fibonacci(" << n << ") = " << result << endl << endl;
    //root=create_btree_node("fn");
    //cout<< "Fibonacci(" << n << ") = " ;
    
    print_btree(root);
    delete_btree(root);
    return 0;
}