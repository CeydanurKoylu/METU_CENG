#include <iostream>
#include "LinkedList.h"
using namespace std;
int main() {
    // You can test your implementations here
    LinkedList<int> list1;
    Node<int>* node1 = new Node<int>(35);
    list1.removeNodeAtIndex(9);
    if(list1.isEmpty()){
        cout << "The list is empty" << endl;
    }
    else{
        cout << "List is not empty" << endl;
    }
    if(list1.containsNode(node1)){
        cout << "The list contains 35" << endl;
    }
    else{
        cout << "List does not contain 35" << endl;
    }
    
    list1.append(35);
    list1.insertAtIndex(89,0);
    list1.append(42);
    list1.append(17);
    list1.prepend(25);
    list1.insertAtIndex(44,2);
    Node<int>* node2 = list1.getFirstNode();
    list1.insertAfterNode(66,node2);
    list1.print();
    cout << endl;
    list1.moveToIndex(1,3);
    list1.removeNodeAtIndex(9);
    list1.print();
    cout << endl;
    
    Node<int>* node3 = list1.getLastNode();
    node1 = list1.getNodeAtIndex(1);
    if(list1.isEmpty()){
        cout << "The list is empty" << endl;
    }
    else{
        cout << "List is not empty" << endl;
    }
    if(list1.containsNode(node1)){
        cout << node1->data << endl;
        if(list1.containsNode(node2)){
            cout << node2->data << endl;
        }
        if(list1.containsNode(node3)){
            cout << node3->data << endl;
        }
    }
    else{
        cout << "List does not contain node1" << endl;
    }
    list1.removeNodeAtIndex(0);
    list1.print();
    cout << list1.getSize() << " " << list1.getIndex(node3) << endl; 
    
}
