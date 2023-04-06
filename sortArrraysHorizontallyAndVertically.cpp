#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int getRandomNumber(int range) { return (rand() % range) + 1; }

void customSwap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void insertionSort(int arr[]) {
  for (int i = 1; i < 3; i++) {
    int j = i;
    while ((j > 0) && (arr[j] < arr[j - 1])) {
      customSwap(arr[j], arr[j - 1]);
      j--;
    }
  }
}

void generateArray(int arr[]) {
  for (int i = 0; i < 3; i++) {
    arr[i] = getRandomNumber(20);
  }
}

void printArray(int arr[]) {
  for (int i = 0; i < 3; i++) {
    std::cout << arr[i] << "\t";
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

int main() {
  srand(time(0));

  // Table
  int table[3][3] = {0};

  // Declare
  int arr1[3];
  int arr2[3];
  int arr3[3];

  // Define
  generateArray(arr1);
  generateArray(arr2);
  generateArray(arr3);

  // Print
  std::cout << "Original Arrays" << std::endl;
  printArray(arr1);
  printArray(arr2);
  printArray(arr3);

  // Sort
  insertionSort(arr1);
  insertionSort(arr2);
  insertionSort(arr3);

  // Print
  std::cout << "Sorted Arrays" << std::endl;
  printArray(arr1);
  printArray(arr2);
  printArray(arr3);

  // Fill table with arrays
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      if (r == 0) {
        table[r][c] = arr1[c];
      }
      if (r == 1) {
        table[r][c] = arr2[c];
      }
      if (r == 2) {
        table[r][c] = arr3[c];
      }
    }
  }

  // Print table
  std::cout << "Original Table" << std::endl;
  for (int k = 0; k < 3; k++) {
    for (int l = 0; l < 3; l++) {
      std::cout << table[k][l] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  int arr[3] = {0};

  // Sort first column
  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      if (b == 0) {
        arr[a] = table[a][0];
      }
    }
  }
  // Sort the column
  insertionSort(arr);
  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      if (b == 0) {
        table[a][0] = arr[a];
      }
    }
  }

  // Sort second column
  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      if (b == 1) {
        arr[a] = table[a][1];
      }
    }
  }
  // Sort the column
  insertionSort(arr);
  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      if (b == 1) {
        table[a][1] = arr[a];
      }
    }
  }

  // Sort third column
  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      if (b == 2) {
        arr[a] = table[a][2];
      }
    }
  }
  // Sort the column
  insertionSort(arr);
  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      if (b == 2) {
        table[a][2] = arr[a];
      }
    }
  }

  // Print table
  std::cout << "Modified Table" << std::endl;
  for (int k = 0; k < 3; k++) {
    for (int l = 0; l < 3; l++) {
      std::cout << table[k][l] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
