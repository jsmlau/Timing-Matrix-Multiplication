# Timing Matrix Multiplication

> This project shows the timeing of matrix multiplication by using dynamic 2D array in C++.

---

## Usage

Dynamic 2D arrays - Matrix A, B , C

```cpp
for (r = 0; r < MAT_SIZE; r++) {
    matA[r] = new float[MAT_SIZE];
    matB[r] = new float[MAT_SIZE];
    matC[r] = new float[MAT_SIZE];
    for (c = 0; c < MAT_SIZE; c++) {
      matA[r][c] = initVal;
      matB[r][c] = initVal;
      matC[r][c] = initVal;
    }
  }
```

Matrix Multiplication

```cpp
void matAMult(const DynamicMat& matA, const DynamicMat& matB, DynamicMat& matC,
              int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        matC[i][j] += matA[i][k] * matB[k][j];
      }
    }
  }
}
```

Show *5 x 5* sub-matrices

```cpp
showDynamicMat(matC, MAT_SIZE - 10, 5);
```

Timing Result

```cpp
10 % sparse Matrix A, B
Matrix size = 100 x 100

Matrix A
00.00 00.00 00.00 00.00 00.00
00.14 00.98 00.00 00.00 00.00
00.00 00.15 00.00 00.00 00.00
00.96 00.00 00.00 00.00 00.00
00.00 00.00 00.00 00.00 00.00
Percent = 10 %

Matrix B
00.00 00.00 00.23 00.00 00.00
00.00 00.00 00.00 00.00 00.00
00.00 00.00 00.00 00.72 00.00
00.41 00.00 00.00 00.00 00.00
00.00 00.00 00.00 00.00 00.00

Matrix C
00.00 00.00 00.06 00.18 00.07
00.00 00.00 00.38 00.21 00.00
00.65 00.34 01.05 00.29 00.48
00.91 00.00 01.09 00.71 00.25
00.58 00.00 00.11 00.00 00.19

Elapsed Time: 10.93 seconds.
```

---

## Related repo

[jsmlau/Sparse-Matrix](https://github.com/jsmlau/Sparse-Matrix)</br>

[jsmlau/Sparse-Matrix-Multiplication](https://github.com/jsmlau/Sparse-Matrix-Multiplication)</br>

---

## Author

- GitHub - [@jsmlau](https://github.com/jsmlau)

[Back To The Top](#read-me-template)