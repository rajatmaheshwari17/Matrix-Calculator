#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "List.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(1);
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Unable to open input file: %s\n", argv[1]);
        exit(1);
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Unable to open output file: %s\n", argv[2]);
        fclose(inputFile);
        exit(1);
    }

    int n, a, b;
    fscanf(inputFile, "%d %d %d", &n, &a, &b);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    for (int i = 0; i < a; i++) {
        int row, column;
        double value;
        fscanf(inputFile, "%d %d %lf", &row, &column, &value);
        changeEntry(A, row, column, value);
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), inputFile);

    for (int i = 0; i < b; i++) {
        int row, column;
        double value;
        fscanf(inputFile, "%d %d %lf", &row, &column, &value);
        changeEntry(B, row, column, value);
    }

    fclose(inputFile);

    fprintf(outputFile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outputFile, A);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outputFile, B);
    fprintf(outputFile, "\n");

    Matrix C = scalarMult(1.5, A);
    fprintf(outputFile, "(1.5)*A =\n");
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    freeMatrix(&C);

    C = sum(A, B);
    fprintf(outputFile, "A+B =\n");
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    freeMatrix(&C);

    C = sum(A, A);
    fprintf(outputFile, "A+A =\n");
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    freeMatrix(&C);

    C = diff(B, A);
    fprintf(outputFile, "B-A =\n");
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    freeMatrix(&C);

    C = diff(A, A);
    fprintf(outputFile, "A-A =\n");
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    freeMatrix(&C);

    C = transpose(A);
    fprintf(outputFile, "Transpose(A) =\n");
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    freeMatrix(&C);

    C = product(A, B);
    fprintf(outputFile, "A*B =\n");
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    freeMatrix(&C);

    C = product(B, B);
    fprintf(outputFile, "B*B =\n");
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    freeMatrix(&C);

    fclose(outputFile);

    freeMatrix(&A);
    freeMatrix(&B);

    return 0;
}
