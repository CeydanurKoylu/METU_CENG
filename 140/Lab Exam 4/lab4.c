#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "lab4.h"

/*
    This function calculates the final position of an object on
    a 1D line with reading:
        force   (N)
        mass    (kg)
        gravity (kg/ms^2)
        f_Coeff (no unit)
        time    (s)
    from stdin according to the description and prints the final position
    as it is instructed.
*/
void CalculatePos()
{
    /* Write Your Code Here */
    float force, mass, gravity, f_Coeff, times, result,F_Friction,acc;
    
    scanf("%f %f %f %f %f", &force, &mass, &gravity, &f_Coeff, &times);
    
    F_Friction = mass*gravity*f_Coeff;
    if(force>=0){
        if(F_Friction>force){
            acc = 0.0;
        }
        else{
        acc = (force-F_Friction)/mass;
        }
    }
    else{
        if(F_Friction>fabs(force)){
            acc = 0.0;
        }
        else{
        acc = (force+F_Friction)/mass;
        }
    }
    
    result = (1.0/2.0)*acc*times*times;
    printf("The position is %.2f",result);
}

/*
    Transposes the given nxn matrix
    mat -> nxn matrix given as a 1D array (row-major)
    n   -> size of one dimension
*/
void TransposeSquareMatrix(int* mat, int n)
{
    /* Write Your Code Here */
    int **arr,i,j;
    arr = (int **)malloc(sizeof(int*)*n);
    for(i=0 ; i<n; i++){
        arr[i] = (int*)malloc(sizeof(int)*n);
    }
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            arr[i][j] = mat[i*n+j];
        }
    }
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            mat[i*n+j] = arr[j][i];
        }
    }
    
}


/*
    This function traverses shipment nodes
    according to the rules in the description
*/
void ProcessShipment(char* Username,
                          float DistanceLimit,
                          StationNode* HeadNode,
                          Response* Resp)
{
    /* Write Your Code Here */
    float totalDistance=0.0, prevCoord[2];
    int i=0;
    strcpy(Resp->username,Username);
    prevCoord[0] = HeadNode->coordX;
    prevCoord[1] = HeadNode->coordY;
    while(HeadNode){
        totalDistance += sqrt(((prevCoord[0]-HeadNode->coordX)*(prevCoord[0]-HeadNode->coordX))+((prevCoord[1]-HeadNode->coordY)*(prevCoord[1]-HeadNode->coordY)));
        prevCoord[0] = HeadNode->coordX;
        prevCoord[1] = HeadNode->coordY;
        HeadNode = HeadNode->next;
        i++;
    }
    if(totalDistance > DistanceLimit){
        Resp->data.error.code = 'D';
    }
    else{
        Resp->data.success.totalDistance = totalDistance;
        Resp->data.success.stationCount = i;
    }
}


/*
    This function reverses a linked list without creating
    a new one
*/
void ReverseLinkedList(LinkedList* list)
{
    /* Write Your Code Here */
    ListNode* current = list->head,*prev = NULL,*temp;
    while(current){
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    list->head = prev;
    
}

/*
    This function splits the given circular linked list into
    two halves. If the list is not equally splitted, the first
    list gets less nodes.
*/
CircularLLs* SplitCircularLLs(CircularLLNode* head)
{
    /* Write Your Code Here */
    CircularLLs *circular;
    CircularLLNode* current,*prev,*curr1,*curr2;
    int size = 1, split,i=0;
    
    circular = (CircularLLs*)malloc(sizeof(CircularLLs));
    current = head->next;
    
    while(current!=head){
        current = current -> next;
        size++;
    }
    split = size/2;
    
    circular->head1 = head;
    
    curr1 = head->next;
    i++;
    while(i!=split){
        curr1 = curr1->next;
        i++;
    }
    circular->head2 = curr1;
    
    curr2 = circular->head1;
    
    while(curr2 != circular->head2){
        prev = curr2;
        curr2 = curr2->next;
    }
    prev->next = circular->head1;  
    
    while(curr2!=circular->head1){
        prev = curr2;
        curr2 = curr2->next;
    }
    prev->next = circular->head2;
    
    
    
    return circular;
}