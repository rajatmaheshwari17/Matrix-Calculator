
# SparseMatrixCalc

SparseMatrixCalc is a high-performance C program designed for efficient operations on sparse matrices. Leveraging the sparseness of matrices, it provides fast computations for large matrices by storing and manipulating only the non-zero elements. This approach significantly reduces both space and time complexity, making it ideal for applications in scientific computing, engineering, and any domain where sparse matrices are prevalent.

## Features

- **Matrix Operations**: Supports a variety of operations on sparse matrices, including addition, subtraction, multiplication, scalar multiplication, and transpose.
- **Efficient Storage**: Utilizes a 1-dimensional array of lists to store non-zero elements along with their column indices, optimizing memory usage.
- **Scalability**: Capable of handling very large matrices efficiently, provided they are sparse.
- **Dynamic Memory Management**: Implements careful memory management to avoid leaks and ensure efficiency.
- **File Input/Output**: Reads matrices from files and writes the result of operations to files, allowing for easy integration with other programs and data sources.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC or Clang)
- Make (for using the provided Makefile)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/SparseMatrixCalc.git
   ```
2. Navigate to the project directory:
   ```bash
   cd SparseMatrixCalc
   ```
3. Compile the program using Make:
   ```bash
   make
   ```
   This will create an executable named `Sparse`.

### Usage

To perform matrix operations, run `Sparse` with two arguments: the input file and the output file names. The input file should follow the specified format for sparse matrices.

```bash
./Sparse inputfile.txt outputfile.txt
```

#### Input File Format

The input file must start with a single line containing three integers: `n`, `a`, and `b`, separated by spaces, where `n` is the size of the square matrices, `a` is the number of non-zero entries in matrix A, and `b` is the same for matrix B. The following lines specify the non-zero entries for matrices A and B in the format: `row column value`.

#### Output File Format

The output file will contain the matrices resulting from the operations specified in the program, each with its non-zero entries listed in a row-wise manner.


## License

This project is open source and available under the [MIT License](LICENSE.md).

##
This README is a part of the SparseMatrixCalc Project by Rajat Maheshwari.
