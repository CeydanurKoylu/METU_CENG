#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

//=======================//
// Implemented Functions //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::PRIMES[3] = {102523, 100907, 104659};

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintLine(int tableIndex) const
{
    const HashData& data = table[tableIndex];

    // Using printf here it is easier to format
    if(data.sentinel == SENTINEL_MARK)
    {
        printf("[%03d]         : SENTINEL\n", tableIndex);
    }
    else if(data.sentinel == EMPTY_MARK)
    {
        printf("[%03d]         : EMPTY\n", tableIndex);
    }
    else
    {
        printf("[%03d] - [%03d] : ", tableIndex, data.lruCounter);
        printf("(%-5s) ", data.isCostWeighted ? "True" : "False");
        size_t sz = data.intArray.size();
        for(size_t i = 0; i < sz; i++)
        {
            if(i % 2 == 0)
                printf("[%03d]", data.intArray[i]);
            else
                printf("/%03d/", data.intArray[i]);

            if(i != sz - 1)
                printf("-->");
        }
        printf("\n");
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintTable() const
{
    printf("____________________\n");
    printf("Elements %d\n", elementCount);
    printf("[IDX] - [LRU] | DATA\n");
    printf("____________________\n");
    for(int i = 0; i < MAX_SIZE; i++)
    {
        PrintLine(i);
    }
}

//=======================//
//          TODO         //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Hash(int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    int h = PRIMES[0]*startInt + PRIMES[1]*endInt + PRIMES[2]*((int)isCostWeighted);
    h = h%MAX_SIZE;
    if(h<0) h = h + MAX_SIZE;
    return h;
}

template<int MAX_SIZE>
HashTable<MAX_SIZE>::HashTable()
{
    /* TODO */
    for(int i = 0; i < MAX_SIZE; i++){
        (table[i]).lruCounter = 0;
        (table[i]).intArray.push_back(0);
        (table[i]).sentinel = EMPTY_MARK; 
    }
    elementCount = 0;
}

template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Insert(const std::vector<int>& intArray, bool isCostWeighted)
{
    /* TODO */
    if(intArray.empty()){
        throw  InvalidTableArgException();
    }
    /*
    HashData data;
    bool found = false;
    for(int i =  0; i < MAX_SIZE ; i++){
        data = table[i];
        if(data.startInt == startInt && data.endInt == endInt && data.isCostWeighted == isCostWeighted){
            if(incLRU){
                found = true;
                data.lruCounter = data.lruCounter + 1;
                break;
            }
        }
    }
    if(found) return data.lruCounter - 1;
  */
    int startIn = intArray[0];
    int endIn = intArray[(int)intArray.size()-1];
    int key = Hash(startIn, endIn, isCostWeighted);
    int ind = key;
    int itera = 1;
    while((table[ind]).sentinel  != EMPTY_MARK){
        if((table[ind]).sentinel == OCCUPIED_MARK && (table[ind]).startInt == startIn && table[ind].endInt == endIn && table[ind].isCostWeighted == isCostWeighted){
            table[ind].lruCounter = table[ind].lruCounter + 1;
            return table[ind].lruCounter - 1;
        }
        ind = (ind + 2*itera-1)%MAX_SIZE;
        if(ind<0) ind = ind+MAX_SIZE;
        itera++;
    }
    if((float)elementCount/MAX_SIZE >= (float)1/CAPACITY_THRESHOLD){
        throw TableCapFullException(elementCount);
        
    }    
    itera = 1;
    ind = key;
     while((table[ind]).sentinel == OCCUPIED_MARK){
        ind = (ind + 2*itera-1)%MAX_SIZE;
        if(ind<0) ind = ind+MAX_SIZE;
        itera++;
    }
    table[ind].intArray.clear();
    table[ind].intArray.resize(intArray.size(),0);
    for(int j = 0; j < (int)intArray.size(); j++){
        (table[ind]).intArray[j] = intArray[j];
    }
    table[ind].startInt = startIn;
    table[ind].endInt = endIn;
    table[ind].isCostWeighted = isCostWeighted;
    table[ind].sentinel = OCCUPIED_MARK;
    table[ind].lruCounter = 1;
    elementCount++;
    return 0;
}

template<int MAX_SIZE>
bool HashTable<MAX_SIZE>::Find(std::vector<int>& intArray,
                               int startInt, int endInt, bool isCostWeighted,
                               bool incLRU)
{
    /* TODO */
    int key = Hash(startInt, endInt, isCostWeighted);
    int ind = key;
    int itera = 1;
    while((table[ind]).sentinel != EMPTY_MARK){
        if((table[ind]).sentinel == OCCUPIED_MARK && (table[ind]).startInt == startInt && table[ind].endInt == endInt && table[ind].isCostWeighted == isCostWeighted){
            if(incLRU == true) {table[ind].lruCounter = table[ind].lruCounter + 1;}
            intArray.clear();
            intArray.resize(table[ind].intArray.size(),0);
            for(int j = 0; j < (int)table[ind].intArray.size(); j++){
                intArray[j] = (table[ind]).intArray[j];
            }
            return true;
        }
        ind = (ind + 2*itera-1)%MAX_SIZE;
        if(ind<0) ind = ind+MAX_SIZE;
        itera++;
    }
    return false;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::InvalidateTable()
{
    /* TODO */
    for(int i = 0; i < MAX_SIZE ; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
           table[i].intArray.clear();
           table[i].startInt = 0;
           table[i].endInt = 0;
           table[i].lruCounter = 0;
           table[i].isCostWeighted = 0;
           table[i].sentinel = EMPTY_MARK;
           elementCount--;
        }
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::GetMostInserted(std::vector<int>& intArray) const
{
    /* TODO */
    int maxLRU = 0;
    int maxIND = 0;
     for(int i = 0; i < MAX_SIZE ; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
           if(table[i].lruCounter > maxLRU){
               maxIND = i;
               maxLRU = table[i].lruCounter;
           }
        }
    }
    intArray.clear();
    intArray.resize(table[maxIND].intArray.size(),0);
    for(int j = 0; j < (int)table[maxIND].intArray.size(); j++){
        intArray[j] = (table[maxIND]).intArray[j];
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::Remove(std::vector<int>& intArray,
                                 int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
     int key = Hash(startInt, endInt, isCostWeighted);
    int ind = key;
    int itera = 1;
    while((table[ind]).sentinel != EMPTY_MARK){
        if((table[ind]).sentinel == OCCUPIED_MARK && (table[ind]).startInt == startInt && table[ind].endInt == endInt && table[ind].isCostWeighted == isCostWeighted){
            intArray.clear();
            intArray.resize(table[ind].intArray.size(),0);
            for(int j = 0; j < (int)table[ind].intArray.size(); j++){
                intArray[j] = (table[ind]).intArray[j];
            }
            table[ind].intArray.clear();
            table[ind].startInt = 0;
            table[ind].endInt = 0;
            table[ind].lruCounter = 0;
            table[ind].isCostWeighted = 0;
            table[ind].sentinel = SENTINEL_MARK;
            elementCount--;
            return;
        }
        ind = (ind + 2*itera-1)%MAX_SIZE;
        if(ind<0) ind = ind+MAX_SIZE;
        itera++;
    }
   
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::RemoveLRU(int lruElementCount)
{
    /* TODO */
    int minLRU = 9999999;
    int times = 0;
    for(int i = 0; i < MAX_SIZE ; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
           if(table[i].lruCounter < minLRU){
               minLRU = table[i].lruCounter;
           }
        }
    }
    for(int i = 0; i < MAX_SIZE ; i++){
        if(times == lruElementCount) return;
        if(table[i].sentinel == OCCUPIED_MARK && table[i].lruCounter == minLRU ){
           table[i].intArray.clear();
           table[i].startInt = 0;
           table[i].endInt = 0;
           table[i].lruCounter = 0;
           table[i].isCostWeighted = 0;
           table[i].sentinel = SENTINEL_MARK;
           elementCount--;
           times++;
        }
    }
    
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintSortedLRUEntries() const
{
    /* TODO */
    MaxPairHeap<int, int> maxHeap;
    Pair<int,int> p1;
    for(int i = 0; i < MAX_SIZE ; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
        p1.key = table[i].lruCounter;
        p1.value = i;
        maxHeap.push(p1);    
        }
    }
    while(!maxHeap.empty()){
        PrintLine((maxHeap.top()).value);
        maxHeap.pop();
    }
}

#endif // HASH_TABLE_HPP