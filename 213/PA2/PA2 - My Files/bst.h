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
    void remove(TreeNode* &temp ,std::string key);
    void tree2vector(vector<TreeNode> &result,TreeNode* root);
    void deletebst(TreeNode* root);
    TreeNode* getMin(TreeNode* r){
        TreeNode* temp = r;
        while(temp){
            if(temp->left){
                temp = temp->left;
            }
            else{
                break;
            }
        }
        return temp;}
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
    /* IMPLEMENT THIS */
        if(root != NULL){
            deletebst(root);
        }
    }
    template <class T>
    void BST<T>::deletebst(TreeNode* node){
            if(node->right){
                deletebst(node->right);
            }
            if(node->left){
                deletebst(node->left);
            }
            delete node;
        
    }
    

    // Insert function for BST.    
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
        /* IMPLEMENT THIS */
        if(isEmpty()){
            root  = new TreeNode(key, value);
            return *this;
        }
        TreeNode* temp = root;
        while(temp){
            if(temp->key > key){
                if(temp->left){
                    temp = temp->left;
                }
                else{
                    temp->left = new TreeNode(key, value);
                    break;
                }
            }
            else if(temp->key < key){
                if(temp->right){
                    temp = temp->right;
                }
                else{
                    temp->right = new TreeNode(key, value);
                    break;
                }
            }
            else{
                break;
            }
        }
        
        return *this;
    
    }
    
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
     /* IMPLEMENT THIS */
     if(root == NULL){
            return false;
        }
        TreeNode* temp = root;
        while(temp){
            if(temp->key > value){
                if(temp->left){
                    temp = temp->left;
                }
                else{
                    return false;
                }
            }
            else if(temp->key < value){
                if(temp->right){
                    temp = temp->right;
                }
                else{
                    return false;
                }
            }
            else{
                return true;
            }
        }
        
        return false;
    }
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        /* IMPLEMENT THIS */
        if(search(key)){
            remove(root, key);
        }
    }
    
    template <class T>
    void BST<T>::remove(TreeNode* &temp, std::string key) {
        if(temp->key > key){
            remove(temp->left, key);
        }
        else if(temp->key < key){
            remove(temp->right, key);
        }
        else{
            if(temp->right != NULL && temp->left != NULL){
                TreeNode* minimal = getMin(temp->right);
                temp->data = minimal->data;
                temp->key = minimal->key;
                remove(temp->right, temp->key);
            }
            else{
                TreeNode* old = temp;
                temp = (temp->left!=NULL)? temp->left : temp->right;
                delete old;
            }
        
        }
    }
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        tree2vector(result,root);
        return result;
    }
    template <class T>
    void BST<T>::tree2vector(vector<TreeNode> &result,TreeNode* root) {
        if(root == NULL){
            return;
        }
        if(root->left){
            tree2vector(result, root->left);
        }
        
        result.push_back(*root);
        
        if(root->right){
            tree2vector(result,root->right);
        }
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
    /* IMPLEMENT THIS */
    vector<TreeNode> result1 = tree2vector(root);
    vector<TreeNode> result2 = tree2vector(bst->root);
    
    if(result1.empty() && result2.empty()){
        return NULL;
    }
    vector<TreeNode> result3;
    int i = 0, j = 0;
    
    while(i < (int)result1.size() && j < (int)result2.size()){
        if((result1[i]).key == (result2[j]).key){
            result3.push_back(result1[i]);
            i++;
            j++;
        }
        else if((result1[i]).key < (result2[j]).key){
            result3.push_back(result1[i]);
            i++;
        }
        else{
            result3.push_back(result2[j]);
            j++;
        }
    }
    if(i < (int)result1.size()){
        while(i < (int)result1.size()){
            result3.push_back(result1[i]);
            i++;
        }
    }
    else if(j < (int)result2.size()){
        while(j < (int)result2.size()){
            result3.push_back(result2[j]);
            j++;
        }
    }
    BST<T>* newbst = new BST<T>;
    while(!result3.empty()){
        
        newbst->insert((result3[0]).key, (result3[0]).data);
        result3.erase(result3.begin());
        
    }
    
    return newbst;
        
    }
        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
    /* IMPLEMENT THIS */
    vector<TreeNode> result1 = tree2vector(root);
    vector<TreeNode> result2 = tree2vector(bst->root);
    
    if(result1.empty() && result2.empty()){
        return NULL;
    }
    
    vector<TreeNode> result3;
    int i = 0, j = 0;
    
    while(i < (int)result1.size() && j < (int)result2.size()){
        if((result1[i]).key == (result2[j]).key){
            result3.push_back(result1[i]);
            i++;
            j++;
        }
        else if((result1[i]).key < (result2[j]).key){
            i++;
        }
        else{
            j++;
        }
    }
    
    BST<T>* newbst = new BST<T>;
    while(!result3.empty()){
        
        newbst->insert((result3[0]).key, (result3[0]).data);
        result3.erase(result3.begin());
        
    }
    
    return newbst;
    
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


