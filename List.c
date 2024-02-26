#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj {
    void* data;
    struct NodeObj *prev;
    struct NodeObj *next;
} NodeObj;

typedef NodeObj *Node;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorIndex;
} ListObj;

typedef ListObj *List;

// Prototypes
List newList(void);      
void freeList(List* pL);    

int length(List L);
int index(List L);
void* front(List L);
void* back(List L);       
void* get(List L);              

void clear(List L); 
void set(List L, void* x);
void moveFront(List L);     
void moveBack(List L);  
void movePrev(List L);  
void moveNext(List L);      
void prepend(List L, void* x); 
void append(List L, void* x);     
void insertBefore(List L, void* x);   
void insertAfter(List L, void* x);    
void deleteFront(List L);  
void deleteBack(List L);    
void delete(List L);
  
List copyList(List L);      
List concatList(List A, List B);    


// Helper function
Node newNode(void* data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return N;
}

void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// Constructors-Destructors
List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
    return L;
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while (length(*pL) > 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions
int length(List L) {
    if (L == NULL) {
        printf("Error 404: calling length() on NULL List reference\n");
        exit(1);
    }
    return L->length;
}

int index(List L) {
    if (L == NULL) {
        printf("Error 404: calling index() on NULL List reference\n");
        exit(1);
    }
    return L->cursorIndex;
}

void* front(List L) {
    if (L == NULL || length(L) <= 0) {
        printf("Error 404: calling front() on NULL or empty List\n");
        exit(1);
    }
    return L->front->data;
}

void* back(List L) {
    if (L == NULL || length(L) <= 0) {
        printf("Error 404: calling back() on NULL or empty List\n");
        exit(1);
    }
    return L->back->data;
}

void* get(List L) {
    if (L == NULL || L->cursor == NULL) {
        printf("Error 404: calling get() on NULL List or undefined cursor\n");
        exit(1);
    }
    return L->cursor->data;
}

// Manipulation procedures
void clear(List L) {
    while (L->front != NULL) {
        Node temp = L->front;
        L->front = L->front->next;
        freeNode(&temp);
    }
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
}

void set(List L, void* x) {
    if (L == NULL || L->cursor == NULL) {
        printf("Error 404: calling set() on NULL List or undefined cursor\n");
        exit(1);
    }
    L->cursor->data = x;
}

void moveFront(List L) {
    if (L == NULL || length(L) <= 0) {
        return;
    }
    L->cursor = L->front;
    L->cursorIndex = 0;
}

void moveBack(List L) {
    if (L == NULL || length(L) <= 0) {
        return;
    }
    L->cursor = L->back;
    L->cursorIndex = L->length - 1;
}

void movePrev(List L) {
    if(L->cursor != NULL){
      if(L->cursor != L->front){
         L->cursorIndex -= 1;
         L->cursor = L->cursor->prev;
      }else{
         L->cursor = NULL;
         L->cursorIndex = -1;
      }
   }
}

void moveNext(List L) {
    if(L->cursor != NULL){
      if(L->cursor != L->back){
         L->cursorIndex += 1;
         L->cursor = L->cursor->next;
      }else{
         L->cursor = NULL;
         L->cursorIndex = -1;
      }
   }
}

void prepend(List L, void* x) {
    Node new_node = newNode(x);
    if (L->front == NULL) {
        L->front = L->back = new_node;
    } else {
        new_node->next = L->front;
        L->front->prev = new_node;
        L->front = new_node;
    }
    if (L->cursorIndex != -1) {
        L->cursorIndex++;
    }
    L->length++;
}

void append(List L, void* x) {
    Node new_node = newNode(x);
    if (L->back == NULL) {
        L->front = L->back = new_node;
    } else {
        new_node->prev = L->back;
        L->back->next = new_node;
        L->back = new_node;
    }
    L->length++;
}

void insertBefore(List L, void* x) {
    if (L == NULL || L->cursor == NULL) {
        printf("Error 404: calling insertBefore() on NULL List or undefined cursor\n");
        exit(1);
    }
    if (L->cursor == L->front) {
        prepend(L, x);
    } else {
        Node new_node = newNode(x);
        new_node->prev = L->cursor->prev;
        new_node->next = L->cursor;
        L->cursor->prev->next = new_node;
        L->cursor->prev = new_node;
        L->length++;
        L->cursorIndex++;
    }
}

void insertAfter(List L, void* x) {
    if (L == NULL || L->cursor == NULL) {
        printf("Error 404: calling insertAfter() on NULL List or undefined cursor\n");
        exit(1);
    }
    if (L->cursor == L->back) {
        append(L, x);
    } else {
        Node new_node = newNode(x);
        new_node->next = L->cursor->next;
        new_node->prev = L->cursor;
        L->cursor->next->prev = new_node;
        L->cursor->next = new_node;
        L->length++;
    }
}

void deleteFront(List L) {
    if (L == NULL || length(L) <= 0) {
        printf("Error 404: calling deleteFront() on NULL or empty List\n");
        exit(1);
    }
    Node temp = L->front;
    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->cursorIndex = -1;
    }  else if (L->cursor != NULL) {
        L->cursorIndex--;
    }

    if (length(L) > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    } else {
        L->front = L->back = NULL;
    }
    L->length--;
    freeNode(&temp);
}

void deleteBack(List L) {
    if (L == NULL || length(L) <= 0) {
        printf("Error 404: calling deleteBack() on NULL or empty List\n");
        exit(1);
    }
    Node temp = L->back;
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    if (length(L) > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    } else {
        L->front = L->back = NULL;
    }
    L->length--;
    freeNode(&temp);
}

void delete(List L) {
    if (L == NULL || L->cursor == NULL) {
        printf("Error 404: calling delete() on NULL List or undefined cursor\n");
        exit(1);
    }
    if (L->cursor == L->front) {
        deleteFront(L);
    } else if (L->cursor == L->back) {
        deleteBack(L);
    } else {
        Node temp = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        L->cursor = NULL;
        L->cursorIndex = -1;
        L->length--;
        freeNode(&temp);
    }
}

// Other operations
List copyList(List L) {
    List new_list = newList();
    Node temp = L->front;
    while (temp != NULL) {
        append(new_list, temp->data);
        temp = temp->next;
    }
    return new_list;
}

List concatList(List A, List B) {
    if (A == NULL || B == NULL) {
        printf("Error 404: calling concatList() on NULL List reference\n");
        exit(1);
    }

    List new_list = newList();
    Node temp = A->front;
    while (temp != NULL) {
        append(new_list, temp->data);
        temp = temp->next;
    }
    temp = B->front;
    while (temp != NULL) {
        append(new_list, temp->data);
        temp = temp->next;
    }
    return new_list;
}
