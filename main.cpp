
#include <math.h>
#include <time.h>

#include <ctime>
#include <iomanip>
#include <iostream>

#define MAT_SIZE 1000

typedef float* DynamicMat[MAT_SIZE];

void matAMult(const DynamicMat& matA, const DynamicMat& matB, DynamicMat& matC,
              int size);
void showDynamicMat(const DynamicMat& matA, int start, int size);

//========================= Global Scope Function ============================

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

void showDynamicMat(const DynamicMat& matA, int start, int size) {
  if (start < 0 || size <= 0) std::cout << "\nOut of bound!" << std::endl;

  std::cout << std::setprecision(2) << std::fixed;
  for (int i = start; i < start + size; i++) {
    std::cout << "\n";
    for (int j = start; j < start + size; j++) {
      std::cout << std::setw(5) << std::setfill('0') << std::setprecision(2)
                << std::fixed;
      std::cout << matA[i][j] << " ";
    }
  }
  std::cout << std::endl;
}

//============================== Main Program ================================

int main() {
  int i, r, c;
  clock_t startTime, stopTime;
  double randFrac;
  double initVal = 0.00;
  int smallPercent;
  double low = 0.1, high = 0.99, range = (high - low);

  DynamicMat matA, matB, matC;

  //----------------- allocate matrices -----------------------
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

  //   smallPercent = MAT_SIZE / 100. * MAT_SIZE;  // 5%
  smallPercent = MAT_SIZE / 10. * MAT_SIZE;  // 10%
  //   smallPercent = MAT_SIZE *(3 / 10) * MAT_SIZE;  // 30%

  int percentX = (smallPercent / double(MAT_SIZE * MAT_SIZE)) * 100;
  srand((unsigned int)time(0));

  for (r = 0; r < smallPercent; r++) {
    // check range 0 < smallPercent <= 10
    if (percentX < 0.1 || percentX > 10) {
      std::cout << "small % must be between 0.1% and 10%!" << std::endl;
      exit(0);
    }
    int randRow = rand() % MAT_SIZE;
    int randCol = rand() % MAT_SIZE;
    randFrac = low + (range * rand() / (RAND_MAX + 1.0));
    // assign to matA
    if (matA[randRow][randCol] == 0.0) {
      matA[randRow][randCol] = randFrac;
    }
    randRow = rand() % MAT_SIZE;
    randCol = rand() % MAT_SIZE;
    randFrac = low + (range * rand() / (RAND_MAX + 1.0));
    // assign to matB
    if (matB[randRow][randCol] == 0.0) {
      matB[randRow][randCol] = randFrac;
    }
  }
  std::cout << "Percent = " << percentX << " %" << std::endl;
  std::cout << "\nSize = " << MAT_SIZE;
  std::cout << "\nMatrix A" << std::endl;
  // 10x10 submatrix in lower right
  showDynamicMat(matA, MAT_SIZE - 10, 5);
  std::cout << "\nMatrix B" << std::endl;
  // 10x10 submatrix in lower right
  showDynamicMat(matB, MAT_SIZE - 10, 5);

  startTime = clock();  // ------------------ start
  matAMult(matA, matB, matC, MAT_SIZE);
  stopTime = clock();  // ---------------------- stop

  std::cout << "\nnMatrix C" << std::endl;
  showDynamicMat(matC, MAT_SIZE, 5);
  std::cout << " matAMult Elapsed Time: "
            << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
            << " seconds." << std::endl
            << std::endl;

  // clean up
  for (r = 0; r < MAT_SIZE; r++) {
    delete[] matA[r];
    delete[] matB[r];
  }
  std::cout << std::endl;
}
