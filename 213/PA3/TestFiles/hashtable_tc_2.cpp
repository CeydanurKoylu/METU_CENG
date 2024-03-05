#include "HashTable.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Hash Table Insert" << std::endl;
    
    HashTable<9> ht;
    
    
    std::vector<int> array = {1, 2, 3, 4};
    std::vector<int> array2 = {2, 2, 3, 0};
    
    std::cout << "Inserting {1, 2, 3, 4}, true" << std::endl;
    ht.Insert(array, true);
    
    std::cout << "Inserting {1, 2, 3, 4}, false" << std::endl;
    ht.Insert(array, false);
    
    std::cout << "Inserting {2, 2, 3, 0}, false" << std::endl;
    ht.Insert(array2, false);
    
    ht.PrintTable();
    
    try
    {
        
        std::cout << "Inserting {}, false" << std::endl;
        ht.Insert({}, false);
    }
    catch(InvalidTableArgException&e)
    {
        std::cout << e.ToString() << std::endl;
    }
    
    try
    {
        
        std::cout << "Inserting {1,2,3}, false" << std::endl;
        ht.Insert({1,2,3}, false);
        std::cout << "Inserting {1,2,399}, false" << std::endl;
        ht.Insert({1,2,399}, false);
        std::cout << "Inserting {1,2,3299}, false" << std::endl;
        ht.Insert({1,2,3299}, false);
        std::cout << "Inserting {1,2,4299}, false" << std::endl;
        ht.Insert({1,2,4299}, false);
    }
    catch(TableCapFullException&e)
    {
        std::cout << e.ToString() << std::endl;
    }
    
    ht.PrintTable();
    
	return 0;
}