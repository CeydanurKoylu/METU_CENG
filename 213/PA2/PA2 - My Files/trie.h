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
    void deleteTrieNode(TrieNode* node);
    void StartsWithQuestion(std::string key, vector<TrieNode*> &possible, TrieNode* nod, int number);
    void StartsWithStar(std::string key, vector<TrieNode*> &possible, TrieNode* nod);
    void StartsWithQuestionStar(std::string key, vector<TrieNode*> &possible, TrieNode* nod, int number);
    void findStartingWithNodes(string prefix, vector<TrieNode*> &possible, TrieNode* start);
    bool inTheResults(vector<T*> &results, T* &obj);
    
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
Trie<T>& Trie<T>::insert(const string& key) {
    /* IMPLEMENT THIS */
    char c = '\0';
    int i = 0;
    int length = key.length();
    TrieNode* node = root;
    if(search(key)){
        return *this;
    }
    for(i = 0; i < length;i++){
        c = key[i];
        if((node->children)[(int)c]){
            node = (node->children)[(int)c];
            if(i == length-1){
                node->isEndOfKey = true;
                node->data = new T(key);
            }
        }
        
        else{
            break;
        }
        
    }
    
    while(i < length){
        c = key[i];
        (node->children)[int(c)] = new TrieNode(c);
        node = (node->children)[int(c)];
        if(i == length-1){
            node->isEndOfKey = true;
            node->data = new T(key);
        }
        i++;
    }
    
   
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    /* IMPLEMENT THIS */
    char c = '\0';
    TrieNode* node = root;
    for(int i = 0; i < (int)username.length();i++){
        if(!node){
            return NULL;
        }
        c = username[i];
        node = (node->children)[(int)c];
        if(!node){
            return NULL;
        }
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
    for(int i = 0; i < (int)username.length();i++){
        if(!node){
            return;
        }
        c = username[i];
        node = (node->children)[(int)c];
        if(!node){
            return;
        }
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
    for(int i = 0; i < (int)prefix.length();i++){
        if(!node){
            return;
        }
        c = prefix[i];
        node = (node->children)[(int)c];
    }
    if(!node){
        return;
    }
    vector<TrieNode*> myQ;
    TrieNode* visiting; 
    myQ.push_back(node);
    int j = 0;
    while(!myQ.empty()){
        visiting = myQ[0];
        myQ.erase(myQ.begin());
        if(visiting->isEndOfKey){
            results.push_back(visiting->data);
        }
        for(j = 127; j > -1; j--){
            if((visiting->children)[j]){
                myQ.insert(myQ.begin(),(visiting->children)[j]);
            }
        }
    }
}


template <class T>
void Trie<T>::findStartingWithNodes(string prefix, vector<TrieNode*> &possible, TrieNode* start) {
    /* IMPLEMENT THIS */
    char c = '\0';
    TrieNode* node = start;
    if(!node){
        return;
    }
    for(int i = 0; i < (int)prefix.length();i++){
        c = prefix[i];
        node = (node->children)[(int)c];
        if(!node){
            return;
        }
    }
    
    possible.push_back(node);
}

template <class T>
void Trie<T>::StartsWithStar(std::string key, vector<TrieNode*> &possible, TrieNode* nod) {
    /* IMPLEMENT THIS */
    vector<TrieNode*> myQ;
    vector<TrieNode*> possWait;
    TrieNode* visiting, *temp;
    char c = '\0';
    bool poss = true;
    
    int j = 0;
    
    myQ.push_back(nod);

    bool added = false;
    int b = 0;

    while(!myQ.empty()){
        added = false;
        visiting = myQ[0];
        myQ.erase(myQ.begin());
        for(b = 0; b < (int)possWait.size(); b++){
            if(possWait[b] == visiting){
                possible.push_back(possWait[b]);
                possWait.erase(possWait.begin() + b);
                added = true;
                break;
            }
        }
        if(!added && !key.empty() && visiting->keyChar == key[0]){
            temp = visiting;
            for(int z = 1; z < (int)key.length();z++){
                c = key[z];
                temp = (temp->children)[(int)c];
                if(!temp){
                    poss = false;
                    break;
                }
            }
            if(poss){
                if(key.size()==1){
                    possible.push_back(temp);
                }
                else{
                possWait.push_back(temp);
                }}
        }
        else if(!added && key.empty()){
            possible.push_back(visiting);
        }
        poss = true;
        for(j = 127; j > -1; j--){
            if((visiting->children)[j]){
             
                myQ.insert(myQ.begin(),(visiting->children)[j]);
            }
        }
    }
}
template <class T>
void Trie<T>::StartsWithQuestion(std::string key, vector<TrieNode*> &possible, TrieNode* nod, int number) {
    /* IMPLEMENT THIS */
    if(!nod){ return ;}
    vector<TrieNode*> myQ;
    TrieNode* visiting, *temp;
    int l = 0;
    char c = '\0';
    bool poss = true;
    int j = 0, i = 0;
    visiting = nod;
    
    for(j = 127; j > -1; j--){
            if((visiting->children)[j]){
                myQ.insert(myQ.begin(),(visiting->children)[j]);
                
            }
        }
    /*If there are multiple question marks, do the search accordingly:*/
    vector <TrieNode*> Temp;
    if(number>1){
        
        for(i = 0; i < number-1 ; i++){
            while(!myQ.empty()){
                l = myQ.size()-1;
                visiting = myQ[l];
                myQ.erase(myQ.begin()+l);
                for(j = 127; j > -1; j--){
                    if((visiting->children)[j]){
                        Temp.insert(Temp.begin(),(visiting->children)[j]);
                    }
                }
            }
            while(!Temp.empty()){
                myQ.push_back(Temp[0]);
                Temp.erase(Temp.begin());
            }
        }
    }

    if(key.empty()){
        while(!myQ.empty()){
            visiting = myQ[0];
            myQ.erase(myQ.begin());
            possible.push_back(visiting);
        }
        return;
    }
    
    while(!myQ.empty()){
                l = myQ.size()-1;
                visiting = myQ[l];
                myQ.erase(myQ.begin()+l);
                for(j = 127; j > -1; j--){
                    if((visiting->children)[j]){
                        Temp.insert(Temp.begin(),(visiting->children)[j]);
                    }
                }
            }
            while(!Temp.empty()){
                myQ.push_back(Temp[0]);
                Temp.erase(Temp.begin());
            }
    while(!myQ.empty()){
        visiting = myQ[0];
        myQ.erase(myQ.begin());
        if(!key.empty() && visiting->keyChar == key[0]){
            temp = visiting;
            for(int z = 1; z < (int)key.length();z++){
                
                c = key[z];
                temp = (temp->children)[(int)c];
                if(!temp){
                    poss = false;
                    break;
                }
            }
            if(poss){
                
                possible.push_back(temp);}
        }
        poss = true;
        
    }
}
template <class T>
void Trie<T>::StartsWithQuestionStar(std::string key, vector<TrieNode*> &possible, TrieNode* nod, int number) {
    /* IMPLEMENT THIS */
    if(!nod){ return ;}
    vector<TrieNode*> myQ1;
    vector<TrieNode*> myQ2;
    TrieNode* visiting, *temp;
    int l = 0;
    char c = '\0';
    bool poss = true;
    int j = 0, i = 0;
    for(j = 127; j > -1; j--){
            if((nod->children)[j]){
                myQ1.insert(myQ1.begin(),(nod->children)[j]);
            }
        }
    /*If there are multiple question marks, do the search accordingly:*/
    if(number>1){
        vector <TrieNode*> Temp;
        for(i = 0; i < number-1 ; i++){
            while(!myQ1.empty()){
                l = myQ1.size()-1;
                visiting = myQ1[l];
                myQ1.erase(myQ1.begin()+l);
                for(j = 127; j > -1; j--){
                    if((visiting->children)[j]){
                        Temp.insert(Temp.begin(),(visiting->children)[j]);
                    }
                }
            }
            while(!Temp.empty()){
                myQ1.push_back(Temp[0]);
                Temp.erase(Temp.begin());
            }
        }
    }
    bool added = false;
    int b = 0;
    vector<TrieNode*> possWait;
    while(!myQ1.empty()){
        /*One by one, try to search ahead of the nodes that you obtained above*/
        /*First push the children of the nodes that you obtained above, since the nodes themselves
         have to be in the sequence of characters, as they are there because of the question marks */
        if(!key.empty()){
            for(j = 127; j > -1; j--){
                    if(((myQ1[0])->children)[j]){
                        myQ2.insert(myQ2.begin(),((myQ1[0])->children)[j]);
                    }
                }
            
            myQ1.erase(myQ1.begin());}
        else{
            myQ2.insert(myQ2.begin(),myQ1[0]);
            myQ1.erase(myQ1.begin());
        }
        
        
        while(!myQ2.empty()){
            added = false;
            visiting = myQ2[0];
            myQ2.erase(myQ2.begin());
            for(b = 0; b < (int)possWait.size(); b++){
                if(possWait[b] == visiting){
                    possible.push_back(possWait[b]);
                    possWait.erase(possWait.begin() + b);
                    added = true;
                    break;
                }
             }
            if(!added && !key.empty() && visiting->keyChar == key[0]){
                temp = visiting;
                for(int z = 1; z < (int)key.length();z++){
                    c = key[z];
                    temp = (temp->children)[(int)c];
                    if(!temp){
                        poss = false;
                        break;
                    }
                }
                if(poss){
                    if(key.size()==1){
                    possible.push_back(temp);
                    }
                    else{
                    possWait.push_back(temp);
                    }
                }
            }
            else if(!added && key.empty()){
                possible.push_back(visiting);
            }
            poss = true;
            for(j = 127; j > -1; j--){
                 if((visiting->children)[j]){
                     myQ2.insert(myQ2.begin(),(visiting->children)[j]);
                }
            }
        }
    }
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
    /* IMPLEMENT THIS */
    int length = wildcardKey.length();
    std::string actualKey = "";
    int i = 0, num = 0;
    bool contStar = false, contQue = false;
    vector<TrieNode*> possible;
    vector<TrieNode*> possibleTemp;
    TrieNode* visiting = NULL;
    
    /*Firstly, try and shorten the given string by eliminating extra *'s:*/
    for(i = 0; i < length; i++){
        if(wildcardKey[i] == '*' && !actualKey.empty() && actualKey[(int)actualKey.length()-1] == '*'){
          continue;  
        }
        else if(wildcardKey[i] == '*' && (int)actualKey.length()>=2 && actualKey[(int)actualKey.length()-1] == '?' &&  actualKey[(int)actualKey.length()-2] == '*'){
          
          continue;  
        }
        else{
            actualKey = actualKey + wildcardKey[i]; 
        }
    }
    bool firstTime = true;
    length = actualKey.length();
    i = 0;
    string key = "";
    /*In the below loop, we will slice the input string into parts, and analyze them one by one:*/
    while(i < length){
        num = 0;
        contQue = false;
        contStar = false;
        /*If the next part of the string contains * or ?:*/
        while(actualKey[i] == '*' || actualKey[i] == '?'){
            if(actualKey[i] == '?'){
                num++;
                contQue = true;
            }
            
            if(actualKey[i] == '*'){
                contStar = true;
            }
            i++;
            /*If you are at the end of the given string:*/
            if(i >= length){
                if(contQue && contStar){

                    /*if there aare no nodes in the possible vector yet, start with the root node:*/
                    if(possible.empty()){
                        if(!firstTime){
                    return;
                }
                        StartsWithQuestionStar(key, possible, root , num);
                        firstTime = false;
                    }
                    else{
                        while(!possible.empty()){
                            visiting = possible[0];
                            possible.erase(possible.begin());
                            StartsWithQuestionStar(key, possibleTemp, visiting, num);
                        }
                        while(!possibleTemp.empty()){
                            possible.push_back(possibleTemp[0]);
                            possibleTemp.erase(possibleTemp.begin());
                        }
                    }
                }
                else if(contQue){
                    if(possible.empty()){
                        if(!firstTime){
                    return;
                }
                        StartsWithQuestion(key, possible, root , num);
                        firstTime = false;
                    }
                    else{
                        while(!possible.empty()){
                            visiting = possible[0];
                            possible.erase(possible.begin());
                            StartsWithQuestion(key, possibleTemp, visiting, num);
                        }
                        while(!possibleTemp.empty()){
                            possible.push_back(possibleTemp[0]);
                            possibleTemp.erase(possibleTemp.begin());
                        }
                    }
                    
                }
                else if(contStar){
                    if(possible.empty()){
                        if(!firstTime){
                    return;
                }
                        StartsWithStar(key, possible, root);
                        firstTime = false;
                    }
                    else{
                        while(!possible.empty()){
                            visiting = possible[0];
                            possible.erase(possible.begin());
                            StartsWithStar(key, possibleTemp, visiting);
                        }
                        while(!possibleTemp.empty()){
                            possible.push_back(possibleTemp[0]);
                            possibleTemp.erase(possibleTemp.begin());
                        }
                    }
                }
                break;
            }
            
        }
        if(i>=length){
            break;
        }
        /*If the given string contains a * and ? just before the text:*/
        if(contQue && contStar){
            
            while(i < length && actualKey[i] != '*' && actualKey[i] != '?'){
                key = key + actualKey[i];
                i++;
            }
            if(possible.empty()){
                if(!firstTime){
                    return;
                }
                StartsWithQuestionStar(key, possible, root , num);
                firstTime = false;
            }
            else{
                while(!possible.empty()){
                    visiting = possible[0];
                    possible.erase(possible.begin());
                    StartsWithQuestionStar(key, possibleTemp, visiting, num);
                }
                while(!possibleTemp.empty()){
                    possible.push_back(possibleTemp[0]);
                    possibleTemp.erase(possibleTemp.begin());
                }
            }
            key = "";
        }
        /*If the given string contains a ? just before the text:*/
        else if(contQue){
            while(i < length && actualKey[i] != '*' && actualKey[i] != '?'){
                key = key + actualKey[i];
                i++;
            }
            
            if(possible.empty()){
                if(!firstTime){
                    return;
                }
                StartsWithQuestion(key, possible, root , num);
                firstTime = false;
            }
            else{
                while(!possible.empty()){
                    visiting = possible[0];
                    possible.erase(possible.begin());
                    StartsWithQuestion(key, possibleTemp, visiting, num);
                }
                while(!possibleTemp.empty()){
                    possible.push_back(possibleTemp[0]);
                    possibleTemp.erase(possibleTemp.begin());
                }
            }
            key = "";
            
            
        }
        /*If the given string contains a * just before the text:*/
        else if(contStar){
            while(i < length && actualKey[i] != '*' && actualKey[i] != '?'){
                key = key + actualKey[i];
                i++;
            }
           
            if(possible.empty()){
                if(!firstTime){
                    return;
                }
                StartsWithStar(key, possible, root);
                firstTime = false;
            }
            else{
                while(!possible.empty()){
                    visiting = possible[0];
                    possible.erase(possible.begin());
                    StartsWithStar(key, possibleTemp, visiting);
                    
                }
                while(!possibleTemp.empty()){
                    possible.push_back(possibleTemp[0]);
                    possibleTemp.erase(possibleTemp.begin());
             
                }
            }
            key = "";
        }
        /*If the given string doesn't contain anything before the text:*/
        else{
        
            while(i < length && actualKey[i] != '*' && actualKey[i] != '?'){
                key = key + actualKey[i];
                i++;
            }
            
            if(possible.empty()){
                if(!firstTime){
                    return;
                }
                findStartingWithNodes(key, possible, root);
                firstTime = false;
            }
            else{
                while(!possible.empty()){
                    visiting = possible[0];
                    possible.erase(possible.begin());
                    findStartingWithNodes(key, possibleTemp, visiting);
                }
                while(!possibleTemp.empty()){
                    possible.push_back(possibleTemp[0]);
                    possibleTemp.erase(possibleTemp.begin());
                }
            }
            key = "";
            
        }
    }
    /*Push all of the possible nodes' data that you obtained from the previous loop: */
    while(!possible.empty()){
        visiting = possible[0];
        possible.erase(possible.begin());
        if(visiting->isEndOfKey){
            if(!inTheResults(results,visiting->data))
            results.push_back(visiting->data);
        }
    }
   
}
template<class T>
bool Trie<T>::inTheResults(vector<T*> &results, T* &obj) {
    int count = results.size();
    for(int i = 0; i < count ; i++){
        if(obj == results[i]){
            return true;
        }
    }
    return false;
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

template <class T>
void Trie<T>::deleteTrieNode(TrieNode* node){
    if(node!=NULL){
        for(int i = 0; i < 128; i++){
            deleteTrieNode((node->children)[i]);
        }
        delete (node->data);
        delete node;
    }
}
