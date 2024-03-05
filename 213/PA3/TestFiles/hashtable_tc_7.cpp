#include "HashTable.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Hash Table Remove LRU" << std::endl;
    
    HashTable<13> ht;
    
    std::vector<int> array = {1, 2, 3, 4};
    std::vector<int> array2 = {2, 1, 2, 0};
    std::vector<int> array3 = {4, 2, 3, 0};
    std::vector<int> array4 = {1, 2, 3, 2};
    
    std::cout << "Inserting {1, 2, 3, 4}, true" << std::endl;
    ht.Insert(array, true);
    
    std::cout << "Inserting {1, 2, 3, 4}, false" << std::endl;
    ht.Insert(array, false);
    
    std::cout << "Inserting {2, 1, 2, 0}, true" << std::endl;
    ht.Insert(array2, true);
    
    std::cout << "Inserting {4, 2, 3, 0}, false" << std::endl;
    ht.Insert(array3, false);
    std::cout << "Inserting {4, 2, 3, 0}, false" << std::endl;
    ht.Insert(array3, false);

    std::cout << "Inserting {1, 2, 3, 2}, false" << std::endl;
    ht.Insert(array4, false);
    std::cout << "Inserting {1, 2, 3, 2}, false" << std::endl;
    ht.Insert(array4, false);
    std::cout << "Inserting {1, 2, 3, 2}, false" << std::endl;
    ht.Insert(array4, false);
    
    std::cout << "Inserting {4, 2, 3, 0}, false" << std::endl;
    ht.Insert(array3, false);
    std::cout << "Inserting {4, 2, 3, 0}, false" << std::endl;
    ht.Insert(array3, false);
    
    ht.PrintTable();
    
    std::cout << "-------------------------" << std::endl;
    std::cout << "Remove LRU with 2" << std::endl;
    ht.RemoveLRU(2);
    
    
    ht.PrintTable();
    
	return 0;
}