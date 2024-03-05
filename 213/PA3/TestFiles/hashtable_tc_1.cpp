#include "HashTable.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Hash Table Constructor" << std::endl;
    
    HashTable<7> table;
    
    table.PrintTable();
    
	return 0;
}