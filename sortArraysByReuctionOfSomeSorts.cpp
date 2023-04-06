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

void customSwap(std::pair<int, int> &a, std::pair<int, int> &b) {
  std::pair<int, int> temp = a;
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

void sortCollection(std::vector<std::pair<int, int>> &vec) {
  for (int i = 1; i < 3; i++) {
    int j = i;
    while ((j > 0) && (vec[j].second < vec[j - 1].second)) {
      customSwap(vec[j], vec[j - 1]);
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

int reduceArray(int arr[]) {
  int sum = 0;
  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      sum += arr[i] * 100;
      break;
    case 1:
      sum += arr[i] * 10;
      break;
    case 2:
      sum += arr[i];
      break;
    }
  }
  return sum;
}

int main() {
  srand(time(0));

  // Declare
  int arr1[3];
  int arr2[3];
  int arr3[3];

  std::vector<std::pair<int, int>> collection;

  // Define
  generateArray(arr1);
  collection.emplace_back(std::make_pair(0, reduceArray(arr1)));
  generateArray(arr2);
  collection.emplace_back(std::make_pair(1, reduceArray(arr2)));
  generateArray(arr3);
  collection.emplace_back(std::make_pair(2, reduceArray(arr3)));

  // Print
  std::cout << "Original Arrays" << std::endl;
  printArray(arr1);
  printArray(arr2);
  printArray(arr3);

  // Space
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  // Sort
  insertionSort(arr1);
  insertionSort(arr2);
  insertionSort(arr3);

  std::cout << "Individually Sorted Arrays" << std::endl;
  printArray(arr1);
  printArray(arr2);
  printArray(arr3);

  // Space
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  // Sort and print
  sortCollection(collection);
  std::cout << "Collectively Sorted Arrays" << std::endl;
  for (auto item : collection) {
    if (item.first == 0) {
      printArray(arr1);
    } else if (item.first == 1) {
      printArray(arr2);
    } else {
      printArray(arr3);
    }
  }
}
