#include <stdio.h>
#include <stdlib.h>

#include "lab4.h"

void PrintSquareMatrix(int* mat, int n)
{
    int i,j;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("%d ", mat[i*n + j]);
        }

        printf("\n");
    }

    printf("\n");
}

int main()
{

    /* Matrix */
    int mat[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    /* ProcessShipment Variables */
    StationNode* firstNode;
    Response resp;

    /* ReverseList variables */
    LinkedList* list;
    ListNode* it;

    /* SplitCircularLL Variables */
    int i;
    CircularLLs* cllLists;
    CircularLLNode* cllNode;

    /* Process Shipment Test */

    /* First Node */
    firstNode = (StationNode*)malloc(sizeof(StationNode));
    firstNode->coordX = 0.8;
    firstNode->coordY = 0.0;
    firstNode->id = 0;
    
    /* Second Node */
    firstNode->next = (StationNode*)malloc(sizeof(StationNode));
    firstNode->next->coordX = 1.2;
    firstNode->next->coordY = 0.0;
    firstNode->next->id = 1;

    /* Third Node */
    firstNode->next->next = (StationNode*)malloc(sizeof(StationNode));
    firstNode->next->next->coordX = -3.5;
    firstNode->next->next->coordY = 0.0;
    firstNode->next->next->id = 2;

    /* Fourth Node */
    firstNode->next->next->next = (StationNode*)malloc(sizeof(StationNode));
    firstNode->next->next->next->coordX = 1.5;
    firstNode->next->next->next->coordY = 0.0;
    firstNode->next->next->next->id = 3;
    
    firstNode->next->next->next->next = NULL;


    /* ReverseListTest */

    list = (LinkedList*)malloc(sizeof(LinkedList));

    /* First Node */
    list->head = (ListNode*)malloc(sizeof(StationNode));
    list->head->letter = 'A';
    
    /* Second Node */
    list->head->next = (ListNode*)malloc(sizeof(StationNode));
    list->head->next->letter = 'B';

    /* Third Node */
    list->head->next->next = (ListNode*)malloc(sizeof(StationNode));
    list->head->next->next->letter = 'C';

    /* Fourth Node */
    list->head->next->next->next = (ListNode*)malloc(sizeof(StationNode));
    list->head->next->next->next->letter = 'D';
    
    list->head->next->next->next->next = NULL;

    /* Split CircularLL Test */

    /* First Node */
    cllNode = (CircularLLNode*)malloc(sizeof(CircularLLNode));
    cllNode->letter = 'A';

    /* Second Node */
    cllNode->next = (CircularLLNode*)malloc(sizeof(CircularLLNode));
    cllNode->next->letter = 'B';

    /* Third Node */
    cllNode->next->next = (CircularLLNode*)malloc(sizeof(CircularLLNode));
    cllNode->next->next->letter = 'C';

    /* Fourth Node */
    cllNode->next->next->next = (CircularLLNode*)malloc(sizeof(CircularLLNode));
    cllNode->next->next->next->letter = 'D';

    /* Fifth Node */
    cllNode->next->next->next->next = (CircularLLNode*)malloc(sizeof(CircularLLNode));
    cllNode->next->next->next->next->letter = 'E';    
    
    cllNode->next->next->next->next->next = cllNode;

    printf("---------- CalculatePosTest ---------------\n");
    CalculatePos();
    printf("\n");

    printf("----------- MatrixTransposeTest -----------\n");
    PrintSquareMatrix(mat,3);
    TransposeSquareMatrix(mat, 3);
    PrintSquareMatrix(mat,3);

    printf("---------- ProcessShipmentTest ----------\n");
    ProcessShipment("John", 15, firstNode, &resp);
    printf("Username: %s\n", resp.username);
    printf("StationCount: %d\n", resp.data.success.stationCount);
    printf("TotalDistance: %.2f\n", resp.data.success.totalDistance);

    ProcessShipment("Sonya", 10.0, firstNode, &resp);
    printf("Username: %s\n", resp.username);
    printf("ErrorCode: %c\n", resp.data.error.code);

    /* ReverseList Test */
    printf("---------- ReverseListTest ----------\n");
    ReverseLinkedList(list);
    it = list->head;
    while(it)
    {
        printf("%c ", it->letter);
        it = it->next;
    }
    
    printf("\n");

    printf("------------ Split CircularLLTest -----------\n");
    cllLists = SplitCircularLLs(cllNode);
    cllNode = cllLists->head1;

    printf("List1: ");
    for(i=0; i<10; i++)
    {
        printf("%c ", cllNode->letter);
        cllNode = cllNode->next;
    }

    cllNode = cllLists->head2;
    printf("\n");
    printf("List2: ");
    for(i=0; i<10; i++)
    {
        printf("%c ", cllNode->letter);
        cllNode = cllNode->next;
    }

    return 0;
    
}