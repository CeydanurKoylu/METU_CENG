#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void removeHelper(TreeNode* &node, std::string key);
    TreeNode* getMin(TreeNode* node){
        TreeNode* curr = node;
        if(!curr) return NULL;
        while(curr->left){
            curr = curr->left;
        }
        return curr;
    }
    bool searchHelper(TreeNode* node,std::string key) const;
    void deletion(TreeNode* node);
    void tree2vector(vector<TreeNode> &result, TreeNode* node);
    void vectorToBalancedBST(vector<TreeNode> &arr, TreeNode* &node, int start, int end);
    BST<T>& insert(const string key, const T& value, TreeNode* &node);
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
    /* IMPLEMENT THIS */
        deletion(root);
    }
    template <class T>
    void BST<T>::deletion(TreeNode* node) {
    /* IMPLEMENT THIS */
        if(node){
            deletion(node->left);
            deletion(node->right);
            delete node;
        }
        
    }

    // Insert function for BST.    
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
             /* IMPLEMENT THIS */
        return insert(key,value,root);
    }

    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value, TreeNode* &node){
        if(!node){
            node = new TreeNode(key, value);
            return *this;
        }
        else if(key > node->key){
            return insert(key, value, node->right);
        }
        else if(key < node->key){
            return insert(key, value, node->left);
        }
        else{
            return *this;
        }
    }
    
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
     /* IMPLEMENT THIS */
        return searchHelper(root, value);
    }
    template <class T>
    bool BST<T>::searchHelper(TreeNode* node,std::string key) const {
     /* IMPLEMENT THIS */
     if(!node) return false;
        if(key > node->key){
            searchHelper(node->right, key);
        }
        else if(key < node->key){
            searchHelper(node->left, key);
        }
        else{
            return true;
        }
    }
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        /* IMPLEMENT THIS */
        removeHelper(root,key);

    }
    template <class T>
    void BST<T>::removeHelper(TreeNode* &node,std::string key) {
        /* IMPLEMENT THIS */
        if(!node) return;
        if(key > node->key){
            removeHelper(node->right, key);
        }
        else if(key < node->key){
            removeHelper(node->left, key);
        }
        else{
            if(node->left && node->right){
                TreeNode* temp = getMin(node->right);
                node->data = temp->data;
                node->key = temp->key;
                removeHelper(node->right, temp->key);
            }
            else{
                TreeNode* temp = node;
                node = ((node->right)? node->right : node->left);
                delete temp;
            }
        }
        
    }
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        tree2vector(result, root);
        return result;
    }
    template <class T>
    void BST<T>::tree2vector(vector<TreeNode> &result, TreeNode* node) {
        if(node){
            if(node->left){
                tree2vector(result, node->left);
            }
            result.push_back(*node);
            if(node->right){
                tree2vector(result, node->right);
            }
        }
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
    /* IMPLEMENT THIS */
        vector<TreeNode> vector1 = tree2vector(root);
        vector<TreeNode> vector2 = tree2vector(bst->getRoot());
        vector<TreeNode> vector3;
        while(!vector1.empty() && !vector2.empty()){
            if((vector1[0]).key < (vector2[0]).key){
                vector3.push_back(vector1[0]);
                vector1.erase(vector1.begin());
            }
            else{ 
                vector3.push_back(vector2[0]);
            if((vector1[0]).key == (vector2[0]).key){
                vector1.erase(vector1.begin());
            }
            vector2.erase(vector2.begin());
            }
        }
        while(!vector1.empty()){
            vector3.push_back(vector1[0]);
            vector1.erase(vector1.begin());
        }
        while(!vector2.empty()){
            vector3.push_back(vector2[0]);
            vector2.erase(vector2.begin());
        }
        BST<T> * newBST = new BST<T>; 
        vectorToBalancedBST(vector3, newBST->root, 0, (int)vector3.size() - 1 );
        return newBST; 
    }

    template <class T>
    void BST<T>::vectorToBalancedBST(vector<TreeNode> &arr, TreeNode* &node, int start, int end) {
    /* IMPLEMENT THIS */
        if(start > end) return;
        int mid = (start+end)/2 ;
        node = new TreeNode((arr[mid]).key,(arr[mid]).data);
        vectorToBalancedBST(arr, node->left, start, mid-1);
        vectorToBalancedBST(arr, node->right, mid+1, end);
    }
        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
    /* IMPLEMENT THIS */
    vector<TreeNode> vector1 = tree2vector(root);
    vector<TreeNode> vector2 = tree2vector(bst->getRoot());
    vector<TreeNode> vector3;
    
        while(!vector1.empty() && !vector2.empty()){
            if((vector1[0]).key < (vector2[0]).key){
                vector1.erase(vector1.begin());
            }
            else if((vector1[0]).key > (vector2[0]).key){
                vector2.erase(vector2.begin());
            }
            else{ 
                vector3.push_back(vector2[0]);
                vector2.erase(vector2.begin());
                vector1.erase(vector1.begin());
            }
        }
        BST<T> * newBST = new BST<T>; 
        vectorToBalancedBST(vector3, newBST->root, 0, (int)vector3.size() - 1 );
        return newBST; 
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }


