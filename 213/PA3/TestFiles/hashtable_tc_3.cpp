#include "HashTable.h"
#include "Exceptions.h"
#include <iostream>

void PrintArray(const std::vector<int>& arr)
{
    std::cout << "{";
    for(int a : arr)
    {
        std::cout << a << " ";
    }
    std::cout << "}" << std::endl;
}

int main()
{
    std::cout << "Testing Hash Table Find" << std::endl;
    
    HashTable<7> ht;
    
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
    
    std::cout << "Finding 2, 3, false incrementing LRU" << std::endl;
    outArray.clear();
    result = ht.Find(outArray, 2, 3, false, true);
    std::cout << "Returned " << result << " Returned Array:" << std::endl; 
    PrintArray(outArray);
    
    ht.PrintTable();
    
    std::cout << "-------------------------" << std::endl;
    std::cout << "Finding 1, 4, true incrementing LRU" << std::endl;
    outArray.clear();
    result = ht.Find(outArray, 1, 4, true, true);
    std::cout << "Returned " << result << " Returned Array:" << std::endl; 
    PrintArray(outArray);
    
    ht.PrintTable();
    
    std::cout << "-------------------------" << std::endl;
    std::cout << "Finding 1, 4, true **not** incrementing LRU" << std::endl;
    outArray.clear();
    result = ht.Find(outArray, 2, 0, true, false);
    std::cout << "Returned " << result << " Returned Array:" << std::endl; 
    PrintArray(outArray);
    
    ht.PrintTable();
	return 0;
}