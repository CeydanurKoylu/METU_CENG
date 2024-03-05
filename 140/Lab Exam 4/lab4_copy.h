#ifndef LAB4_H
#define LAB4_H

typedef struct StationNode StationNode;
typedef struct Response Response;
typedef struct CircularLL CircularLL;
typedef struct CircularLLNode CircularLLNode;
typedef struct ListNode ListNode;
typedef struct LinkedList LinkedList;
typedef struct CircularLLs CircularLLs;

struct StationNode
{
    int id;
    float coordX;
    float coordY;
    StationNode* next;
};

struct Response
{
    char username[256];

    union Data
    {
        struct Error   {char code;} error;
        struct Success { float totalDistance; int stationCount; } success;
    } data;
};


struct ListNode
{
    char letter;
    ListNode* next;
};

struct LinkedList
{
    ListNode* head;
};

struct CircularLLNode
{
    char letter;
    CircularLLNode* next;
};


struct CircularLLs
{
    CircularLLNode* head1;
    CircularLLNode* head2;
};

/*
   This function takes values from stdin 
   and calculates vehicle's position after
   a certain time, in seconds 
*/
void CalculatePos();


/*
    This function transposes a matrix that is
    given as an nxn matrix
*/
void TransposeSquareMatrix(int* mat, int n);


/*
    This function traverses shipment nodes
    according to the rules in the description
*/
void ProcessShipment(char* Username,
                     float DistanceLimit,
                     StationNode* HeadNode,
                     Response* Resp);


/*
    This function reverses the given LinkedList
*/
void ReverseLinkedList(LinkedList* list);

/*
    This function splits the given Circular Linked List to
    two halves according to the description
*/
CircularLLs* SplitCircularLLs(CircularLLNode* head);

#endif