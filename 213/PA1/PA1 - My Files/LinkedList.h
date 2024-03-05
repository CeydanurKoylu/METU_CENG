#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &rhs);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);
    void mergeNodes(int sourceIndex, int destIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    head = new Node<T>(T());
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{   
    /* TODO */
    head = new Node<T>(T());
    Node<T> *current1 = head;
    Node<T> *current2 = (rhs.head)->next;
    size = 0;
    for(int i = 0; i < rhs.size ; i++){
        current1->next = new Node<T>((current2)->data, current1, NULL);
        current1 = current1->next;
        current2 = current2->next;
        size++;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{   
    /* TODO */
    for(Node<T>* temp = head; head != NULL ; head = temp){
        temp = head->next;
        delete head;
    }
    
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    for(Node<T>* temp = head; head != NULL ; head = temp){
        temp = head->next;
        delete head;
    }
    head = new Node<T>(T());
    Node<T> *current1 = head;
    Node<T> *current2 = (rhs.head)->next;
    size = 0;
    for(int i = 0; i < rhs.size ; i++){
        current1->next = new Node<T>((current2)->data, current1, NULL);
        current1 = current1->next;
        current2 = current2->next;
        size++;
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
    Node<T> * temp = head->next; int i = 0;
    while(temp){
        i++;
        temp = temp->next;
    }
    return i;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    Node<T> * temp = head->next;
    if(temp == NULL){
        return true;
    }
    return false;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    Node<T> * current = head->next;
    while(current){
        if(current == node){
            return true;
        }
        current = current->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    return head->next;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    Node<T> * current = head->next;
    if(current){
        while(current->next){
            current = current->next;
        }
    return current;
        
    }
    else{
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    Node<T> * current = head->next;
    while(current){
        if(current->data == data){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    Node<T> * current = head->next; int i = 0;
    if(index < 0 || index >= size){
        return NULL;
    }
    while(current){
        if(i == index){
            return current;
        }
        current = current->next;
        i++;
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{   
    /* TODO */
    
    Node<T> *last = this->getLastNode();
    
    
    if(last != NULL){
      (last)->next = new Node<T>(data,last,NULL);  
    } 
    else{
        head->next = new Node<T>(data,head,NULL); 
    }
    
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    
    Node<T> *first = new Node<T>(data, head, head->next);
    if(head->next){
    head->next->prev = first;}
    head->next = first;
    
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    
    if(this->containsNode(node)){
        
    
        Node<T> *current = node;
        current->next = new Node<T>(data, current, current->next);
        if(current->next->next){
            current->next->next->prev = current->next;}
        size++;
    }
    
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    
    if(index < size && index > -1){
        Node<T> *current = (getNodeAtIndex(index))->prev;
        current->next = new Node<T>(data, current, current->next);
        if(current->next->next){
            current->next->next->prev = current->next;}
        size++;
    }
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    Node<T> *temp = head->next; int i = 0;
    while(temp){
        if(temp == node){
            return i;
        }
        temp = temp->next;
        i++;
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
    if(currentIndex < size && currentIndex > -1){
        Node<T>* current = getNodeAtIndex(currentIndex);
        current->prev->next = current->next;
        if(current->next){
            current->next->prev = current->prev;
        }
        if(newIndex >=  size - 1){
             Node<T> *last = this->getLastNode();
            
            if(last != NULL){
              (last)->next = current;
              current->prev = last;
            } 
            else{
                head->next = current;
                current->prev = head; 
            }
            current->next = NULL;
            
    
        }
        else{
            Node<T>* destination = getNodeAtIndex(newIndex);
            if(destination){
                destination->prev->next = current;
                current->prev = destination->prev;
                destination->prev = current;
                current->next = destination;
            
                }
            else{
                head->next = current;
                current->prev = head;
                current->next = NULL;
                }
            }
    }
}

template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    /* TODO */
    Node<T>* source = getNodeAtIndex(sourceIndex);
    Node<T>* dest = getNodeAtIndex(destIndex);
    if(source && dest){
        dest->data = dest->data + source->data;
        this->removeNode(source);
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{   
    /* TODO */
    if(this->containsNode(node)){
        int i = this->getIndex(node);
        Node<T> *temp = this->getNodeAtIndex(i);
        temp->prev->next = temp->next;
        if(temp->next){
        temp->next->prev = temp->prev;}
        delete temp;
        size--;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{   
    /* TODO */
    Node<T> *del = this->getNode(data);
    
    while((del = (this->getNode(data)))){
        this->removeNode(del);
        
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    Node<T>* temp = this->getNodeAtIndex(index);
    if(temp){
        this->removeNode(temp);
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{   
    /* TODO */
    int y = size;
    for(int i = 0; i < y; i++){
        this->removeNodeAtIndex(0);
    }
    size = 0;
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    while(node)
    {
        std::cout << *node << std::endl;
        node = node->next;
    }

}

#endif //LINKEDLIST_H