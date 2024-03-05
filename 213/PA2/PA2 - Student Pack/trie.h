#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    void deleteTrieNode(TrieNode* root);
    void populateVector(vector<T*> &results, TrieNode* node);
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    /* IMPLEMENT THIS */
    deleteTrieNode(root);
}
template <class T>
void Trie<T>::deleteTrieNode(TrieNode* node) {
    /* IMPLEMENT THIS */
    if(node){
    for(int i = 0; i < 128; i++){
        if((node->children)[i]){
            deleteTrieNode((node->children)[i]);
        }
    }
    delete node->data;
    delete node;
    }
}
template <class T>
Trie<T>& Trie<T>::insert(const string& key) {
    /* IMPLEMENT THIS */
    char c = '\0';
    TrieNode* node  = root;
    if(search(key)!=NULL){return *this;}
    for(int i = 0; i < (int)key.length() ; i++){
        c = key[i];
        if((node->children)[(int)c]==NULL){
            (node->children)[(int)c] = new TrieNode(c);
        }
        
        node = (node->children)[(int)c];
        
    }
    node->isEndOfKey = true;
    node->data = new T(key);

    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    /* IMPLEMENT THIS */
    char c = '\0';
    TrieNode* node = root;
    if(!node){return NULL;}
    for(int i = 0; i < (int)username.length(); i++){
        c = username[i];
        if((node->children)[(int)c]==NULL){
            return NULL;
        }
        node = (node->children)[(int)c];

    }
    if(node && node->isEndOfKey){
        return node->data;
    }
    return NULL;
}

template <class T>
void Trie<T>::remove(std::string username) {
    /* IMPLEMENT THIS */
    char c = '\0';
    TrieNode* node = root;
    if(!node){return;}
    for(int i = 0; i < (int)username.length(); i++){
        c = username[i];
        if((node->children)[(int)c]==NULL){
            return;
        }
        node = (node->children)[(int)c];

    }
    if(node && node->isEndOfKey){
        node->isEndOfKey = false;
    }
   
}

template <class T>
void Trie<T>::findStartingWith(string prefix,vector<T*> &results) {
/* IMPLEMENT THIS */
    char c = '\0';
    TrieNode* node = root;
    if(!node){return;}
    for(int i = 0; i < (int)prefix.length(); i++){
        c = prefix[i];
        if((node->children)[(int)c]==NULL){
            return;
        }
        node = (node->children)[(int)c];

    }
    populateVector(results,node);
}
template <class T>
void Trie<T>::populateVector(vector<T*> &results, TrieNode* node){
    if(node == NULL){ return;}
    if(node->isEndOfKey){
        results.push_back(node->data);
    }
    for(int i = 0; i < 128; i++){

        if((node->children)[i]){
            populateVector(results,(node->children)[i]);
        }
    }
}
template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
/* IMPLEMENT THIS */
}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < (int)primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}

