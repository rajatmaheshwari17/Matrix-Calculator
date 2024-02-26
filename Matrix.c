#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Matrix.h"
#include "List.h"

// Private Entry type
typedef struct EntryObj {
    int column;
    double value;
    struct EntryObj* next;
} EntryObj;

typedef EntryObj* Entry;

// Private MatrixObj type
typedef struct MatrixObj {
    int size;
    int nnz;
    Entry* rows;
} MatrixObj;

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->nnz = 0;
    M->rows = malloc((n + 1) * sizeof(Entry));

    for (int i = 1; i <= n; i++) {
        M->rows[i] = NULL;
    }
    
    return M;
}

void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        Matrix M = *pM;
        for (int i = 1; i <= M->size; i++) {
            Entry current = M->rows[i];
            while (current != NULL) {
                Entry next = current->next;
                free(current);
                current = next;
            }
        }
        free(M->rows);
        free(M);
        *pM = NULL;
    }
}

int size(Matrix M) {
    return M->size;
}

int NNZ(Matrix M) {
    return M->nnz;
}

int equals(Matrix A, Matrix B) {
    if (A->size != B->size || A->nnz != B->nnz) {
        return 0;
    }

    for (int i = 1; i <= A->size; i++) {
        Entry entryA = A->rows[i];
        Entry entryB = B->rows[i];

        while (entryA != NULL && entryB != NULL) {
            if (entryA->column != entryB->column || entryA->value != entryB->value) {
                return 0;
            }

            entryA = entryA->next;
            entryB = entryB->next;
        }

        if (entryA != NULL || entryB != NULL) {
            return 0;
        }
    }

    return 1;
}

void makeZero(Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        Entry current = M->rows[i];
        while (current != NULL) {
            Entry next = current->next;
            free(current);
            current = next;
        }
        M->rows[i] = NULL;
    }
    M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (i < 1 || i > M->size || j < 1 || j > M->size) {
        fprintf(stderr, "Invalid row or column index\n");
        exit(1);
    }

    Entry entry = M->rows[i];
    Entry prev = NULL;

    while (entry != NULL && entry->column < j) {
        prev = entry;
        entry = entry->next;
    }

    if (entry != NULL && entry->column == j) {
        if (x != 0) {
            entry->value = x;
        } else {
            if (prev == NULL) {
                M->rows[i] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            M->nnz--;
        }
    } else {
        if (x != 0) {
            Entry newEntry = malloc(sizeof(EntryObj));
            newEntry->column = j;
            newEntry->value = x;
            newEntry->next = entry;

            if (prev == NULL) {
                M->rows[i] = newEntry;
            } else {
                prev->next = newEntry;
            }
            M->nnz++;
        }
    }
}

Matrix copy(Matrix A) {
    Matrix copyM = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        Entry entry = A->rows[i];

        while (entry != NULL) {
            changeEntry(copyM, i, entry->column, entry->value);
            entry = entry->next;
        }
    }

    return copyM;
}

Matrix transpose(Matrix A) {
    Matrix transposeM = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        Entry entry = A->rows[i];

        while (entry != NULL) {
            changeEntry(transposeM, entry->column, i, entry->value);
            entry = entry->next;
        }
    }

    return transposeM;
}

Matrix scalarMult(double x, Matrix A) {
    Matrix multM = copy(A);

    for (int i = 1; i <= multM->size; i++) {
        Entry entry = multM->rows[i];

        while (entry != NULL) {
            entry->value *= x;
            entry = entry->next;
        }
    }

    return multM;
}

Matrix sum(Matrix A, Matrix B) {
    if (A->size != B->size) {
        fprintf(stderr, "Matrix sizes do not match\n");
        exit(1);
    }

    Matrix sumM = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        Entry entryA = A->rows[i];
        Entry entryB = B->rows[i];

        while (entryA != NULL || entryB != NULL) {
            int colA = entryA ? entryA->column : INT_MAX;
            int colB = entryB ? entryB->column : INT_MAX;

            if (colA == colB) {
                changeEntry(sumM, i, colA, entryA->value + entryB->value);
                entryA = entryA->next;
                entryB = entryB->next;
            } else if (colA < colB) {
                changeEntry(sumM, i, colA, entryA->value);
                entryA = entryA->next;
            } else {
                changeEntry(sumM, i, colB, entryB->value);
                entryB = entryB->next;
            }
        }
    }

    return sumM;
}

Matrix diff(Matrix A, Matrix B) {
    if (A->size != B->size) {
        fprintf(stderr, "Matrix sizes do not match\n");
        exit(1);
    }

    Matrix diffM = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        Entry entryA = A->rows[i];
        Entry entryB = B->rows[i];

        while (entryA != NULL || entryB != NULL) {
            int colA = entryA ? entryA->column : INT_MAX;
            int colB = entryB ? entryB->column : INT_MAX;

            if (colA == colB) {
                changeEntry(diffM, i, colA, entryA->value - entryB->value);
                entryA = entryA->next;
                entryB = entryB->next;
            } else if (colA < colB) {
                changeEntry(diffM, i, colA, entryA->value);
                entryA = entryA->next;
            } else {
                changeEntry(diffM, i, colB, -entryB->value);
                entryB = entryB->next;
            }
        }
    }

    return diffM;
}

Matrix product(Matrix A, Matrix B) {
    if (A->size != B->size) {
        fprintf(stderr, "Matrix sizes do not match\n");
        exit(1);
    }

    Matrix productM = newMatrix(A->size);
    Matrix transposedB = transpose(B);

    for (int i = 1; i <= A->size; i++) {
        for (int j = 1; j <= A->size; j++) {
            double sum = 0.0;
            Entry entryA = A->rows[i];
            Entry entryB = transposedB->rows[j];

            while (entryA != NULL && entryB != NULL) {
                if (entryA->column < entryB->column) {
                    entryA = entryA->next;
                } else if (entryA->column > entryB->column) {
                    entryB = entryB->next;
                } else {
                    sum += entryA->value * entryB->value;
                    entryA = entryA->next;
                    entryB = entryB->next;
                }
            }

            if (sum != 0.0) {
                changeEntry(productM, i, j, sum);
            }
        }
    }

    freeMatrix(&transposedB);
    return productM;
}

void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        Entry entry = M->rows[i];

        if (entry != NULL) {
            fprintf(out, "%d: ", i);

            while (entry != NULL) {
                fprintf(out, "(%d, %.1f) ", entry->column, entry->value);
                entry = entry->next;
            }

            fprintf(out, "\n");
        }
    }
}
