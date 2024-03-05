#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"


/*
    Create a cache by reading inputs from stdin
*/
Cache* createCache()
{   int cacheSize, n,i,length = 0;
    char *line,*token;
    char *mediaName,*domainName;
    Cache *myCache;
    CacheNode *myNode;
    DomainFreqNode *freqNode;
    DomainFreqList *freqList;
    DomainFreqNode *current;
    current = NULL;
    
    line = (char*)malloc(sizeof(char)*1000);
    
    fgets(line, 1000, stdin);
    token = strtok(line," ");
    cacheSize = atoi(token);
    
    token = strtok(NULL," ");
    n = atoi(token);
    
    
    myCache = (Cache*)malloc(sizeof(Cache));
    
    myCache->cacheLimit = cacheSize;
    myCache->mediaCount = n;
    myCache->head = NULL;
    myCache->tail = NULL;
    myCache->currentSize = 0;
    
    for(i=0;i<n;i++){
        
        myNode = (CacheNode*)malloc(sizeof(CacheNode));
        
        freqList = (DomainFreqList *)malloc(sizeof(DomainFreqList));
        
        
        
        fgets(line, 1000, stdin);
        
        
        token = strtok(line," ");
        length = strlen(token)+1;
        mediaName = (char *)malloc(sizeof(char)*length);
        strcpy(mediaName,token);
        
        (myNode->media).name = mediaName;
        
        
        token = strtok(NULL," ");
        (myNode->media).size = atoi(token);
        
        
        myNode->prev = NULL;
        myNode->next = NULL;
        
        myNode->domainFreqList = freqList;
        freqList->head = NULL;
        freqList->tail = NULL;
        
        token = strtok(NULL, " ");
        
        
        while(token){
            
            freqNode = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
            length = strlen(token)+1;
            domainName = (char*)malloc(sizeof(char)*length);
            strcpy(domainName,token);
            freqNode->name = domainName;
            
            
            token = strtok(NULL, " ");
            freqNode->freq = atoi(token);
            
            
            freqNode->prev = NULL;
            freqNode->next = NULL;
            
            current = freqList->head;
            
            if(freqList->head == NULL){
                freqList->head = freqNode;
                freqList->tail = freqNode;
            }
            else{
                while(current && current->freq > freqNode->freq){
                    current = current->next;
                }
                
                while(current && current->freq == freqNode->freq){
                    if(strcmp(current->name,freqNode->name)<0){
                        current = current->next;
                    }
                    else{
                        if(current->prev){
                        (current->prev)->next = freqNode;
                        freqNode->prev = current->prev;
                        current->prev = freqNode;
                        freqNode->next = current;
                        
                        }
                        else{
                            freqList->head=freqNode;
                            freqNode->next = current;
                            current->prev = freqNode;
                        }
                        break;
                        
                    }
                }
                
                if(current && current->freq < freqNode-> freq){
                    if(current->prev){
                        (current->prev)->next = freqNode;
                        freqNode->prev = current->prev;
                        current->prev = freqNode;
                        freqNode->next = current;
                        }
                    else{
                        freqList->head=freqNode;
                        freqNode->next = current;
                        current->prev = freqNode;
                    }
                }
                
                if(!current){
                    (freqList->tail)->next = freqNode;
                    freqNode->prev = freqList->tail;
                    freqList->tail = freqNode;
                }
            }
                
            token = strtok(NULL, " ");
            
        }
        
        
        
        
        if(myCache->head == NULL){
            myCache->head = myNode;
            
        }
        
        else if(myCache->tail){
            
            (myCache->tail)->next = myNode;
            myNode->prev = myCache->tail;
            myCache->tail = myNode;
        }
        else{
            (myCache->head)->next = myNode;
            myNode->prev = myCache->head;
            myCache->tail = myNode;
        }
        
        myCache->currentSize += (myNode->media).size;
    
    }
    
    
    
    return myCache;
}

