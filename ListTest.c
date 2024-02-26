#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main() {
    // Create Lists
    List L = newList();
    List M = newList();
    List N = newList();
    List O = newList();

    int testData[] = {1, 2, 3, 4, 5};
    int i;

    // Test append and length
    for(i = 0; i < 5; i++) {
        append(L, &testData[i]);
    }
    printf("After appending, length = %d\n", length(L));

    // Test prepend
    for(i = 0; i < 5; i++) {
        prepend(M, &testData[i]);
    }
    printf("After prepending, length = %d\n", length(M));

    // Test index, front, back, get
    moveFront(L);
    printf("Front item: %d\n", *(int*)front(L));
    printf("Back item: %d\n", *(int*)back(L));
    printf("Current item: %d\n", *(int*)get(L));

    // Test moveNext and movePrev
    moveNext(L);
    printf("Next item: %d\n", *(int*)get(L));
    movePrev(L);
    printf("Previous item: %d\n", *(int*)get(L));

    // Test set
    set(L, &testData[4]);
    moveFront(L);
    printf("After setting, first item: %d\n", *(int*)get(L));

    // Test insertBefore, insertAfter
    moveFront(L);
    moveNext(L);
    insertBefore(L, &testData[2]);
    moveFront(L);
    for(i = 0; i < 2; i++) {
        moveNext(L);
    }
    printf("Item before insertBefore: %d\n", *(int*)get(L));
    insertAfter(L, &testData[1]);
    moveNext(L);
    printf("Item after insertAfter: %d\n", *(int*)get(L));

    // Test delete, deleteFront, deleteBack
    deleteFront(L);
    printf("After deleteFront, front item: %d\n", *(int*)front(L));
    deleteBack(L);
    printf("After deleteBack, back item: %d\n", *(int*)back(L));
    moveFront(L);
    delete(L);
    printf("After delete, front item: %d\n", *(int*)front(L));

    // Test clear
    clear(L);
    printf("After clear, length = %d\n", length(L));

    // Test copyList and concatList
    for(i = 0; i < 5; i++) {
        append(N, &testData[i]);
    }
    O = copyList(N);
    printf("Copied list length = %d\n", length(O));

    List P = concatList(M, N);
    printf("Concatenated list length = %d\n", length(P));

    // Free lists
    freeList(&L);
    freeList(&M);
    freeList(&N);
    freeList(&O);
    freeList(&P);

    return(0);
}

/*
Expected Output -
After appending, length = 5
After prepending, length = 5
Front item: 1
Back item: 5
Current item: 1
Next item: 2
Previous item: 1
After setting, first item: 5
Item before insertBefore: 2
Item after insertAfter: 2
After deleteFront, front item: 3
After deleteBack, back item: 4
After delete, front item: 2
After clear, length = 0
Copied list length = 5
Concatenated list length = 10
*/
