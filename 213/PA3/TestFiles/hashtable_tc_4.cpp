#include "HashTable.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Invalidate Hash Table" << std::endl;
    
    HashTable<5> ht;
    
    bool result;
    std::vector<int> outArray;
    
    std::vector<int> array = {1, 2, 3, 4};
    std::vector<int> array2 = {2, 2, 3, 0};
    
    std::cout << "Inserting {1, 2, 3, 4}, true" << std::endl;
    ht.Insert(array, true);
    std::cout << "Inserting {1, 2, 3, 4}, false" << std::endl;
    ht.Insert(array, false);
    std::cout << "Inserting {2, 2, 3, 0}, false" << std::endl;
    ht.Insert(array2, false);
    
    ht.PrintTable();
    
    std::cout << "-------------------------" << std::endl;
    std::cout << "Invalidating Table" << std::endl;
    ht.InvalidateTable();
    ht.PrintTable();
    
	return 0;
}