/*
    Prints cache information and its contents
*/
void printCache(Cache* cache)
{   CacheNode *current;
    DomainFreqNode *currfreq;
    int i;
    current = cache -> head;
    if(cache->mediaCount){
        
        printf("-------------- Cache Information --------------\n");
        printf("Cache Limit: %d KB\n", cache->cacheLimit);
        printf("Current Size: %d KB\n", cache->currentSize);
        printf("Media Count: %d\n", cache->mediaCount);
        printf("Cache Media Info:\n");
        for(i=0;i<cache->mediaCount;i++){
            currfreq = (current->domainFreqList)->head;
            
            printf("\tName: %s\tSize: %d KB\n",(current->media).name,(current->media).size);
            printf("\t------- Media Domain Frequencies -------\n");
            
            while(currfreq){
                printf("\t\tName: %s\tFreq: %d\n",currfreq->name,currfreq->freq);
                currfreq = currfreq->next;
            }
            printf("\t----------------------------------------\n");
            current = current->next;
        }
        printf("----------------------------------------------\n");
    }
    else{
        printf("The Cache is Empty\n");
    }
}


/*
    Adds media to the cache
*/
CacheNode* addMediaRequest(Cache* cache, Media media, char* domain)
{   
    CacheNode *found,*newNode = NULL;
    DomainFreqNode *currfr = NULL,*current=NULL,*newFreq;
    DomainFreqList *freqList = NULL;
    char *domName=NULL,*mediaName=NULL;
    int maxSize = cache->cacheLimit;
    int control = 0,length = 0;
    
    /*Check if node already exists:*/
    
    if((found = findMedia(cache,media.name))){
        /*If node exists seperate it from the rest and add it to the beginning*/
        if(cache->head == found){
            ;
        }
        else if(cache->tail == found){
            (found->prev)->next = NULL;
            cache->tail = found->prev;
            
            (cache->head)->prev = found;
            found->next = cache->head;
            found->prev=NULL;
            cache->head=found;
        }
        else{
            (found->prev)->next = (found->next);
            (found->next)->prev = (found->prev);
            
            (cache->head)->prev = found;
            found->next = cache->head;
            found->prev=NULL;
            cache->head=found;
        }
        
        currfr = (found->domainFreqList)->head;
        
        /*Check if there is an existing domain node with the same name inside the found cache node:*/
        
        while(currfr){
            if(!strcmp(currfr->name,domain)){
                /* If the domain node exists seperate it from the rest and 
                add it to the corresponding place within frequency list */
                    currfr->freq += 1;
                    if(currfr->next){
                    (currfr->next)->prev = currfr->prev;}
                    else{
                        (found->domainFreqList)->tail = currfr->prev;
                    }
                    if(currfr->prev){
                    (currfr->prev)->next = currfr->next;}
                    else{
                        (found->domainFreqList)->head = currfr->next;
                    }
                    currfr->prev=NULL;
                    currfr->next=NULL;
                    
                    current = (found->domainFreqList)->head;
                /*If the domain list is empty, just add the node there*/
                if((found->domainFreqList)->head == NULL){
                    (found->domainFreqList)->head = currfr;
                    (found->domainFreqList)->tail = currfr;
                }
                else{
                    /*If the domain is mot empty search for the correct place*/
                    while(current && current->freq > currfr->freq){
                        current = current->next;
                    }
                    
                    while(current && current->freq == currfr->freq){
                        if(strcmp(current->name,currfr->name)<0){
                            current = current->next;
                        }
                        else{
                            if(current->prev){
                            (current->prev)->next = currfr;
                            currfr->prev = current->prev;
                            current->prev = currfr;
                            currfr->next = current;
                            }
                            else{
                                (found->domainFreqList)->head=currfr;
                                currfr->next = current;
                                current->prev = currfr;
                            }
                            break;
                            
                        }
                    }
                    
                    if(current && current->freq < currfr-> freq){
                        if(current->prev){
                            (current->prev)->next = currfr;
                            currfr->prev = current->prev;
                            current->prev = currfr;
                            currfr->next = current;
                            }
                        else{
                            (found->domainFreqList)->head=currfr;
                            currfr->next = current;
                            current->prev = currfr;
                        }
                    }
                    /*If you come to the end of the freq list, add the node there*/
                    if(!current){
                        ((found->domainFreqList)->tail)->next = currfr;
                        currfr->prev = (found->domainFreqList)->tail;
                        (found->domainFreqList)->tail = currfr;
                        }
                    }
                    control = 1;
                    break;
                }
                currfr = currfr->next;
            }
        
        /*If there is no existing domain node, create one:*/
        
        if(!control){
            
            newFreq = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
            length = strlen(domain)+1;
            domName = (char*)malloc(sizeof(char)*length);
            strcpy(domName,domain);
            
            newFreq->name = domName;
            newFreq->freq = 1;
            newFreq->prev = NULL;
            newFreq->next = NULL;
            
            current = (found->domainFreqList)->head;
            
            if((found->domainFreqList)->head == NULL){
                (found->domainFreqList)->head = newFreq;
                (found->domainFreqList)->tail = newFreq;
            }
            else{
                while(current && current->freq > newFreq->freq){
                    current = current->next;
                }
                
                while(current && current->freq == newFreq->freq){
                    if(strcmp(current->name,newFreq->name)<0){
                        current = current->next;
                    }
                    else{
                        if(current->prev){
                        (current->prev)->next = newFreq;
                        newFreq->prev = current->prev;
                        current->prev = newFreq;
                        newFreq->next = current;
                        }
                        else{
                            (found->domainFreqList)->head=newFreq;
                            newFreq->next = current;
                            current->prev = newFreq;
                        }
                        break;
                        
                    }
                }
                
                if(current && current->freq < newFreq-> freq){
                    if(current->prev){
                        (current->prev)->next = newFreq;
                        newFreq->prev = current->prev;
                        current->prev = newFreq;
                        newFreq->next = current;
                        }
                    else{
                        (found->domainFreqList)->head=newFreq;
                        newFreq->next = current;
                        current->prev = newFreq;
                    }
                }
                
                if(!current){
                    ((found->domainFreqList)->tail)->next = newFreq;
                    newFreq->prev = (found->domainFreqList)->tail;
                    (found->domainFreqList)->tail = newFreq;
                }
            }
        }
        
        return found;
        
    }
    
    /*Cache node doesn't exist and needs to be created:*/
    
    else{
        
        while(maxSize < cache->currentSize + media.size){
            deleteMedia(cache, ((cache->tail)->media).name);
        }
        
        cache->mediaCount += 1;
        cache->currentSize += media.size;
        
        newNode = (CacheNode*)malloc(sizeof(CacheNode));
        
        length = strlen(media.name)+1;
        mediaName = (char*)malloc(sizeof(char)*length);
        
        freqList = (DomainFreqList*)malloc(sizeof(DomainFreqList));
        
        newFreq = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        
        length = strlen(domain)+1;
        domName = (char*)malloc(sizeof(char)*length);
        
        strcpy(domName,domain);
        
        newFreq->name = domName;
        newFreq->freq = 1;
        newFreq->prev = NULL;
        newFreq->next = NULL;
        
        strcpy(mediaName,media.name);
        (newNode->media).name = mediaName;
        (newNode->media).size = media.size;
        newNode->domainFreqList = freqList;
        
        freqList->head = newFreq;
        freqList->tail = newFreq;
        
        if(cache->head){
            (cache->head)->prev = newNode;
            newNode->next = cache->head;
            cache->head = newNode;
        }
        else{
            cache->head = newNode;
            cache->tail = newNode;
        }
        
        return newNode;
    
}
        
}

/*
    Finds the corresponding media's node in the cache
    Return NULL if it is not found
*/
CacheNode* findMedia(Cache* cache, char* name)
{   
    CacheNode *current = cache->head;
    int i;
    if(current){
        for(i=0;i<cache->mediaCount;i++){
            if(!strcmp((current->media).name,name)){
                return current;
                }
                current = current->next;
            }
    }
    return NULL;
}

/*
    Finds a media from its name and deletes it's node from the cache
    Do not do anything if media is not found
*/
void deleteMedia(Cache* cache, char* name)
{   CacheNode *found;
    if((found = findMedia(cache,name))){
        cache->mediaCount -= 1;
        cache->currentSize -= (found->media).size;
        if(found == cache->tail && cache->head == found){
            cache->head = NULL;
            cache->tail = NULL;
        }
        else if(cache->head == found){
            (found->next)->prev = NULL;
            cache->head = found->next;
        }
        else if(cache->tail == found){
            (found->prev)->next = NULL;
            cache->tail = found->prev;
        }
        else{
        (found->prev)->next = (found->next);
        (found->next)->prev = (found->prev);
        }
        free(found);
    }
    
}

